1.设置成自己的安装目录<br>
set(TENSORRT_ROOT "E:/TensorRT-8.5.3.1")<br>
set(CUDA_ROOT "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v11.2")<br>
set( CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "E:/Qt/Qt5.9.2/5.9.2/msvc2017_64" )<br>

2.构建<br>
mkdir build <br>
cd build <br>
cmake .. <br>
cmake --build . <br>

注意：需要动态链接 tensort库 和QT库 <br>
