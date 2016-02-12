#ifndef GRAPHS_HYPEREDGE_H
#define GRAPHS_HYPEREDGE_H

#include "Edge.h"
#include <vector>
#include "typedefs.h"

namespace hypergraphs {

    class HyperEdge {
        struct HyperEdgeData;
        std::unique_ptr<HyperEdgeData> data;

    public:
        hyperVertexList sourceNodes;
        hyperVertexList destinationNodes;

        HyperEdge();
        HyperEdge(std::string);
        HyperEdge(std::string, int);
        ~HyperEdge();

        HyperEdge(const HyperEdge&);
        HyperEdge& operator=(const HyperEdge&);

        std::string getLabel() const;

        void addSourceVertex(HyperVertex&);
        void addDestinationVertex(HyperVertex&);

        friend std::ostream& operator<<(std::ostream&, const HyperEdge&);
    };

    typedef std::vector<HyperEdge*> hyperEdgeList;
    typedef std::unique_ptr<HyperEdge> smartHyperEdgePtr;

}

#endif //GRAPHS_HYPEREDGE_H
