cmake_minimum_required(VERSION 3.3)
project(graphs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(SOURCE_FILES src/main.cpp src/Graph.cpp src/Graph.h src/Vertex.cpp src/Vertex.h src/Edge.cpp src/Edge.h src/HyperEdge.cpp src/HyperEdge.h src/Hypergraph.cpp src/Hypergraph.h src/typedefs.h src/HyperVertex.cpp src/HyperVertex.h)
add_executable(graphs ${SOURCE_FILES})