#ifndef GRAPHS_EDGE_H
#define GRAPHS_EDGE_H

#include <memory>
#include <vector>

namespace graphs {
    class Vertex;
    class Edge {
        struct EdgeData;
        std::unique_ptr<EdgeData> data;
    public:
        Vertex* from;
        Vertex* to;
        std::pair<Vertex*, Vertex*> nodes;

        Edge(Vertex&, Vertex&);

        Edge(Vertex&, Vertex&, std::string);

        Edge(Vertex&, Vertex&, std::string, int);

        ~Edge();
    };
}


#endif //GRAPHS_EDGE_H
