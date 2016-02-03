#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"
#include "HyperEdge.h"

namespace hypergraphs {
    class HyperGraph : graphs::Graph {
        std::vector<smartEdgePtr> edges;
    public:
        ~HyperGraph();

        void printGraph() const;
        void addVertex(const std::string);
//        void printGraph();
//        void addVertex(std::string);
        void addEdge(std::string);
        void addVertexToEdge(std::string, std::string);
        void addEdgeToVertex(std::string, std::string);
        HyperEdge* getEdge(std::string);
        graphs::Vertex* traverseToVertexBfs(const std::string, const std::string);
//        void traverseBfs(std::string);
//        void traverseBfs(graphs::Vertex&);
        void traverseDfsRecursive(const std::string);
    };

}

#endif
