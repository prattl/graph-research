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
        std::string name;
        std::vector<Vertex*> neighbors;
        Vertex* previous;  // Used during traversal

        bool visited;
        void addNeighbor(Vertex&);
        bool isNeighborTo(Vertex const&);

//        Vertex();
        Vertex(std::string s);
        ~Vertex();

//        Vertex(const Vertex& rhs);
//        Vertex& operator=(const Vertex& rhs);

        friend std::ostream& operator<<(std::ostream&, const Vertex&);
    };

}


#endif //GRAPHS_VERTEX_H
