#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"
#include "HyperEdge.h"

namespace hypergraphs {
    class HyperGraph {
        std::vector<smartHyperEdgePtr> edges;
        std::vector<smartHyperVertexPtr> nodes;
    public:
        ~HyperGraph();

        void printGraph() const;

        void addEdge(std::string);
        void addVertex(const std::string);
//        void addVertexToEdge(std::string, std::string);
//        void addEdgeToVertex(std::string, std::string);

        void connectVertices(std::string, std::string, std::string);

        HyperEdge* getEdge(std::string) const;
        HyperVertex* getVertex(std::string) const;

//        graphs::Vertex* traverseToVertexBfs(const std::string, const std::string);
//        void traverseBfs(std::string);
//        void traverseBfs(graphs::Vertex&);
//        void traverseDfsRecursive(const std::string);
    };

}

#endif
