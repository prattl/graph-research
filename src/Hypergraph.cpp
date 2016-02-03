#include "Hypergraph.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace hypergraphs;

HyperGraph::~HyperGraph() {
    std::cout << "HyperGraph destructor called for object at " << this << "\n";
}

void HyperGraph::printGraph() const {
    std::cout << "Hyper";
    graphs::Graph::printGraph();
    for (const auto& edge: edges) {
        std::cout << "\t" << (*edge) << "\n";
    }
}

void HyperGraph::addVertex(std::string name) {
    graphs::Graph::addVertex(name);
}

void HyperGraph::addEdge(std::string name) {
    smartEdgePtr newEdge = std::make_unique<HyperEdge>(name);
    edges.push_back(std::move(newEdge));
}

HyperEdge* HyperGraph::getEdge(std::string name) {
    for (const auto& edge: edges) {
        if (edge->getLabel() == name) {
            return edge.get();
        }
    }
    return nullptr;
}

void HyperGraph::addVertexToEdge(std::string vertex_name, std::string edge_name) {
    // Add the given vertex as a member of the given edge
    graphs::Vertex* vertex = graphs::Graph::getVertex(vertex_name);
    HyperEdge* edge = getEdge(edge_name);
    edge->addNode(*vertex);
}

void HyperGraph::addEdgeToVertex(std::string edge_name, std::string vertex_name) {
    // Mark the given vertex as belonging to the given edge
    graphs::Vertex* vertex = graphs::Graph::getVertex(vertex_name);
    HyperEdge* edge = getEdge(edge_name);
    // TODO: Derive HyperEdge from Edge
//    vertex->addEdge(*edge);
}

graphs::Vertex* HyperGraph::traverseToVertexBfs(std::string start_name, std::string end_name) {
    return graphs::Graph::traverseToVertexBfs(start_name, end_name);
}


//void HyperGraph::traverseBfs(std::string root_name) {
//    graphs::smartVertexPtr root_node = getVertex(root_name);
//    traverseBfs(root_node);
//}

//void HyperGraph::traverseBfs(graphs::Vertex& root) {
//    // Traverse the entire graph until all nodes have been visited.
//    graphs::Graph::prepareTraverse();
//    std::queue<graphs::Vertex*> visit_queue;
//
//    std::cout << "Hypergraph BFS traversal starting from node " << root->name << ":\n";
//
//    visit_queue.push(&root);
//
//    while (!visit_queue.empty()) {
//        auto current = visit_queue.front();
//        visit_queue.pop();
//
//        if (!current->visited) {
//            std::cout << "\tVisiting vertex: " << current->name << "\n";
//
//            for (auto& neighbor: current->neighbors) {
//                std::cout << "\t\tLooking at neighbor " << neighbor->name << " of node " << current->name <<".\n";
//                if (neighbor->visited) {
//                    std::cout << "\t\t\tNeighbor " << neighbor->name << " has already been visited.\n";
//                } else {
//                    std::cout << "\t\t\tAdding " << neighbor->name << " to the visit queue.\n";
//                    // If it's already in the queue, we'll skip it above after we visit it the first time.
//                    neighbor->previous = current;
//                    visit_queue.push(neighbor);
//                }
//            }
//            current->visited = true;
//        }
//    }
//}

void HyperGraph::traverseDfsRecursive(std::string root_name) {
    graphs::Graph::traverseDfsRecursive(root_name);
}
