#include <iostream>
#include "Graph.h"
#include "Hypergraph.h"
using namespace std;

int main() {
    cout << "================== GRAPHS ==================\n";
//    graphs::Graph g;
//    graphs::Graph g2;
//
//    g.addVertex("1");
//    g.addVertex("2");
//    g.addVertex("3");
//    g.addVertex("4");
//    g.addVertex("5");
//    g.addVertex("6");
//    g.addVertex("7");
//    g.addVertex("8");
//    g.addVertex("9");
//    g.addVertex("10");
//
//    g.addEdge("1", "2");
//    g.addEdge("1", "6");
//    g.addEdge("2", "3");
//    g.addEdge("2", "4");
//    g.addEdge("4", "5");
//    g.addEdge("6", "7");
//    g.addEdge("6", "8");
//    g.addEdge("8", "9");
//    g.addEdge("9", "4");
//    g.addEdge("9", "10");
//
//    g2.addVertex("4");
//    g2.addVertex("5");
//    g2.addVertex("9");
//    g2.addVertex("10");
//
//    g2.addEdge("4", "5");
//    g2.addEdge("9", "4");
//    g2.addEdge("9", "10");
//
//    cout << "Graph 1:\n";
//    g.printGraph();
//    cout << "Graph 2:\n";
//    g2.printGraph();
//
//    graphs::vertexList iso = g.findIsomorphism(g2);
//    cout << "Results:\n";
//    for (auto& node: iso) {
//        cout << "\t" << *node << "\n";
//    }

//    g.ullmann(g2);

//    g.traverseDfsRecursive("1");
//    g.traverseDfsIterative("1");
//    g.traverseDfsIterativeDeepening("1");
//
//    graphs::Vertex* v = g.traverseToVertexBfs("1", "5");
//
//    stack<graphs::Vertex*> shortest_path;
//    cout << "Shortest path to " << v->getLabel() << ": \n";
//    shortest_path.push(v);
//
//    while (v->previous) {
//        v = v->previous;
//        shortest_path.push(v);
//    }
//    while (!shortest_path.empty()) {
//        v = shortest_path.top();
//        shortest_path.pop();
//
//        cout << v->getLabel();
//        if (!shortest_path.empty()) {
//            cout << " --> ";
//        }
//    }
//    cout << endl;
//
//    graphs::Triangle t = g2.findTriangle();
//
//    graphs::AdjacencyMatrix am = g2.buildAdjacencyMatrix();
//    cout << "Adjacency matrix for g2:\n";
//    for (const auto& row: am) {
//        for (const auto& node: row) {
//            cout << node << " ";
//        }
//        cout << "\n";
//    }

    cout << "================== HYPERGRAPHS ==================\n";
    hypergraphs::HyperGraph hg;

    hg.addVertex("1");
    hg.addVertex("2");
    hg.addVertex("3");
    hg.addVertex("4");
    hg.addVertex("5");
    hg.addVertex("6");
    hg.addVertex("7");

    hg.addEdge("a");
    hg.addEdge("b");
    hg.addEdge("c");
    hg.addEdge("d");

    hg.connectVertices("1", "3", "a");
    hg.connectVertices("1", "4", "a");
    hg.connectVertices("1", "5", "b");
    hg.connectVertices("2", "3", "a");
    hg.connectVertices("2", "4", "a");
    hg.connectVertices("3", "5", "b");
    hg.connectVertices("5", "6", "d");
    hg.connectVertices("5", "7", "d");
    hg.connectVertices("7", "3", "c");
    hg.connectVertices("7", "4", "c");

//    hg.traverseBfs("1");

    hg.traverseDfsRecursive("1");
//    hg.traverseDfsIterative("1");
//    hg.traverseDfsIterativeDeepening("1");

    hg.printGraph();

    return 0;
}