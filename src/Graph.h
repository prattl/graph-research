#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>

class Vertex
{
public:
    std::string name;
    std::vector<Vertex*> neighbors;
    int distance;
    Vertex* previous;
};


class Graph
{
    std::vector<Vertex*> nodes;
public:
    void printGraph();
    void addVertex(std::string);
    Vertex* getVertex(std::string);
    void addEdge(std::string, std::string);
    Vertex* traverseToVertexBfs(std::string start_name, std::string end_name);
    Vertex* traverseToVertexBfs(Vertex &start, Vertex &end);
    int findShortestPath(Vertex &start, Vertex &end);
};


#endif //GRAPHS_GRAPH_H
