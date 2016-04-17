cmake_minimum_required(VERSION 3.5)
project(SysMeasure)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    LICENSE
    README.md CPU/main.cpp lib/rdtscp.h common.h)

add_executable(SysMeasure ${SOURCE_FILES})