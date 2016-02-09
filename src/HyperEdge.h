#ifndef GRAPHS_HYPEREDGE_H
#define GRAPHS_HYPEREDGE_H

#include "Edge.h"
#include <vector>
#include "typedefs.h"

namespace hypergraphs {

    class HyperEdge {
        struct EdgeData;
        std::unique_ptr<EdgeData> data;

    public:
        std::vector<HyperVertex*> sourceNodes;
        std::vector<HyperVertex*> destinationNodes;
        // Store connected nodes as source and destination vectors
        std::vector<graphs::Vertex*> nodes;

        HyperEdge();
        HyperEdge(std::string);
        HyperEdge(std::string, int);
        ~HyperEdge();

        HyperEdge(const HyperEdge&);
        HyperEdge& operator=(const HyperEdge&);

        std::string getLabel() const;
//        void addNode(graphs::Vertex&);
        friend std::ostream& operator<<(std::ostream&, const HyperEdge&);

        void addSourceVertex(HyperVertex&);
        void addDestinationVertex(HyperVertex&);
    };

    typedef std::vector<HyperEdge*> hyperEdgeList;
    typedef std::unique_ptr<HyperEdge> smartHyperEdgePtr;

}

#endif //GRAPHS_HYPEREDGE_H
