#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"
#include "HyperEdge.h"

namespace hypergraphs {
    class HyperGraph : graphs::Graph {
        std::vector<smartHyperEdgePtr> edges;
        std::vector<smartHyperVertexPtr> nodes;
    public:
        ~HyperGraph();

        void printGraph() const;
        void addVertex(const std::string);
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
