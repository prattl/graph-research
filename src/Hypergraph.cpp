#include "Hypergraph.h"
#include <iostream>
#include <algorithm>
#include <queue>

using namespace hypergraphs;

HyperGraph::~HyperGraph() {
    std::cout << "HyperGraph destructor called for object at " << this << "\n";
}

void HyperGraph::printGraph() const {
    std::cout << "HyperGraph:\n\tNodes:\n";
    for (const auto& node: nodes) {
        std::cout << "\t\t" << (*node) << "\n";
    }
    std::cout << "\tEdges:\n";
    for (const auto& edge: edges) {
        std::cout << "\t\t" << (*edge) << "\n";
    }
}

void HyperGraph::addVertex(std::string label) {
    nodes.push_back(std::make_unique<HyperVertex>(label));
}

void HyperGraph::addEdge(std::string label) {
    edges.push_back(std::make_unique<HyperEdge>(label));
}



HyperEdge* HyperGraph::getEdge(std::string label) const {
    for (const auto& edge: edges) {
        if (edge->getLabel() == label) {
            return edge.get();
        }
    }
    return nullptr;
}

HyperVertex* HyperGraph::getVertex(std::string label) const {
    for (const auto& node: nodes) {
        if (node->getLabel() == label) {
            return node.get();
        }
    }
    return nullptr;
}

void HyperGraph::connectVertices(std::string sourceVertexLabel, std::string destinationVertexLabel, std::string edgeLabel) {
    HyperVertex* sourceVertex = getVertex(sourceVertexLabel);
    HyperVertex* destinationVertex = getVertex(destinationVertexLabel);
    HyperEdge* edge = getEdge(edgeLabel);

    sourceVertex->addDestinationEdge(*edge);
    edge->addSourceVertex(*sourceVertex);
    edge->addDestinationVertex(*destinationVertex);
    destinationVertex->addSourceEdge(*edge);

}

//void HyperGraph::addVertexToEdge(std::string vertex_label, std::string edge_label) {
//    // Add the given vertex as a member of the given edge
//    HyperVertex* vertex = getVertex(vertex_label);
//    HyperEdge* edge = getEdge(edge_label);
//    edge->addNode(*vertex);
//}

//void HyperGraph::addEdgeToVertex(std::string edge_label, std::string vertex_label) {
//    // Mark the given vertex as belonging to the given edge
//    graphs::Vertex* vertex = graphs::Graph::getVertex(vertex_label);
//    HyperEdge* edge = getEdge(edge_label);
//    // TODO: Derive HyperEdge from Edge
////    vertex->addEdge(*edge);
//}

//graphs::Vertex* HyperGraph::traverseToVertexBfs(std::string start_label, std::string end_label) {
//    return graphs::Graph::traverseToVertexBfs(start_label, end_label);
//}


//void HyperGraph::traverseBfs(std::string root_label) {
//    graphs::smartVertexPtr root_node = getVertex(root_label);
//    traverseBfs(root_node);
//}

//void HyperGraph::traverseBfs(graphs::Vertex& root) {
//    // Traverse the entire graph until all nodes have been visited.
//    graphs::Graph::prepareTraverse();
//    std::queue<graphs::Vertex*> visit_queue;
//
//    std::cout << "Hypergraph BFS traversal starting from node " << root->label << ":\n";
//
//    visit_queue.push(&root);
//
//    while (!visit_queue.empty()) {
//        auto current = visit_queue.front();
//        visit_queue.pop();
//
//        if (!current->visited) {
//            std::cout << "\tVisiting vertex: " << current->label << "\n";
//
//            for (auto& neighbor: current->neighbors) {
//                std::cout << "\t\tLooking at neighbor " << neighbor->label << " of node " << current->label <<".\n";
//                if (neighbor->visited) {
//                    std::cout << "\t\t\tNeighbor " << neighbor->label << " has already been visited.\n";
//                } else {
//                    std::cout << "\t\t\tAdding " << neighbor->label << " to the visit queue.\n";
//                    // If it's already in the queue, we'll skip it above after we visit it the first time.
//                    neighbor->previous = current;
//                    visit_queue.push(neighbor);
//                }
//            }
//            current->visited = true;
//        }
//    }
//}

//void HyperGraph::traverseDfsRecursive(std::string root_label) {
//    graphs::Graph::traverseDfsRecursive(root_label);
//}
