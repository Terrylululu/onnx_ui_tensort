#include "Onnx2Trt.h"

void Onnx2Trt::onnxToTRTModel(const std::string &modelFile, // name of the onnx model
	const std::string &engineFile,  // name of saved engine
	const int &BATCH_SIZE)
{
	int verbosity = (int)nvinfer1::ILogger::Severity::kWARNING;
	static Logger gLogger;
	// create the builder
	nvinfer1::IBuilder* builder = nvinfer1::createInferBuilder(gLogger);//����������(��ָ��Ibuilder���Ͷ����ָ��)
	nvinfer1::IBuilderConfig* config = builder->createBuilderConfig();//�������������ö���
	const auto explicitBatch = 1U << static_cast<uint64_t>(nvinfer1::NetworkDefinitionCreationFlag::kEXPLICIT_BATCH);
	nvinfer1::INetworkDefinition* network = builder->createNetworkV2(explicitBatch);/*�ȼ���*bulider.createNetwork(),ͨ��Ibulider�������ΪcreatNetwork()����������INetworkDefinition�Ķ���ntework���ָ��ָ���������*/

	auto parser = nvonnxparser::createParser(*network, gLogger.getTRTLogger());//����������

	if (!parser->parseFromFile(modelFile.c_str(), verbosity)) //����onnx�ļ������������
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
	//�����潨������ʱ��TensorRT�Ḵ��
	nvinfer1::ICudaEngine *engine = builder->buildEngineWithConfig(*network, *config);
	assert(engine);

	// we can destroy the parser
	parser->destroy();

	// serialize the engine, 
	// then close everything down
	nvinfer1::IHostMemory* trtModelStream = engine->serialize();//���������л������浽�ļ���
	engine->destroy();
	network->destroy();
	builder->destroy();
	config->destroy();

	std::ofstream out(engineFile, std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "���ļ�ʧ��!" << std::endl;
	}
	out.write(reinterpret_cast<const char*>(trtModelStream->data()), trtModelStream->size());
	out.close();

}
