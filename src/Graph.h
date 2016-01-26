#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Vertex.h"

namespace graphs {

    class Graph {
        std::vector<smartVertexPtr> nodes;

        void recursiveDfs(Vertex&);

        void depthLimitedDfs(Vertex&, int);

    public:
        virtual void printGraph();

        virtual void addVertex(std::string);

        Vertex* getVertex(std::string);

        void prepareTraverse();

        void addEdge(std::string, std::string);

        virtual Vertex* traverseToVertexBfs(std::string, std::string);

        Vertex* traverseToVertexBfs(Vertex&, Vertex&);

        virtual void traverseDfsRecursive(std::string);

        void traverseDfsIterative(std::string);

        void traverseDfsIterativeDeepening(std::string);
    };
}

#endif //GRAPHS_GRAPH_H
