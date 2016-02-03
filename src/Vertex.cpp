#include "Vertex.h"
#include "Graph.h"
#include <queue>
#include <unordered_set>
#include <algorithm>

using namespace graphs;

struct Vertex::VertexData {
    std::string uuid;
    std::string label;
    bool visited;
};

namespace graphs {
    std::ostream &operator<<(std::ostream &strm, const Vertex &v) {
        std::string neighborString;
        for (auto const& neighbor: v.neighbors) {
            neighborString += neighbor->getLabel() + ", ";
        }
//        for (auto const& edge: v.edges) {
//            auto neighbor = edge->destNode();
//            neighbors += neighbor->data->label + ", ";
//        }
        neighborString = neighborString.substr(0, neighborString.length() - 2);
        return strm << "Vertex: " << v.data->label << " (neighbors: " << neighborString << ")";
    }
}

Vertex::Vertex(const std::string s) {
    auto newData = VertexData{"", s};
    data = std::make_unique<VertexData>(std::move(newData));
};

Vertex::~Vertex() = default;

// Not used yet but this is how it would be implemented
Vertex::Vertex(const Vertex& rhs) : data(nullptr) {
    std::cout << "Copy constructor called for " << data->label << " with rhs " << rhs.data->label << "\n";
    if (rhs.data) {
        data = std::make_unique<VertexData>(*rhs.data);
    }
}

// Not used yet but this is how it would be implemented
Vertex& Vertex::operator=(const Vertex& rhs) {
    std::cout << "Assignment operator called for " << data->label << " with rhs " << rhs.data->label << "\n";
    if (rhs.data) data.reset();
    else if (!data) data = std::make_unique<VertexData>(*rhs.data);
    else *data = *rhs.data;

    return *this;
}

void Vertex::visit() const {
    data->visited = true;
}

void Vertex::unVisit() const {
    data->visited = false;
}

bool Vertex::isVisited() const {
    return data->visited;
}

std::string Vertex::getLabel() const {
    return data->label;
}

void Vertex::addNeighbor(Vertex& vertex) {
//    auto newEdge = std::make_unique<Edge>((*this), vertex);
//    edges.push_back(std::move(newEdge));
    neighbors.push_back(&vertex);
}

bool Vertex::isNeighborTo(const Vertex& vertex) const {
    // Returns whether this vertex sees the passed vertex as a neighbor. Note: Does not check whether the passed
    // vertex considers this vertex as a neighbor. However it should if the graph is undirected.
    std::cout << "Checking if vertex " << data->label << " sees vertex " << vertex.data->label << " as a neighbor\n";
    for (auto const& neighbor: neighbors) {
        if (neighbor->getLabel() == vertex.getLabel()) {
            std::cout << "Returning true\n";
            return true;
        }
    }
//    for (auto const& edge: edges) {
//        if (edge->destNode()->data->label == vertex.data->label) {
//            std::cout << "Returning true\n";
//            return true;
//        }
//    }
    std::cout << "Returning false\n";
    return false;
}

//void Vertex::addEdge(const Edge& edge) {
//    edges.push_back(edge);
//}

//std::vector<Vertex*> Vertex::getNeighbors() const {
//    std::vector<Vertex*> neighbors;
//    for (auto const& edge: edges) {
//        neighbors.push_back(edge->destNode());
//    }
//    return neighbors; // This should be fast because of return value optimization
//}