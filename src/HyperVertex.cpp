#include "HyperVertex.h"
#include <memory>
#include <iostream>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace hypergraphs;

struct HyperVertex::HyperVertexData {
    boost::uuids::uuid uuid;
    std::string label;
    bool visited;
};

namespace hypergraphs {
    std::ostream &operator<<(std::ostream &strm, const HyperVertex &hv) {
        std::string sources, destinations;
        for (auto const& source: hv.sourceEdges) {
            sources += source->getLabel() + ", ";
        }
        sources = sources.substr(0, sources.length() - 2);
        for (auto const& destination: hv.destinationEdges) {
            destinations += destination->getLabel() + ", ";
        }
        destinations = destinations.substr(0, destinations.length() - 2);
        return strm << "HyperVertex (" << hv.data->uuid << "): " << hv.getLabel()
               << " (source hyperedges: " << sources << ")"
               << " (destination hyperedges: " << destinations << ")";
    }
}

HyperVertex::HyperVertex() :
        data(std::make_unique<HyperVertexData>(HyperVertexData{boost::uuids::random_generator()(), ""})) {};

HyperVertex::HyperVertex(std::string label) :
        data(std::make_unique<HyperVertexData>(HyperVertexData{boost::uuids::random_generator()(), label})) {};

HyperVertex::~HyperVertex() = default;

void HyperVertex::visit() const {
    data->visited = true;
}

void HyperVertex::unVisit() const {
    data->visited = false;
}

bool HyperVertex::isVisited() const {
    return data->visited;
}

std::string HyperVertex::getLabel() const {
    return data->label;
}

void HyperVertex::addSourceEdge(HyperEdge& edge) {
    bool found = false;
    for (const auto& destinationEdge: sourceEdges) {
        if (destinationEdge->getLabel() == edge.getLabel()) {
            found = true;
        }
    }
    if (!found) {
        sourceEdges.push_back(&edge);
    }
}

void HyperVertex::addDestinationEdge(HyperEdge& edge) {
    bool found = false;
    for (const auto& sourceEdge: destinationEdges) {
        if (sourceEdge->getLabel() == edge.getLabel()) {
            found = true;
        }
    }
    if (!found) {
        destinationEdges.push_back(&edge);
    }
}