#include "Edge.h"
#include "Vertex.h"

using namespace graphs;

struct Edge::EdgeData {
    std::string uuid;
    std::string label;
    int weight;
};

Edge::Edge(Vertex& source, Vertex& dest) :
        data(std::make_unique<EdgeData>(EdgeData{"", "", 0})) {};

Edge::Edge(Vertex& source, Vertex& dest, std::string label) :
        data(std::make_unique<EdgeData>(EdgeData{"", label, 0})) {};

Edge::Edge(Vertex& source, Vertex& dest, std::string label, int weight) :
        data(std::make_unique<EdgeData>(EdgeData{"", label, weight})) {};

Edge::~Edge() = default;

Vertex* Edge::sourceNode() const {
    return nodes.first;
}

Vertex* Edge::destNode() const {
    return nodes.second;
}