#include "Hypergraph.h"
#include <iostream>
#include <algorithm>
#include <queue>

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

graphs::smartVertexPtr HyperGraph::traverseToVertexBfs(std::string start_name, std::string end_name) {
    return graphs::Graph::traverseToVertexBfs(start_name, end_name);
}


void HyperGraph::traverseBfs(std::string root_name) {
    graphs::smartVertexPtr root_node = getVertex(root_name);
    traverseBfs(root_node);
}

void HyperGraph::traverseBfs(graphs::smartVertexPtr root) {
    // Traverse the entire graph until all nodes have been visited.
    graphs::Graph::prepareTraverse();
    std::queue<graphs::smartVertexPtr> visit_queue;

    std::cout << "Hypergraph BFS traversal starting from node " << root->name << ":\n";

    visit_queue.push(root);
    graphs::smartVertexPtr current;

    while (!visit_queue.empty()) {
        current = visit_queue.front();
        visit_queue.pop();

        if (!current->visited) {
            std::cout << "\tVisiting vertex: " << current->name << "\n";

            for (auto& neighbor: current->neighbors) {
                std::cout << "\t\tLooking at neighbor " << neighbor->name << " of node " << current->name <<".\n";
                if (neighbor->visited) {
                    std::cout << "\t\t\tNeighbor " << neighbor->name << " has already been visited.\n";
                } else {
                    std::cout << "\t\t\tAdding " << neighbor->name << " to the visit queue.\n";
                    // If it's already in the queue, we'll skip it above after we visit it the first time.
                    neighbor->previous = current;
                    visit_queue.push(neighbor);
                }
            }
            current->visited = true;
        }
    }
}

void HyperGraph::traverseDfsRecursive(std::string root_name) {
    graphs::Graph::traverseDfsRecursive(root_name);
}
