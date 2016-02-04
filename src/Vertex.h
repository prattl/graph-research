#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <vector>
#include <iostream>
#include <memory>
#include "Edge.h"

namespace graphs {
    class Vertex {
        struct VertexData;
        std::unique_ptr<VertexData> data;
    public:
        // TODO: Should vertices hold pointers to their edges or an adjacency list of neighbors?
        std::vector<Vertex*> neighbors;
//        std::vector<std::unique_ptr<Edge>> edges;  // Vertices own their originating edges
        Vertex* previous;

        bool matched; // Temporary, for use in Ullmann traversal

        void visit() const;
        void unVisit() const;
        bool isVisited() const;

        std::string getLabel() const;
        void addNeighbor(Vertex&);
        bool isNeighborTo(const Vertex&) const;
//        void addEdge(const Edge&);

//        std::vector<Vertex*> getNeighbors() const;

        Vertex(const std::string);
        ~Vertex();
        Vertex(const Vertex&);
        Vertex& operator=(const Vertex&);

        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    };

}


#endif //GRAPHS_VERTEX_H
