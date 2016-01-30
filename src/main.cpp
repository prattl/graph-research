#include <iostream>
#include "Graph.h"
//#include "Hypergraph.h"
#include <stack>

using namespace std;

int main() {
    cout << "================== GRAPHS ==================\n";
    graphs::Graph g;

    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");
    g.addVertex("6");
    g.addVertex("7");
    g.addVertex("8");
    g.addVertex("9");
    g.addVertex("10");

    g.addEdge("1", "2");
    g.addEdge("1", "6");
    g.addEdge("2", "3");
    g.addEdge("2", "4");
    g.addEdge("4", "5");
    g.addEdge("6", "7");
    g.addEdge("6", "8");
    g.addEdge("8", "9");
    g.addEdge("9", "10");

    // Simulate an undirected graph
//    g.addEdge("2", "1");
//    g.addEdge("6", "1");
//    g.addEdge("3", "2");
//    g.addEdge("4", "2");
//    g.addEdge("5", "4");
//    g.addEdge("7", "6");
//    g.addEdge("8", "6");
//    g.addEdge("9", "8");
//    g.addEdge("10", "9");

    g.printGraph();

    g.traverseDfsRecursive("1");
    g.traverseDfsIterative("1");
    g.traverseDfsIterativeDeepening("1");

    graphs::Vertex* v = g.traverseToVertexBfs("1", "5");

    stack<graphs::Vertex*> shortest_path;
    cout << "Shortest path: \n";
    shortest_path.push(v);

    while (v->previous) {
        v = v->previous;
        shortest_path.push(v);
    }
    while (!shortest_path.empty()) {
        v = shortest_path.top();
        shortest_path.pop();

        cout << v->getLabel();
        if (!shortest_path.empty()) {
            cout << " --> ";
        }
    }
    cout << endl;

//    cout << "================== HYPERGRAPHS ==================\n";
//    hypergraphs::HyperGraph hg;
//
//    hg.addVertex("1");
//    hg.addVertex("2");
//    hg.addVertex("3");
//    hg.addVertex("4");
//    hg.addVertex("5");
//    hg.addVertex("6");
//    hg.addVertex("7");
//
//    hg.addEdge("a");
//    hg.addEdge("b");
//    hg.addEdge("c");
//    hg.addEdge("d");
//
//    hg.connectVertexToEdge("1", "a");
//    hg.connectVertexToEdge("2", "a");
//    hg.connectVertexToEdge("7", "a");
//    hg.connectVertexToEdge("2", "b");
//    hg.connectVertexToEdge("3", "b");
//    hg.connectVertexToEdge("4", "b");
//    hg.connectVertexToEdge("3", "c");
//    hg.connectVertexToEdge("4", "c");
//    hg.connectVertexToEdge("5", "c");
//    hg.connectVertexToEdge("5", "d");
//    hg.connectVertexToEdge("6", "d");
//
//    hg.traverseBfs("1");
//
//    hg.traverseDfsRecursive("3");
////    hg.traverseDfsIterative("1");
////    hg.traverseDfsIterativeDeepening("1");
//
//    hg.printGraph();

    return 0;
}