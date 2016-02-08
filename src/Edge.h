#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H

#include <memory>
#include <vector>
//#include "Vertex.h"

namespace graphs {
    class Vertex;
    class Edge {
        struct EdgeData;
        std::unique_ptr<EdgeData> data;
    public:
        // Store connected nodes as a pair (source, dest)
        std::pair<Vertex*, Vertex*> nodes;

        Vertex* sourceNode() const;
        Vertex* destNode() const;

        Edge(Vertex&, Vertex&);

        Edge(Vertex&, Vertex&, std::string);

        Edge(Vertex&, Vertex&, std::string, int);

        ~Edge();
    };
}


#endif //GRAPHS_EDGE_H
