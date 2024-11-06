cmake_minimum_required(VERSION 3.10)
# 项目名称
project(onnx_ui_trt)


#  包含头文件目录
set(TENSORRT_ROOT "E:/TensorRT-8.5.3.1(自己下载)")
set(CUDA_ROOT "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2")
set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "E:/Qt/Qt5.9.2/5.9.2/msvc2017_64" )

include_directories(${TENSORRT_ROOT}/include)
include_directories(${CUDA_ROOT}/include)
include_directories(include)

 
set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

# 找到 Qt5 包
find_package(Qt5Widgets REQUIRED)
qt5_wrap_ui( UI_HEADERS widget.ui )

find_library(NVINFER NAMES nvinfer)
find_library(NVPARSERS NAMES nvparsers)
find_library(NVONNXPARSERS NAMES nvonnxparser)

add_subdirectory(${PROJECT_SOURCE_DIR}/libsrc)
# 定义可执行文件
add_executable(onnx_ui_trt
    main.cpp
    widget.cpp   
)
# 链接 Qt5 库
target_link_libraries(onnx_ui_trt
    Qt5::Widgets 
    Onnx2Trt
    ${NVINFER}
    ${NVPARSERS}
    ${NVONNXPARSERS}
)

 




