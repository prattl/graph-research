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

void Vertex::addNeighbor(Vertex* vertex) {
    // Adds the vertex as a neighbor of this vertex only if it is not already a neighbor.
    bool isNeighbor = isNeighborTo(vertex);
    if (!isNeighbor) {
        neighbors.push_back(vertex);
    }
}

bool Vertex::isNeighborTo(Vertex* vertex) {
    // Returns whether this vertex sees the passed vertex as a neighbor. Note: Does not check whether the passed
    // vertex considers this vertex as a neighbor. However it should as long as we are using undirected graphs.
//    std::vector<Vertex*>::iterator found;
    auto found = find(neighbors.begin(), neighbors.end(), vertex);
    return (found != neighbors.end());
}

Vertex::~Vertex() {
    std::cout << "Vertex destructor called for node " << name << "\n";
}