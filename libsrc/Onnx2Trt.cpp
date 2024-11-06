#include "Onnx2Trt.h"

void Onnx2Trt::onnxToTRTModel(const std::string &modelFile, // name of the onnx model
	const std::string &engineFile,  // name of saved engine
	const int &BATCH_SIZE)
{
	int verbosity = (int)nvinfer1::ILogger::Severity::kWARNING;
	static Logger gLogger;
	// create the builder
	nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(gLogger);//创建构建器(即指向Ibuilder类型对象的指针)
	nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();//创建生成器配置对象
	const auto explicitBatch = 1U << static_cast<uint64_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
	nvinfer1::INetworkDefinition* network = builder->createNetworkV2(explicitBatch);/*等价于*bulider.createNetwork(),通过Ibulider定义的名为creatNetwork()方法，创建INetworkDefinition的对象，ntework这个指针指向这个对象*/

	auto parser = nvonnxparser::createParser(*network, gLogger.getTRTLogger());//创建解析器

	if (!parser->parseFromFile(modelFile.c_str(), verbosity)) //解析onnx文件，并填充网络
	{
		std::string msg("failed to parse onnx file");
		gLogger.log(nvinfer1::ILogger::Severity::kERROR, msg.c_str());
		exit(EXIT_FAILURE);
	}

	// Build the engine
	builder->setMaxBatchSize(1);
	config->setMaxWorkspaceSize(1 << 30);
	//builder->setMaxWorkspaceSize(1 << 30);
#if 0
	config->setFlag(BuilderFlag::kFP16);
#endif
	config->setFlag(BuilderFlag::kFP16);
	// samplesCommon::enableDLA(builder, gUseDLACore);
	//当引擎建立起来时，TensorRT会复制
	nvinfer1::ICudaEngine *engine = builder->buildEngineWithConfig(*network, *config);
	assert(engine);

	// we can destroy the parser
	parser->destroy();

	// serialize the engine, 
	// then close everything down
	nvinfer1::IHostMemory* trtModelStream = engine->serialize();//将引擎序列化，保存到文件中
	engine->destroy();
	network->destroy();
	builder->destroy();
	config->destroy();

	std::ofstream out(engineFile, std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "打开文件失败!" << std::endl;
	}
	out.write(reinterpret_cast<const char*>(trtModelStream->data()), trtModelStream->size());
	out.close();

}
