#ifndef GRAPHS_HYPERVERTEX_H
#define GRAPHS_HYPERVERTEX_H

#include <vector>
#include "HyperEdge.h"
#include <iostream>
#include <boost/uuid/uuid.hpp>

namespace hypergraphs {

    class HyperEdge;
    using hyperEdgeList = std::vector<HyperEdge*>;
    using smartHyperEdgePtr = std::unique_ptr<HyperEdge>;

    class HyperVertex {
        struct HyperVertexData;
        std::unique_ptr<HyperVertexData> data;

    public:
        hyperEdgeList sourceEdges;      // Edges that point to this node
        hyperEdgeList destinationEdges; // Edges that originate from this node

        HyperVertex();
        HyperVertex(std::string);
        ~HyperVertex();

        void visit() const;
        void unVisit() const;
        bool isVisited() const;
        std::string getLabel() const;
        boost::uuids::uuid getUuid() const;

        void addSourceEdge(HyperEdge&);
        void addDestinationEdge(HyperEdge&);

        friend std::ostream& operator<<(std::ostream&, const HyperVertex&);
    };

    using hyperVertexList = std::vector<HyperVertex*>;
    using smartHyperVertexPtr = std::unique_ptr<HyperVertex>;
}

#endif //GRAPHS_HYPERVERTEX_H
