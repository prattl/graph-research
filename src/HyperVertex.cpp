#include "HyperVertex.h"
#include <memory>
#include <iostream>


using namespace hypergraphs;

struct HyperVertex::HyperVertexData {
    std::string uuid;
    std::string label;
    bool visited;
};

namespace hypergraphs {
    std::ostream &operator<<(std::ostream &strm, const HyperVertex &hv) {
        std::string sources, destinations;
        for (auto const& source: hv.sourceEdges) {
            sources += source.getLabel() + ", ";
        }
        sources = sources.substr(0, sources.length() - 2);
        for (auto const& destination: hv.destinationEdges) {
            destinations += destination.getLabel() + ", ";
        }
        destinations = destinations.substr(0, destinations.length() - 2);
        return strm << "HyperVertex: " << hv.getLabel()
               << " (source hyperedges: " << sources << ")"
               << " (destination hyperedges: " << destinations << ")";
    }
}

HyperVertex::HyperVertex() :
        data(std::make_unique<HyperVertexData>(HyperVertexData{"", ""})) {};

HyperVertex::HyperVertex(std::string label) :
        data(std::make_unique<HyperVertexData>(HyperVertexData{"", label})) {};

HyperVertex::~HyperVertex() = default;

std::string HyperVertex::getLabel() const {
    return data->label;
}