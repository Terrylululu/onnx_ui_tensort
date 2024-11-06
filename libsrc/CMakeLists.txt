# 设置路径
set(TENSORRT_ROOT "E:/TensorRT-8.5.3.1(自己下载)")
set(CUDA_ROOT "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2")

# 包含头文件目录
include_directories(${TENSORRT_ROOT}/include)
include_directories(${CUDA_ROOT}/include)

# 设置源文件
set(SOURCES
    Onnx2Trt.cpp
    Onnx2Trt.h
)

# 创建可执行文件
add_library(Onnx2Trt   ${SOURCES})



