#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Vertex.h"

namespace graphs {

    typedef std::unique_ptr<Vertex> smartVertexPtr;

    class Graph {
        std::vector<smartVertexPtr> nodes;
        void recursiveDfs(Vertex&);
        void depthLimitedDfs(Vertex&, int);

    public:
        ~Graph();
        virtual void printGraph() const;
        virtual void addVertex(const std::string);
        Vertex* getVertex(const std::string);
        void prepareTraverse();
        void addEdge(const std::string, const std::string);
        virtual Vertex* traverseToVertexBfs(const std::string, const std::string);
        Vertex* traverseToVertexBfs(Vertex&, const Vertex&);
        virtual void traverseDfsRecursive(const std::string);
        void traverseDfsIterative(const std::string);
        void traverseDfsIterativeDeepening(const std::string);
    };
}

#endif //GRAPHS_GRAPH_H
