#include "Edge.h"
#include "Vertex.h"

using namespace graphs;

struct Edge::EdgeData {
    std::string uuid;
    std::string label;
    int weight;
};

void Edge::init(Vertex& source, Vertex& dest, std::string label, int weight) {
    auto newData = EdgeData{"", label, weight};
    data = std::make_unique<EdgeData>(std::move(newData));
    nodes = std::pair<Vertex*, Vertex*>(&source, &dest);
}

Edge::Edge(Vertex& source, Vertex& dest) {
    init(source, dest, "", 0);
}

Edge::Edge(Vertex& source, Vertex& dest, std::string label) {
    init(source, dest, label, 0);
}

Edge::Edge(Vertex& source, Vertex& dest, std::string label, int weight) {
    init(source, dest, label, weight);
}

Edge::~Edge() = default;

Vertex* Edge::sourceNode() const {
    return nodes.first;
}

Vertex* Edge::destNode() const {
    return nodes.second;
}