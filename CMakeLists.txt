cmake_minimum_required(VERSION 3.26)
project(OpenMPTask)

# added -fopenmp
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")

set(CMAKE_CXX_STANDARD 17)

add_executable(OpenMPTask main.cpp)
