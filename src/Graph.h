#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Vertex.h"
//#include "Edge.h"

namespace graphs {

    typedef std::unique_ptr<Vertex> smartVertexPtr;
    typedef std::unique_ptr<Edge> smartEdgePtr;

    class Graph {
        std::vector<smartVertexPtr> nodes;
        std::vector<smartEdgePtr> edges;

        void recursiveDfs(Vertex&);
        void depthLimitedDfs(Vertex&, int);

    public:
        virtual ~Graph();

        virtual void printGraph() const;
        virtual void addVertex(const std::string);
        Vertex* getVertex(const std::string) const;
        void prepareTraverse() const;
        void addEdge(const std::string, const std::string) const;
        virtual Vertex* traverseToVertexBfs(const std::string, const std::string);
        Vertex* traverseToVertexBfs(Vertex&, const Vertex&);
        virtual void traverseDfsRecursive(const std::string);
        void traverseDfsIterative(const std::string);
        void traverseDfsIterativeDeepening(const std::string);

        bool search(Graph&, std::vector<Vertex*>&);
        std::vector<Vertex*> findIsomorphism(Graph&);
    };
}

#endif //GRAPHS_GRAPH_H
