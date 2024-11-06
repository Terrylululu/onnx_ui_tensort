1.
#  设置成自己的安装目录
set(TENSORRT_ROOT "E:/TensorRT-8.5.3.1")
set(CUDA_ROOT "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2")
set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "E:/Qt/Qt5.9.2/5.9.2/msvc2017_64" )

2.
mkdir build 
cd build 
cmake .. 
cmake --build . 

注意：需要动态链接 tensort库 和QT库 
