#include "Hypergraph.h"
//#include "Graph.h"
#include <iostream>
#include <algorithm>

using namespace hypergraphs;

bool HyperEdge::isVertexInEdge(graphs::smartVertexPtr vertex) {
    // Pass the smartVertexPtr by value so that a copy operation is forced to make sure the vertex won't be deleted
    // after it goes out of scope within the context of this method.
    std::vector<graphs::smartVertexPtr>::iterator found;
    found = find(nodes.begin(), nodes.end(), vertex);
    return (found != nodes.end());
}

void HyperEdge::addVertex(graphs::smartVertexPtr vertex) {
    // Adds the new vertex to this edge. Checks to see if it already is in the edge, and adds it as a neighbor to
    // all existing nodes in this edge and adds those nodes as neighbors to the new node.
    if (isVertexInEdge(vertex)) {
        throw std::logic_error("Vertex with name " + vertex->name + " is already in edge" + name + ".");
    }

    for (auto const& node: nodes) {
        node->addNeighbor(vertex);
        vertex->addNeighbor(node);
    }

    nodes.push_back(vertex);
}

void HyperGraph::printGraph() {
    graphs::Graph::printGraph();
    for (auto const& edge: edges) {
        std::cout << "\t" << *(edge) << "\n";
    }
}

void HyperGraph::addVertex(std::string name) {
    graphs::Graph::addVertex(name);
}

void HyperGraph::addEdge(std::string name) {
    // Make sure it doesn't already exist
    smartEdgePtr existing_edge = getEdge(name);
    if (existing_edge) {
        throw std::logic_error("Edge with name " + name + " already exists.");
    }
    smartEdgePtr new_edge(new HyperEdge(name));
    edges.push_back(new_edge);
}

smartEdgePtr HyperGraph::getEdge(std::string name) {
    for (auto& edge: edges) {
        if (edge->name == name) {
            return edge;
        }
    }
    return nullptr;
}

void HyperGraph::connectVertexToEdge(std::string vertex_name, std::string edge_name) {
    graphs::smartVertexPtr vertex = graphs::Graph::getVertex(vertex_name);
    if (!vertex) {
        throw std::logic_error("Vertex with name " + vertex_name + " does not exist.");
    }

    smartEdgePtr edge = getEdge(edge_name);
    if (!edge) {
        throw std::logic_error("Edge with name " + edge_name + " does not exist.");
    }

    edge->addVertex(vertex);
}