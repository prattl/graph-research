#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>



class Vertex
{
public:
    std::string name;
    std::vector<std::shared_ptr<Vertex>> neighbors;
    std::shared_ptr<Vertex> previous;  // Used during traversal
    bool visited;
    Vertex() {};
    Vertex(std::string s) : name(s) {};
    ~Vertex();
};

namespace graphs
{
    // shared_ptr is needed because both Vertex and Graph can maintain ownership of Vertex pointers.
    typedef std::shared_ptr<Vertex> smartVertexPtr;
}

class Graph
{
    std::vector<graphs::smartVertexPtr> nodes;
    void recursiveDfs(Vertex&);
    void prepareTraverse();
    void depthLimitedDfs(Vertex&, int);
public:
    void printGraph();
    void addVertex(std::string);
    graphs::smartVertexPtr getVertex(std::string);
    void addEdge(std::string, std::string);
    graphs::smartVertexPtr traverseToVertexBfs(std::string start_name, std::string end_name);
    graphs::smartVertexPtr traverseToVertexBfs(Vertex &start, Vertex &end);
    void traverseDfsRecursive(std::string);
    void traverseDfsIterative(std::string);
    void traverseDfsIterativeDeepening(std::string);
};

#endif //GRAPHS_GRAPH_H
