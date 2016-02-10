#ifndef GRAPHS_HYPERVERTEX_H
#define GRAPHS_HYPERVERTEX_H

#include <vector>
#include "HyperEdge.h"
#include <iostream>

namespace hypergraphs {

    class HyperEdge;
    typedef std::vector<HyperEdge*> hyperEdgeList;
    typedef std::unique_ptr<HyperEdge> smartHyperEdgePtr;

    class HyperVertex {
        struct HyperVertexData;
        std::unique_ptr<HyperVertexData> data;

    public:
        std::vector<HyperEdge*> sourceEdges;
        std::vector<HyperEdge*> destinationEdges;

        HyperVertex();
        HyperVertex(std::string);
        ~HyperVertex();

        void visit() const;
        void unVisit() const;
        bool isVisited() const;
        std::string getLabel() const;

        void addSourceEdge(HyperEdge&);
        void addDestinationEdge(HyperEdge&);

        friend std::ostream& operator<<(std::ostream&, const HyperVertex&);
    };

    typedef std::vector<HyperVertex*> hyperVertexList;

}

#endif //GRAPHS_HYPERVERTEX_H
