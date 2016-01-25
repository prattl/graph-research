cmake_minimum_required(VERSION 3.3)
project(graphs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Graph.cpp src/Graph.h src/Hypergraph.cpp src/Hypergraph.h src/Vertex.cpp src/Vertex.h)
add_executable(graphs ${SOURCE_FILES})