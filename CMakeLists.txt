cmake_minimum_required(VERSION 3.3)
project(graphs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Graph.cpp Graph.h)
add_executable(graphs ${SOURCE_FILES})