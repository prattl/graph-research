#ifndef GRAPHS_TYPEDEFS_H
#define GRAPHS_TYPEDEFS_H

#include "HyperEdge.h"
#include "HyperVertex.h"
#include <vector>
#include <memory>

namespace hypergraphs {
    class HyperEdge;
    class HyperVertex;

    typedef std::vector<HyperEdge*> hyperEdgeList;
    typedef std::unique_ptr<HyperEdge> smartHyperEdgePtr;
    typedef std::vector<HyperVertex*> hyperVertexList;
    typedef std::unique_ptr<HyperVertex> smartHyperVertexPtr;

}

#endif //GRAPHS_TYPEDEFS_H
