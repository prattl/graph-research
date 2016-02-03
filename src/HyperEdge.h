#ifndef GRAPHS_HYPEREDGE_H
#define GRAPHS_HYPEREDGE_H

#include "Edge.h"
#include <vector>

namespace hypergraphs {
    class HyperEdge {
        struct EdgeData;
        std::unique_ptr<EdgeData> data;
    public:
        // Store connected nodes as a vector
        std::vector<graphs::Vertex*> nodes;

        void init(std::string, int);

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
    typedef std::unique_ptr<HyperEdge> smartEdgePtr;
}


#endif //GRAPHS_HYPEREDGE_H
