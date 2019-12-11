cmake_minimum_required(VERSION 2.8)
project(LaneDetection)

set(CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_FLAGS "-std=c++11")

# 指定编译器
# set(CMAKE_C_COMPILER "/usr/bin/aarch64-linux-gnu-gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/aarch64-linux-gnu-g++")

# set(CMAKE_PREFIX_PATH 
#     "/home/lho/Programm/opencv-3.4.8/build-arm"
# )

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty
)

find_package(OpenCV 3.4.8 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR})
# link_directories(
#     /usr/lib/x86_64-linux-gnu
# )
message(${OpenCV_LIBS})

# Eigen
include_directories(
    /usr/local/include/eigen3/Eigen
)
#4.source directory，源文件目录
# aux_source_directory(src)

add_library(imagehandle
    include/ImageHandle.h
    src/ImageHandle.cc
)
target_link_libraries(imagehandle
    ${OpenCV_LIBS}
)
add_library(lanefitting
    include/LaneFitting.h
    include/CurveFit.h
    src/CurveFit.cc
    src/LaneFitting.cc
)
target_link_libraries(imagehandle
    ${PROJECT_NAME}_backend
)
#6.add executable file，添加要编译的可执行文件
add_executable(LaneDetection_TEST
    src/main.cpp
)
target_link_libraries(LaneDetection_TEST
    ${OpenCV_LIBS}
    ${PROJECT_NAME}_backend
    # libopencv_highgui.so
    imagehandle
    lanefitting
)

add_executable(Read_YUV
    read_from_yuv.cpp
)
target_link_libraries(Read_YUV
    ${OpenCV_LIBS}
)

add_executable(testQuadFitting
    include/CurveFit.h
    src/CurveFit.cc
    src/CurveFit_TEST.cc
)
target_link_libraries(testQuadFitting
    ${PROJECT_NAME}_backend
)