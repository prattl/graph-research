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
        bool isVertexInEdge(const graphs::Vertex*);
        void addVertex(graphs::smartVertexPtr);

        friend std::ostream& operator<<(std::ostream &strm, const HyperEdge &he);
    };

    class HyperGraph : graphs::Graph {
        std::vector<smartEdgePtr> edges;
    public:
        void printGraph();
        void addVertex(std::string);
        void addEdge(std::string);
        void connectVertexToEdge(std::string, std::string);
        HyperEdge* getEdge(std::string);
        graphs::Vertex* traverseToVertexBfs(std::string start_name, std::string end_name);
        void traverseBfs(std::string);
        void traverseBfs(graphs::smartVertexPtr);
        void traverseDfsRecursive(std::string);
    };

}

#endif
