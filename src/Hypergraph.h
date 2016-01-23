#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"

namespace hypergraphs {
    class HyperEdge;

    typedef std::shared_ptr<HyperEdge> smartEdgePtr;

    class HyperEdge {
        std::vector<graphs::smartVertexPtr> nodes;
    public:

        std::string name;
        HyperEdge(std::string s) : name(s) {};
        bool isVertexInEdge(const graphs::smartVertexPtr);
        void addVertex(graphs::smartVertexPtr);

        friend std::ostream& operator<<(std::ostream &strm, const HyperEdge &he) {
            std::string nodes_str;
            for (auto const& node: he.nodes) {
                nodes_str += node->name + ", ";
            }
            nodes_str = nodes_str.substr(0, nodes_str.length() - 2);
            return strm << "Edge: " << he.name << " (nodes: " << nodes_str << ")";
        }
    };

    class HyperGraph : graphs::Graph {
        std::vector<smartEdgePtr> edges;
    public:
        void printGraph();
        void addVertex(std::string);
        void addEdge(std::string);
        void connectVertexToEdge(std::string, std::string);
        smartEdgePtr getEdge(std::string);
    };

}

#endif
