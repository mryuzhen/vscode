#需要的CMake版本号
cmake_minimum_required(VERSION 3.0)

#工程名
project(hellolib)
#project(<PROJECT-NAME> [LANGUAGES] [<language-name>...])
#设置需要的C++标准
set(CXX_STANDARD 11)

#设置最小的C++标准
set(CXX_STANDARD_REQUIRED 11)
SET(CMAKE_BUILD_TYPE "DEBUG")

#add_subdirectory(opengl-test)
#add_subdirectory(opencv-test)
#add_subdirectory(texture-test)
#add_subdirectory(matrix)
#add_subdirectory(box)
add_subdirectory(breakout)
