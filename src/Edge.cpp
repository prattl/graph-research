#include "Edge.h"
#include "Vertex.h"

using namespace graphs;

struct Edge::EdgeData {
    std::string uuid;
    std::string label;
    int weight;
};

Edge::Edge(Vertex& source, Vertex& dest) {
    auto newData = EdgeData{"", "", 0};
    data = std::make_unique<EdgeData>(std::move(newData));
    from = &source;
    to = &dest;
    nodes = std::pair<Vertex*, Vertex*>(&source, &dest);
}

Edge::Edge(Vertex& source, Vertex& dest, std::string label) {
    auto newData = EdgeData{"", label, 0};
    data = std::make_unique<EdgeData>(std::move(newData));
    from = &source;
    to = &dest;
    nodes = std::pair<Vertex*, Vertex*>(&source, &dest);
}

Edge::Edge(Vertex& source, Vertex& dest, std::string label, int weight) {
    auto newData = EdgeData{"", label, weight};
    data = std::make_unique<EdgeData>(std::move(newData));
    from = &source;
    to = &dest;
    nodes = std::pair<Vertex*, Vertex*>(&source, &dest);
}

Edge::~Edge() = default;