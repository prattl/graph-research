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

void HyperGraph::addVertex(const std::string label) {
    nodes.push_back(std::make_unique<HyperVertex>(label));
}

void HyperGraph::addEdge(const std::string label) {
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

void HyperGraph::connectVertices(HyperVertex& sourceVertex, HyperVertex& destinationVertex, HyperEdge& edge) {
    sourceVertex.addDestinationEdge(edge);
    edge.addSourceVertex(sourceVertex);
    edge.addDestinationVertex(destinationVertex);
    destinationVertex.addSourceEdge(edge);
}

void HyperGraph::connectVertices(std::string sourceVertexLabel, std::string destinationVertexLabel, std::string edgeLabel) {
    HyperVertex* sourceVertex = getVertex(sourceVertexLabel);
    HyperVertex* destinationVertex = getVertex(destinationVertexLabel);
    HyperEdge* edge = getEdge(edgeLabel);
    connectVertices(*sourceVertex, *destinationVertex, *edge);
}

void HyperGraph::prepareForTraversal() const {
    // Prepare for a new traversal by marking all nodes as unvisited.
    for (auto& node: nodes) {
        node->unVisit();
    }
}

void HyperGraph::traverseDfsRecursive(const std::string startingNodeLabel) {
    HyperVertex* startingNode = getVertex(startingNodeLabel);
    traverseDfsRecursive(*startingNode);
}

void HyperGraph::recursiveDfs(const HyperVertex& node) {
    if (!node.isVisited()) {}
    node.visit();
    std::cout << "\tVisiting node " << node.getLabel() << "\n";
    for (auto& edge: node.destinationEdges) {
        for (auto& neighbor: edge->destinationNodes) {
            if (!neighbor->isVisited()) {
                recursiveDfs(*neighbor);
            }
        }
    }
}

void HyperGraph::traverseDfsRecursive(const HyperVertex& startingNode) {
    // Traverse the entire hypergraph beginning from the startingNode
    prepareForTraversal();
    std::cout << "Recursive DFS traversal starting from node " << startingNode.getLabel() << ":\n";
    recursiveDfs(startingNode);
}


isomorphism HyperGraph::findIsomorphism(HyperGraph& query) {
    std::cout << "findIsomorphism()\n";
    isomorphism assignments; // Mapping of query to data nodes

    // Make sure each query node can map to a data graph node
    for (const auto& node: query.nodes) {
        hyperVertexList candidates = filterCandidates(query, (*node.get()));
        if (candidates.empty()) {
            std::cout << "No candidates found for node " << node->getLabel() << ". Cannot find an isomorphism.\n";
            return assignments;
        }
    }

    std::cout << "Found a candidate for each query vertex. Beginning subgraphSearch.\n";

    subgraphSearch(query, assignments);

    std::cout << "Found an isomorphism: \nQuery Vertex :: Data Vertex\n";
    for (auto& mapping: assignments) {
        std::cout << *(mapping.first) << " :: " << *(mapping.second) << "\n";
    }

    return assignments;
}

bool HyperGraph::subgraphSearch(HyperGraph& query, isomorphism& assignments) {
    std::cout << "subgraphSearch():\n";

    if (assignments.size() == query.nodes.size()) {
        std::cout << "\tAll nodes have been matched. Returning true.\n";
        return true;
    }

    // Go through all nodes and give them assignments
    HyperVertex* nextVertex = nextQueryVertex(query, assignments);
//    std::cout << "\tLooking at vertex: " << *nextVertex << "\n";

    hyperVertexList refinedCandidates = refineCandidates(query, assignments, *nextVertex);

    for (auto& candidate: refinedCandidates) {
        std::cout << "\t\tComparing to candidate: " << *candidate << ".\n";
        // TODO: Only check candidates that have not been matched
        bool joinable = isJoinable(query, assignments, *nextVertex, *candidate);
        if (joinable) {
            std::cout << "\t\t\tnextQueryVertex is joinable to data node candidate.\n";
            assignments.push_back(vertexMapping(nextVertex, candidate));
            subgraphSearch(query, assignments);

            // Remove the mapping from assignments
//            int i = 0;
//            for (auto& mapping: assignments) {
//                i++;
//                if (mapping.first->getUuid() == nextVertex->getUuid()) {
//                    break;
//                }
//            }
//            assignments.erase(assignments.begin() + i);
        } else {
            std::cout << "\t\t\tnextQueryVertex is not joinable to data node candidate.\n";
        }
    }
}

hyperVertexList HyperGraph::filterCandidates(const HyperGraph& query, const HyperVertex& queryNode) const {
    // Return list of vertices of this hypergraph which have a matching label of the passed query graph node
    hyperVertexList candidates;
    std::cout << "\tFiltering candidates for query node: " << queryNode.getLabel() << "\n";
    for (const auto& potentialCandidate: nodes) {
        if (potentialCandidate->getLabel() == queryNode.getLabel()) {
            candidates.push_back(potentialCandidate.get());
            std::cout << "\t\tAdding candidate: " << (*potentialCandidate.get()) << "\n";
        }
    }
    return candidates;
}

HyperVertex* HyperGraph::nextQueryVertex(HyperGraph& query, isomorphism& assignments) {
    // Return the next vertex of the query which has not been assigned
    for (auto& node: query.nodes) {
//        if (std::find(assignments.begin(), assignments.end(), node.get()) == assignments.end()) {
        auto nextVertex = std::find_if(assignments.begin(), assignments.end(),
                                       [&](auto& mapping){ return mapping.first == node.get();} );
//        for (auto &mapping: assignments) {
        if (nextVertex == assignments.end()) {
            // Vertex was not found in assignments, so we can return it
            std::cout << "\tSelected nextQueryVertex: " << *(node.get()) << ".\n";
            return node.get();
        }
    }

    std::cout << "\tWas not able to select an unassigned query vertex.\n";
    return nullptr;
}

hyperVertexList HyperGraph::refineCandidates(const HyperGraph& query,
                                             isomorphism& assignments,
                                             const HyperVertex& queryNode) {
    // For the simplest version of this algorithm, don't do any refinements Just treat all candidates as possibilities.
    return filterCandidates(query, queryNode);
}

bool HyperGraph::isJoinable(const HyperGraph& query, isomorphism& assignments,
                            HyperVertex& queryNode, HyperVertex& dataNode) {
    std::cout << "\t\t\tChecking if query node " << queryNode.getLabel() << " is joinable to data node " <<
            dataNode.getLabel() << ":\n";
    for (const auto& sourceQueryEdge: queryNode.sourceEdges) {
        std::cout << "\t\t\t\tLooking at source query edge: " << sourceQueryEdge->getLabel() << "\n";
        // Make sure each sourceQueryEdge has a corresponding source edge in the dataNode
        auto foundSourceEdge = std::find_if(dataNode.sourceEdges.begin(), dataNode.sourceEdges.end(),
                                            [&](auto& edge){ return edge->getLabel() == sourceQueryEdge->getLabel();} );
        if (foundSourceEdge == dataNode.sourceEdges.end()) {
            // Did not find a corresponding edge.
            std::cout << "\t\t\t\tDid not find an edge mapping for query source edge: " << sourceQueryEdge->getLabel() << "\n";
            return false;
        }
    }
    for (const auto& destinationQueryEdge: queryNode.destinationEdges) {
        std::cout << "\t\t\t\tLooking at destination query edge: " << destinationQueryEdge->getLabel() << "\n";
        // Make sure each sourceQueryEdge has a corresponding destination edge in the dataNode
        auto foundDestinationEdge = std::find_if(dataNode.destinationEdges.begin(), dataNode.destinationEdges.end(),
                                            [&](auto& edge){ return edge->getLabel() == destinationQueryEdge->getLabel();} );
        if (foundDestinationEdge == dataNode.destinationEdges.end()) {
            // Did not find a corresponding edge.
            std::cout << "\t\t\t\tDid not find an edge mapping for query destination edge: " << destinationQueryEdge->getLabel() << "\n";
            return false;
        }
    }

    return true;
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
