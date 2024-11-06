#pragma once
#define MYCLASS_EXPORTS
#ifdef MYCLASS_EXPORTS
#define MYCLASS_API __declspec(dllexport)
#else
#define MYCLASS_API __declspec(dllimport)
#endif
#include "NvOnnxParser.h"
#include "logging.h"
#include "NvInfer.h"
#include <fstream>
using namespace std;
using namespace nvinfer1;

class MYCLASS_API  Onnx2Trt
{  public:
	void onnxToTRTModel(const std::string &modelFile, // name of the onnx model
		const std::string &engineFile,  // name of saved engine
		const int &BATCH_SIZE);
};

