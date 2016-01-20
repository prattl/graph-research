#include "Graph.h"
#include <stdexcept>
#include <queue>
#include <deque>
#include <unordered_set>
#include <limits>

std::ostream& operator<<(std::ostream &strm, const Vertex &v) {
    std::string neighbors;
    for (auto const& neighbor: v.neighbors) {
        neighbors += neighbor->name + ", ";
    }
    neighbors = neighbors.substr(0, neighbors.length() - 2);
    return strm << "Vertex: " << v.name << " (neighbors: " << neighbors << ")";
}

void Graph::printGraph() {
    std::cout << "Graph:\n";
    for (auto const& node: nodes) {
        std::cout << "\t" << *(node) << "\n";
    }
}

void Graph::addVertex(std::string name) {
    // Make sure it doesn't already exist
    Vertex* existing_vertex = getVertex(name);
    if (existing_vertex) {
        throw std::logic_error("Vertex with name " + name + " already exists.");
    }
    Vertex* new_vertex = new Vertex();
    (*new_vertex).name = name;
    nodes.push_back(new_vertex);
}

Vertex* Graph::getVertex(std::string name) {
    for (auto const& node: nodes) {
        if (node->name == name) {
            return node;
        }
    }
    return NULL;
}

void Graph::addEdge(std::string node1, std::string node2) {
    Vertex *v1 = getVertex(node1);
    Vertex *v2 = getVertex(node2);
    v1->neighbors.push_back(v2);
    v2->neighbors.push_back(v1);
}

Vertex* Graph::traverseToVertexBfs(std::string start, std::string end) {
    Vertex* v1 = getVertex(start);
    Vertex* v2 = getVertex(end);
    return traverseToVertexBfs(*v1, *v2);
}

Vertex* Graph::traverseToVertexBfs(Vertex &start, Vertex &end) {
    // Traverse the graph from start to end, return the end node if it is found.
    // Store the nodes to be visited next, and the nodes already visited
    std::queue<Vertex*> visit_queue;
    std::unordered_set<Vertex*> visited;

    // Start with the root node
    visit_queue.push(&start);

    Vertex* current;
    int num_visit_queue = 0;

    while (!visit_queue.empty() && num_visit_queue < 100) {
        num_visit_queue++;
        current = visit_queue.front();
        visit_queue.pop();
        if (visited.find(current) == visited.end()) {
            std::cout << "Visiting vertex: " << current->name << "\n";
            if (current->name == end.name) {
                return current;
            }
            for (auto const& neighbor: current->neighbors) {
                std::cout << "\tLooking at neighbor " << neighbor->name << " of node " << current->name <<".\n";
                if (visited.find(neighbor) != visited.end()) {
                    std::cout << "\t\tNeighbor " << neighbor->name << " is already in the visited set.\n";
                } else {
                    std::cout << "\t\tAdding " << neighbor->name << " to the visit queue.\n";
                    // If it's already in the queue, we'll catch it after we visit it the first time.
                    visit_queue.push(neighbor);
                }
            }
            visited.insert(current);
        }
    }
    std::cout << "Could not traverse from " << start.name << " to " << end.name << ".\n";
    return NULL;
}

int Graph::findShortestPath(Vertex &start, Vertex &end) {
    // Find the shortest path from start to end, returning the length of the path.
    std::deque<Vertex*> visit_queue;

    for (auto const& vertex: nodes) {
        vertex->distance = std::numeric_limits<int>::max();
        vertex->previous = NULL;
        visit_queue.push_back(vertex);
    }

    start.distance = 0;

    while (!visit_queue.empty()) {
        // Find vertex in visit_queue with smallest distance
        Vertex* closest_node;
        int smallest_distance = std::numeric_limits<int>::max();
        for (auto const& vertex: visit_queue) {
            if (vertex->distance < smallest_distance) {
                smallest_distance = vertex->distance;
                closest_node = vertex;
            }
        }

        // TODO: Remove closest_node from visit_queue
//        visit_queue.erase(closest_node);

        // TODO: For each neighbor of closest_node (that is still in visit_queue):
        // TODO:    Find alternate distance by incrementing closest_node's distance by 1 (since we're not using a weighted graph)
        // TODO:    If alternate distance < neighbor's distance:
        // TODO:        Set neighbor's distance to alternate distance
        // TODO:        Set neighbor's previous to closest_node

    }
}