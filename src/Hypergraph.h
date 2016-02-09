#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"
#include "HyperEdge.h"
#include "HyperVertex.h"

namespace hypergraphs {
    class HyperGraph {
        std::vector<smartHyperEdgePtr> edges;
        std::vector<smartHyperVertexPtr> nodes;
//        std::vector<std::unique_ptr<HyperVertex>> nodes;
        void recursiveDfs(const HyperVertex&);
    public:
        ~HyperGraph();

        void printGraph() const;

        void addEdge(const std::string);
        void addVertex(const std::string);

        HyperEdge* getEdge(std::string) const;
        HyperVertex* getVertex(std::string) const;

        void connectVertices(HyperVertex&, HyperVertex&, HyperEdge&);
        void connectVertices(std::string, std::string, std::string);

        void prepareForTraversal() const;

        void traverseDfsRecursive(const std::string);
        void traverseDfsRecursive(const HyperVertex&);

    };

}

#endif
