#include "Vertex.h"
#include "Graph.h"
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace graphs;

namespace graphs {
    std::ostream &operator<<(std::ostream &strm, const Vertex &v) {
        std::string neighbors;
        for (auto const &neighbor: v.neighbors) {
            neighbors += neighbor->name + ", ";
        }
        neighbors = neighbors.substr(0, neighbors.length() - 2);
        return strm << "Vertex: " << v.name << " (neighbors: " << neighbors << ")";
    }
}

struct Vertex::VertexData {
    std::string uuid;
    std::string label;
};

//Vertex::Vertex() {
//    auto newData = VertexData{"", "", 0};
//    data = std::make_unique<VertexData>(std::move(newData));
//};

Vertex::Vertex(std::string s) {
    name = s;
    auto newData = VertexData{"", s};
    data = std::make_unique<VertexData>(std::move(newData));
};

Vertex::~Vertex() = default;

void Vertex::addNeighbor(Vertex& vertex) {
    // Adds the vertex as a neighbor of this vertex only if it is not already a neighbor.
    bool isNeighbor = isNeighborTo(vertex);
    std::cout << "Is neighbor: " << isNeighbor << "\n";
    if (!isNeighbor) {
        neighbors.push_back(&vertex);
    }
}

bool Vertex::isNeighborTo(Vertex const& vertex) {
    // Returns whether this vertex sees the passed vertex as a neighbor. Note: Does not check whether the passed
    // vertex considers this vertex as a neighbor. However it should as long as we are using undirected graphs.
//    std::vector<Vertex*>::iterator found;
    std::cout << "Checking if vertex " << vertex.name << " is neighbor to " << name << "\n";
    for (auto const& neighbor: neighbors) {
//        std::cout << "Loop\n";
        if (neighbor->name == vertex.name) {
            std::cout << "Returning true\n";
            return true;
        }
    }
    std::cout << "Returning false\n";
    return false;
//    auto found = find(neighbors.begin(), neighbors.end(), vertex);
//    bool isFound = found != neighbors.end();
//    std::cout << "isFound: " << isFound << "\n";
//    return (found != neighbors.end());
}