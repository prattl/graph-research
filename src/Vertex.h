#ifndef GRAPHS_VERTEX_H
#define GRAPHS_VERTEX_H

#include <vector>
#include <iostream>
#include <memory>

namespace graphs {
    class Vertex {
        struct VertexData;
        std::unique_ptr<VertexData> data;
    public:
        std::vector<Vertex*> neighbors;
        Vertex* previous;  // Used during traversal

        void visit();
        void unVisit();
        bool isVisited();

        std::string getLabel();
        void addNeighbor(Vertex&);
        bool isNeighborTo(const Vertex&);

        Vertex(const std::string);
        ~Vertex();
        Vertex(const Vertex&);
        Vertex& operator=(const Vertex&);

        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    };

}


#endif //GRAPHS_VERTEX_H
