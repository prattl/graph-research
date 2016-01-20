#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    Graph g;
    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");

    g.addEdge("1", "3");
    g.addEdge("2", "3");
    g.addEdge("2", "4");
    g.addEdge("3", "4");
    g.addEdge("4", "5");

    Vertex* v = g.traverseToVertexBfs("1", "5");

    g.printGraph();

    return 0;
}