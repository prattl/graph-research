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

    typedef std::vector<Vertex*> vertexList;
    typedef std::vector<std::pair<int, int>> embedding;

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

        // Basic isomorphism algorithm methods
        vertexList findIsomorphism(Graph&);
        bool isomorphismSearch(Graph&, vertexList&);

        // Ullmann algorithm methods
        void ullmann(Graph&);
        vertexList ullmannFilterCandidates(const Graph&, const Vertex&) const;
        embedding UllmannSubgraphSearch(Graph&, embedding&);
        vertexList ullmannRefineCandidates(embedding&, Vertex&, vertexList&) const;
    };
}

#endif //GRAPHS_GRAPH_H
