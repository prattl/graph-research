#include "HyperEdge.h"
#include <iostream>
#include "Vertex.h"

using namespace hypergraphs;

struct HyperEdge::EdgeData {
    std::string uuid;
    std::string label;
    int weight;
};

namespace hypergraphs {
    std::ostream &operator<<(std::ostream &strm, const HyperEdge &he) {
        std::string nodes_str;
        for (const auto& node: he.nodes) {
            nodes_str += (*node).getLabel() + ", ";
        }
        nodes_str = nodes_str.substr(0, nodes_str.length() - 2);
        return strm << "Edge: " << he.data->label << " (nodes: " << nodes_str << ")";
    }
}

void HyperEdge::init(std::string label, int weight) {
    auto newData = EdgeData{"", label, weight};
    data = std::make_unique<EdgeData>(std::move(newData));
}

HyperEdge::HyperEdge() {
    init("", 0);
}

HyperEdge::HyperEdge(std::string label) {
    init(label, 0);
}

HyperEdge::HyperEdge(std::string label, int weight) {
    init(label, weight);
}

HyperEdge::~HyperEdge() = default;


// Not used yet but this is how it would be implemented
HyperEdge::HyperEdge(const HyperEdge& rhs) : data(nullptr) {
    std::cout << "Copy constructor called for " << data->label << " with rhs " << rhs.data->label << "\n";
    if (rhs.data) {
        data = std::make_unique<EdgeData>(*rhs.data);
    }
}

// Not used yet but this is how it would be implemented
HyperEdge& HyperEdge::operator=(const HyperEdge& rhs) {
    std::cout << "Assignment operator called for " << data->label << " with rhs " << rhs.data->label << "\n";
    if (rhs.data) data.reset();
    else if (!data) data = std::make_unique<EdgeData>(*rhs.data);
    else *data = *rhs.data;

    return *this;
}

void HyperEdge::addNode(graphs::Vertex& newNode) {
    // For now add nodes without direction - retroactively make old nodes neighbors of newly added nodes
    // TODO: What does it mean for a hypergraph to be directed?
    for (auto& node: nodes) {
        if (!node->isNeighborTo(newNode)) {
            node->addNeighbor(newNode);
        }
        if (!newNode.isNeighborTo(*node)) {
            newNode.addNeighbor(*node);
        }
    }
    nodes.push_back(&newNode);
}

std::string HyperEdge::getLabel() const {
    return data->label;
}