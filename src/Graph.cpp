#include "Graph.h"
#include <memory>
#include <queue>
#include <unordered_set>
#include <limits>
#include <algorithm>
#include <stack>

using namespace graphs;

Graph::~Graph() {
    std::cout << "Graph destructor called for object at " << this << "\n";
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

void Graph::addEdge(const std::string source, const std::string dest) {
    auto source_vertex = getVertex(source);
    auto dest_vertex = getVertex(dest);
    source_vertex->addNeighbor(*dest_vertex);
    auto newEdge = std::make_unique<Edge>(*source_vertex, *dest_vertex);
    edges.push_back(std::move(newEdge));
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
//            for (auto& edge: current->edges) {
            for (auto& neighbor: current->neighbors) {
//                auto neighbor = edge->destNode();
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
//    for (auto& edge: node.edges) {
    for (auto& neighbor: node.neighbors) {
//        auto neighbor = edge->destNode();
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
//            for (auto const& edge: current_node->edges) {
            for (auto const& neighbor: current_node->neighbors) {
//                s.push(edge->destNode());
                s.push(neighbor);
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
//        for (auto& edge: node.edges) {
        for (auto& neighbor: node.neighbors) {
//            auto neighbor = edge->destNode();
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

int Graph::getVertexInDegree(const Vertex& vertex) const {
    // Returns the vertex's in degree
    int degree = 0;
    for (const auto& node: nodes) {
        if (node->isNeighborTo(vertex)) {
            degree++;
        }
    }
    return degree;
}

int Graph::getVertexOutDegree(const Vertex& vertex) const {
    return (int)vertex.neighbors.size();
}

Triangle Graph::findTriangle() const {
    // Returns the first found triangle in the graph, or an empty triangle if no triangles were found.
    for (const auto& node: nodes) {
        if (node->neighbors.size() >= 2) {
            for (const auto& neighbor: node->neighbors) {
                // See if 2 of node's neighbors are neighbors of each other.
                for (const auto& neighbor2: neighbor->neighbors) {
                    // Don't look at the original node
                    if (neighbor2->getLabel() != node->getLabel()) {
                        if (neighbor2->isNeighborTo(*neighbor) && node->isNeighborTo(*neighbor2)) {
                            // Found a triangle: node has 2 neighbors who are neighbors to each other.
                            std::cout << "Found triangle: " << node->getLabel() << " " << neighbor->getLabel()
                                << " " << neighbor2->getLabel() << "\n";
                            return Triangle((node.get()), neighbor, neighbor2);
                        }
                    }
                }
            }
        }
    }
    return Triangle(nullptr, nullptr, nullptr);
}

AdjacencyMatrix Graph::buildAdjacencyMatrix() {
    // Builds an adjacency matrix for use in the Ullman algorithm
    AdjacencyMatrix adjMatrix;
    for (const auto& node: nodes) {
        std::vector<int> row;
        for (int i = 0; i < nodes.size(); i++) {
            Vertex* element = nodes[i].get();
            if (node->isNeighborTo(*element)) {
                row.push_back(1);
            } else {
                row.push_back(0);
            }
        }
        adjMatrix.push_back(row);
    }
    return adjMatrix; // Returning this shouldn't be slow because of return value optimization
}

vertexList Graph::findIsomorphism(Graph& query) {
    std::cout << "findIsomorphism()\n";
    vertexList assignments;
    if (isomorphismSearch(query, assignments)) {
        return assignments;
    }

    return assignments;
}

bool Graph::isomorphismSearch(Graph& query, vertexList& assignments) {
    std::cout << "isomorphismSearch()\n";
    int i = (int)assignments.size();

    // Make sure each query node can map to a data graph node
    for (const auto& node: query.nodes) {
        vertexList candidates = ullmannFilterCandidates(query, (*node.get()));
        if (candidates.empty()) {
            std::cout << "No candidates found for node " << node->getLabel() << ". Cannot find an isomorphism.\n";
            return false;
        }
    }

    if (i == (int)query.nodes.size()) {
        return true;
    }

    // Go through all possible assignments
    for (auto& node: nodes) {
        if (std::find(assignments.begin(), assignments.end(), node.get()) == assignments.end()) {
            // node not in assignments
            std::cout << "Adding node " << *node.get() << " to assignments.\n";
            assignments.push_back(node.get());
            if (isomorphismSearch(query, assignments)) {
                std::cout << "Found an isomorphism\n";
                return true;
            }
            assignments.erase(assignments.begin());
        }
    }
}


void Graph::ullmann(Graph& query) {
    // Implementation of the ullmann subgraph isomorphism algorithm as described here:
    // http://www.vldb.org/pvldb/vol6/p133-han.pdf
    embedding M;

    // First, make sure each node in the query graph can be mapped to a possible node in the data graph
    for (const auto& node: query.nodes) {
        vertexList candidates = ullmannFilterCandidates(query, (*node.get()));
        if (candidates.empty()) {
            std::cout << "No candidates found for node " << node->getLabel() << ".\n";
            return;
        }
    }

    UllmannSubgraphSearch(query, M);
}

vertexList Graph::ullmannFilterCandidates(const Graph& query, const Vertex& queryNode) const {
    // Return list of vertices of this graph which have a matching label of the passed query graph node
    vertexList candidates;
    std::cout << "Filtering candidates for: " << queryNode.getLabel() << "\n";
    for (const auto& potentialCandidate: nodes) {
        if (potentialCandidate->getLabel() == queryNode.getLabel()) {
            candidates.push_back(potentialCandidate.get());
            std::cout << "\tAdding candidate: " << (*potentialCandidate.get()) << "\n";
        }
    }
    return candidates;
}

embedding Graph::UllmannSubgraphSearch(Graph& query, embedding& M) {
    // Return when all vertices in query are contained in M
    // TODO: Check vertices, not size
    std::cout << "UllmannSubgraphSearch()\n";

    // All vertices in the query have been mapped
    if (M.size() == query.nodes.size()) {
        return M;
    }

    Vertex* u;
    // Choose a vertex from query that has not been matched
    // TODO: Change logic to check if node is not in M instead of checking `matched`
    for (const auto& node: query.nodes) {
        if (!node->matched) {
            u = node.get();
            break;
        }
    }
}

vertexList Graph::ullmannRefineCandidates(embedding& M, Vertex& u, vertexList& candidates) const {
    // TODO: Refine candidates set by removing all nodes in `candidates` that have a smaller degree than `u`
}
