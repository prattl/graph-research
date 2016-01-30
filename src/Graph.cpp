#include "Graph.h"
#include <memory>
#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <stack>
#include <typeinfo>

using namespace graphs;

Graph::~Graph() {
    std::cout << "Graph destructor called" << "\n";
}

void Graph::printGraph() const {
    std::cout << "Graph:\n";
    for (auto const& node: nodes) {
        std::cout << "\t";
        std::cout << *(node) << "\n";
    }
}

void Graph::addVertex(const std::string label) {
    auto n = std::make_unique<Vertex>(label);
    nodes.push_back(std::move(n));
}

Vertex* Graph::getVertex(const std::string label) const {
    for (const auto& node: nodes) {
        if (node->getLabel() == label) {
            return node.get();
        }
    }
    return nullptr;
}

void Graph::addEdge(const std::string source, const std::string dest) const {
    auto source_vertex = getVertex(source);
    auto dest_vertex = getVertex(dest);
    source_vertex->addNeighbor(*dest_vertex);
//    v2->addNeighbor(*v1);
}

Vertex* Graph::traverseToVertexBfs(const std::string start, const std::string end) {
    auto v1 = getVertex(start);
    auto v2 = getVertex(end);
    return traverseToVertexBfs(*v1, *v2);
}

Vertex* Graph::traverseToVertexBfs(Vertex &start, const Vertex& end) {
    // Traverse the graph from start to end, return the end node if it is found. This will only return the correct
    // shortest path if the graph is non-cyclical.
    prepareTraverse();

    // Store the nodes to be visited next, and the nodes already visited
    std::queue<Vertex*> visit_queue;

    // Start with the root node
    visit_queue.push(&start);

    std::cout << "BFS Traversal from node " << start.getLabel() << " to " << end.getLabel() << ":\n";

    while (!visit_queue.empty()) {
        auto current = visit_queue.front();
        visit_queue.pop();
        if (!current->isVisited()) { // Make sure we haven't visited this node already
            std::cout << "\tVisiting vertex: " << current->getLabel() << "\n";
            if (current->getLabel() == end.getLabel()) {
                return current;
            }
            for (auto& edge: current->edges) {
                auto neighbor = edge->nodes.second;
                std::cout << "\t\tLooking at neighbor " << neighbor->getLabel() << " of node " << current->getLabel() <<".\n";
                if (neighbor->isVisited()) {
                    std::cout << "\t\t\tNeighbor " << neighbor->getLabel() << " is already in the visited set.\n";
                } else {
                    std::cout << "\t\t\tAdding " << neighbor->getLabel() << " to the visit queue.\n";
                    // If it's already in the queue, we'll skip it above after we visit it the first time.
                    neighbor->previous = current;
                    visit_queue.push(neighbor);
                }
            }
            current->visit();
        }
    }
    std::cout << "Could not traverse from " << start.getLabel() << " to " << end.getLabel() << ".\n";
    return NULL;
}

void Graph::prepareTraverse() const {
    // Prepare for a new traversal by marking all nodes as unvisited.
    for (auto& node: nodes) {
        node->unVisit();
        node->previous = nullptr;
    }
}

void Graph::traverseDfsRecursive(const std::string root) {
    prepareTraverse();
    std::cout << "Recursive DFS traversal starting from node " << root << ":\n";
    Vertex* root_node = getVertex(root);
    recursiveDfs(*root_node);
}

void Graph::recursiveDfs(Vertex& node) {
    node.visit();
    std::cout << "\tVisiting node " << node.getLabel() << "\n";
    for (auto& edge: node.edges) {
        auto neighbor = edge->nodes.second;
        if (!neighbor->isVisited()) {
            recursiveDfs(*neighbor);
        }
    }
}

void Graph::traverseDfsIterative(const std::string root) {
    // Results should be the same as recursive DFS except nodes will be visited "right to left"
    prepareTraverse();

    Vertex* root_node = getVertex(root);
    std::stack<Vertex*> s;
    s.push(root_node);

    std::cout << "Iterative DFS traversal starting from node " << root << ":\n";

    while (!s.empty()) {
        auto current_node = s.top();
        s.pop();
        if (!current_node->isVisited()) {
            std::cout << "\tVisiting node " << current_node->getLabel() << "\n";
            current_node->visit();
            for (auto const& edge: current_node->edges) {
                s.push(edge->nodes.second);
            }
        }
    }
}

void Graph::depthLimitedDfs(Vertex& node, int depth) {
    node.visit();
    std::cout << node.getLabel() << " ";
    if (depth == 0) {
        return;
    } else if (depth > 0) {
        for (auto& edge: node.edges) {
            auto neighbor = edge->nodes.second;
            if (!neighbor->isVisited()) {
                depthLimitedDfs(*neighbor, depth - 1);
            }
        }
    }
}

void Graph::traverseDfsIterativeDeepening(const std::string root) {
    auto root_node = getVertex(root);
    std::cout << "Iterative Deepening DFS traversal starting from node " << root << ":\n";
    for (int depth = 0; depth < 8; depth++) {
        prepareTraverse();
        std::cout << "\tDepth " << depth << ": ";
        depthLimitedDfs(*root_node, depth);
        std::cout << "\n";
    }
}