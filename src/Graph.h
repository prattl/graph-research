#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Vertex.h"
#include <tuple>

namespace graphs {

    typedef std::unique_ptr<Vertex> smartVertexPtr;
    typedef std::unique_ptr<Edge> smartEdgePtr;
    typedef std::tuple<Vertex*, Vertex*, Vertex*> Triangle;
    typedef std::vector<std::vector<int>> AdjacencyMatrix;

    class Graph {
        std::vector<smartVertexPtr> nodes;

        void recursiveDfs(Vertex&);
        void depthLimitedDfs(Vertex&, int);

    public:
        std::vector<smartEdgePtr> edges;

        virtual ~Graph();

        virtual void printGraph() const;
        virtual void addVertex(const std::string);
        Vertex* getVertex(const std::string) const;
        void prepareTraverse() const;
        void addEdge(const std::string, const std::string);
        virtual Vertex* traverseToVertexBfs(const std::string, const std::string);
        Vertex* traverseToVertexBfs(Vertex&, const Vertex&);
        virtual void traverseDfsRecursive(const std::string);
        void traverseDfsIterative(const std::string);
        void traverseDfsIterativeDeepening(const std::string);

        int getVertexInDegree(const Vertex&) const;
        int getVertexOutDegree(const Vertex&) const;

        Triangle findTriangle() const;

        AdjacencyMatrix buildAdjacencyMatrix();
//        AdjacencyMatrix ullman();

        std::vector<Vertex*> filterCandidates(const Graph&, const Vertex&) const;
        void ullmann(Graph&);
    };
}

#endif //GRAPHS_GRAPH_H
