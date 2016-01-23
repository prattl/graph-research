#include "Graph.h"
#include <stdexcept>
#include <queue>
#include <deque>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <stack>

using namespace graphs;

void Vertex::addNeighbor(smartVertexPtr vertex) {
    // Adds the vertex as a neighbor of this vertex only if it is not already a neighbor.
    bool isNeighbor = isNeighborTo(vertex);
    if (!isNeighbor) {
        neighbors.push_back(vertex);
    }
}

bool Vertex::isNeighborTo(smartVertexPtr vertex) {
    // Returns whether this vertex sees the passed vertex as a neighbor. Note: Does not check whether the passed
    // vertex considers this vertex as a neighbor. However it should as long as we are using undirected graphs.
    std::vector<smartVertexPtr>::iterator found;
    found = find(neighbors.begin(), neighbors.end(), vertex);
    return (found != neighbors.end());
}

Vertex::~Vertex() {
    std::cout << "Vertex destructor called for node " << name << "\n";
}

void Graph::printGraph() {
    std::cout << "Graph:\n";
    for (auto const& node: nodes) {
        std::cout << "\t" << *(node) << "\n";
    }
}

void Graph::addVertex(std::string name) {
    // Make sure it doesn't already exist
    smartVertexPtr existing_vertex = getVertex(name);
    if (existing_vertex) {
        throw std::logic_error("Vertex with name " + name + " already exists.");
    }
    smartVertexPtr new_vertex(new Vertex(name));
    nodes.push_back(new_vertex);
}

smartVertexPtr Graph::getVertex(std::string name) {
    for (auto& node: nodes) {
        if (node->name == name) {
            return node;
        }
    }
    return nullptr;
}

void Graph::addEdge(std::string node1, std::string node2) {
    smartVertexPtr v1 = getVertex(node1);
    smartVertexPtr v2 = getVertex(node2);
    v1->addNeighbor(v2);
    v2->addNeighbor(v1);
}

smartVertexPtr Graph::traverseToVertexBfs(std::string start, std::string end) {
    smartVertexPtr v1 = getVertex(start);
    smartVertexPtr v2 = getVertex(end);
    return traverseToVertexBfs(*v1, *v2);
}

smartVertexPtr Graph::traverseToVertexBfs(Vertex &start, Vertex &end) {
    // Traverse the graph from start to end, return the end node if it is found. This will only return the correct
    // shortest path if the graph is non-cyclical.

    // Store the nodes to be visited next, and the nodes already visited
    std::queue<smartVertexPtr> visit_queue;
    std::unordered_set<smartVertexPtr> visited;

    // Start with the root node
    visit_queue.push(smartVertexPtr(&start)); // Copy the smart_ptr

    smartVertexPtr current;

    std::cout << "BFS Traversal from node " << start.name << " to " << end.name << ":\n";

    while (!visit_queue.empty()) {
        current = visit_queue.front();
        visit_queue.pop();
        if (visited.find(current) == visited.end()) { // Make sure we haven't visited this node already
            std::cout << "\tVisiting vertex: " << current->name << "\n";
            if (current->name == end.name) {
                return current;
            }
            for (auto& neighbor: current->neighbors) {
                std::cout << "\t\tLooking at neighbor " << neighbor->name << " of node " << current->name <<".\n";
                if (visited.find(neighbor) != visited.end()) {
                    std::cout << "\t\t\tNeighbor " << neighbor->name << " is already in the visited set.\n";
                } else {
                    std::cout << "\t\t\tAdding " << neighbor->name << " to the visit queue.\n";
                    // If it's already in the queue, we'll skip it above after we visit it the first time.
                    neighbor->previous = current;
                    visit_queue.push(neighbor);
                }
            }
            visited.insert(current);
        }
    }
    std::cout << "Could not traverse from " << start.name << " to " << end.name << ".\n";
    return NULL;
}

void Graph::prepareTraverse() {
    // Prepare for a new traversal by marking all nodes as unvisited.
    for (auto& node: nodes) {
        node->visited = false;
        node->previous = nullptr;
    }
}

void Graph::traverseDfsRecursive(std::string root) {
    prepareTraverse();
    std::cout << "Recursive DFS traversal starting from node " << root << ":\n";
    smartVertexPtr root_node = getVertex(root);
    recursiveDfs(*root_node);
}

void Graph::recursiveDfs(Vertex &node) {
    node.visited = true;
    std::cout << "\tVisiting node " << node.name << "\n";
    for (auto& neighbor: node.neighbors) {
        if (!neighbor->visited) {
            recursiveDfs(*neighbor);
        }
    }
}

void Graph::traverseDfsIterative(std::string root) {
    // Results should be the same as recursive DFS except nodes will be visited "right to left"
    prepareTraverse();

    smartVertexPtr root_node = getVertex(root);
    smartVertexPtr current_node;
    std::stack<smartVertexPtr> s;

    s.push(root_node);
    std::cout << "Iterative DFS traversal starting from node " << root << ":\n";

    while (!s.empty()) {
        current_node = s.top();
        s.pop();
        if (!current_node->visited) {
            std::cout << "\tVisiting node " << current_node->name << "\n";
            current_node->visited = true;
            for (auto& neighbor: current_node->neighbors) {
                s.push(neighbor);
            }
        }
    }
}

void Graph::depthLimitedDfs(Vertex& node, int depth) {
    node.visited = true;
    std::cout << node.name << " ";
    if (depth == 0) {
        return;
    } else if (depth > 0) {
        for (auto& neighbor: node.neighbors) {
            if (!neighbor->visited) {
                depthLimitedDfs(*neighbor, depth - 1);
            }
        }
    }
}

void Graph::traverseDfsIterativeDeepening(std::string root) {
    smartVertexPtr root_node = getVertex(root);
    std::cout << "Iterative Deepening DFS traversal starting from node " << root << ":\n";
    for (int depth = 0; depth < 8; depth++) {
        prepareTraverse();
        std::cout << "\tDepth " << depth << ": ";
        depthLimitedDfs(*root_node, depth);
        std::cout << "\n";
    }
}