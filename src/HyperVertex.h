#ifndef GRAPHS_HYPERVERTEX_H
#define GRAPHS_HYPERVERTEX_H

#include <vector>
#include "HyperEdge.h"
#include <iostream>

namespace hypergraphs {

    class HyperEdge;

    typedef std::vector<HyperEdge> hyperEdgeList;
    typedef std::unique_ptr<HyperEdge> smartHyperEdgePtr;

    class HyperVertex {
        struct HyperVertexData;
        std::unique_ptr<HyperVertexData> data;
        hyperEdgeList sourceEdges;
        hyperEdgeList destinationEdges;
    public:
        HyperVertex();
        HyperVertex(std::string);
        ~HyperVertex();
        std::string getLabel() const;
        friend std::ostream& operator<<(std::ostream&, const HyperVertex&);
    };
    typedef std::vector<HyperVertex> hyperVertexList;
    typedef std::unique_ptr<HyperVertex> smartHyperVertexPtr;



}

#endif //GRAPHS_HYPERVERTEX_H
