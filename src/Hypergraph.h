#ifndef GRAPHS_HYPERGRAPH_H
#define GRAPHS_HYPERGRAPH_H

#include <vector>
#include <iostream>
#include <memory>
#include "Graph.h"
#include "HyperEdge.h"
#include "HyperVertex.h"

namespace hypergraphs {
    using vertexMapping = std::pair<HyperVertex*, HyperVertex*>;
    using isomorphism = std::vector<vertexMapping>;
    class HyperGraph {

        std::vector<smartHyperEdgePtr> edges;
        std::vector<smartHyperVertexPtr> nodes;

        void recursiveDfs(const HyperVertex &);
        bool subgraphSearch(HyperGraph&, isomorphism&);
        hyperVertexList filterCandidates(const HyperGraph&, const HyperVertex&) const;
        HyperVertex* nextQueryVertex(HyperGraph&, isomorphism&);
        hyperVertexList refineCandidates(const HyperGraph&, isomorphism&, const HyperVertex&);
        bool isJoinable(const HyperGraph&, isomorphism&,
                        HyperVertex&, HyperVertex&);
    public:
        ~HyperGraph();

        void printGraph() const;

        void addEdge(const std::string);

        void addVertex(const std::string);

        HyperEdge *getEdge(std::string) const;

        HyperVertex *getVertex(std::string) const;

        void connectVertices(HyperVertex &, HyperVertex &, HyperEdge &);

        void connectVertices(std::string, std::string, std::string);

        void prepareForTraversal() const;

        void traverseDfsRecursive(const std::string);

        void traverseDfsRecursive(const HyperVertex &);

        isomorphism findIsomorphism(HyperGraph&);

    };
}

#endif
