#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <vector>
#include <iostream>
#include <memory>

namespace graphs {
    class Vertex;

    // shared_ptr is needed because both Vertex and Graph can maintain ownership of Vertex pointers.
    typedef std::unique_ptr<Vertex> smartVertexPtr;

    class Vertex {
    public:
        std::string name;
        std::vector<Vertex*> neighbors;
        Vertex* previous;  // Used during traversal
        bool visited;
        void addNeighbor(Vertex*);
        bool isNeighborTo(Vertex*);

        Vertex() { };

        Vertex(std::string s) : name(s) { };

        ~Vertex();
        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    };

}


#endif //GRAPHS_VERTEX_H
