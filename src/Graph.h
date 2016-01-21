#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>

class Vertex
{
public:
    std::string name;
    std::vector<Vertex*> neighbors;
    Vertex* previous;  // Used during traversal
    bool visited;
};


class Graph
{
    std::vector<Vertex*> nodes;
    void recursiveDfs(Vertex&);
    void prepareTraverse();
public:
    void printGraph();
    void addVertex(std::string);
    Vertex* getVertex(std::string);
    void addEdge(std::string, std::string);
    Vertex* traverseToVertexBfs(std::string start_name, std::string end_name);
    Vertex* traverseToVertexBfs(Vertex &start, Vertex &end);
    void traverseDfsRecursive(std::string);
    void traverseDfsIterative(std::string);
};


#endif //GRAPHS_GRAPH_H
