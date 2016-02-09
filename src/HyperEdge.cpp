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
        std::string sources, destinations;
        for (auto const& source: he.sourceNodes) {
            sources += source->getLabel() + ", ";
        }
        sources = sources.substr(0, sources.length() - 2);
        for (auto const& destination: he.destinationNodes) {
            destinations += destination->getLabel() + ", ";
        }
        destinations = destinations.substr(0, destinations.length() - 2);
        return strm << "HyperEdge: " << he.getLabel()
               << " (source hypervertices: " << sources << ")"
               << " (destination hypervertices: " << destinations << ")";
    }
}

HyperEdge::HyperEdge() :
    data(std::make_unique<EdgeData>(EdgeData{"", "", 0})) {};

HyperEdge::HyperEdge(std::string label) :
    data(std::make_unique<EdgeData>(EdgeData{"", label, 0})) {};

HyperEdge::HyperEdge(std::string label, int weight) :
    data(std::make_unique<EdgeData>(EdgeData{"", label, weight})) {};

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

//void HyperEdge::addNode(graphs::Vertex& newNode) {
//    for (auto& node: nodes) {
//        if (!node->isNeighborTo(newNode)) {
//            node->addNeighbor(newNode);
//        }
//        if (!newNode.isNeighborTo(*node)) {
//            newNode.addNeighbor(*node);
//        }
//    }
//    nodes.push_back(&newNode);
//}

std::string HyperEdge::getLabel() const {
    return data->label;
}

void HyperEdge::addSourceVertex(HyperVertex& sourceVertex) {
    bool found = false;
    for (const auto& node: sourceNodes) {
        if (node->getLabel() == sourceVertex.getLabel()) {
            found = true;
        }
    }
    if (!found) {
        sourceNodes.push_back(&sourceVertex);
    }
}

void HyperEdge::addDestinationVertex(HyperVertex& destinationVertex) {
    bool found = false;
    for (const auto& node: destinationNodes) {
        if (node->getLabel() == destinationVertex.getLabel()) {
            found = true;
        }
    }
    if (!found) {
        destinationNodes.push_back(&destinationVertex);
    }}