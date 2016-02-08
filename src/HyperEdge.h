#ifndef GRAPHS_HYPEREDGE_H
#define GRAPHS_HYPEREDGE_H

#include "Edge.h"
#include "HyperVertex.h"
#include <vector>

namespace hypergraphs {
    class HyperVertex;

//    typedef std::vector<HyperVertex> hyperVertexList;
//    typedef std::unique_ptr<HyperVertex> smartHyperVertexPtr;

    class HyperEdge {
        struct EdgeData;
        std::unique_ptr<EdgeData> data;
    public:
        // Store connected nodes as source and destination vectors
        std::vector<graphs::Vertex*> nodes;
        std::vector<HyperVertex*> sourceNodes;
        std::vector<HyperVertex*> destinationNodes;

        HyperEdge();
        HyperEdge(std::string);
        HyperEdge(std::string, int);
        ~HyperEdge();

        HyperEdge(const HyperEdge&);
        HyperEdge& operator=(const HyperEdge&);

        std::string getLabel() const;
        void addNode(graphs::Vertex&);
        friend std::ostream& operator<<(std::ostream&, const HyperEdge&);
    };

}

#endif //GRAPHS_HYPEREDGE_H
