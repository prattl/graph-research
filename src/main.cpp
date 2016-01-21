#include <iostream>
#include "Graph.h"
#include <stack>

using namespace std;

int main() {
    Graph g;

    g.addVertex("1");
    g.addVertex("2");
    g.addVertex("3");
    g.addVertex("4");
    g.addVertex("5");
    g.addVertex("6");
    g.addVertex("7");
    g.addVertex("8");

    g.addEdge("1", "2");
    g.addEdge("1", "6");
    g.addEdge("2", "3");
    g.addEdge("2", "4");
    g.addEdge("4", "5");
    g.addEdge("6", "7");
    g.addEdge("6", "8");

    g.printGraph();

    g.traverseDfsRecursive("1");
    g.traverseDfsIterative("1");

    Vertex* v = g.traverseToVertexBfs("1", "5");

    stack<Vertex*> shortest_path;
    cout << "Shortest path: ";
    shortest_path.push(v);
    while (v->previous) {
        v = v->previous;
        shortest_path.push(v);
    }
    while (!shortest_path.empty()) {
        v = shortest_path.top();
        shortest_path.pop();

        cout << v->name;
        if (!shortest_path.empty()) {
            cout << " --> ";
        }
    }
    cout << endl;

    return 0;
}