#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include <vector>
#include <iostream>
#include <memory>


namespace graphs {
    class Vertex;

    // shared_ptr is needed because both Vertex and Graph can maintain ownership of Vertex pointers.
    typedef std::shared_ptr<Vertex> smartVertexPtr;

    class Vertex {
    public:
        std::string name;
        std::vector<smartVertexPtr> neighbors;
        smartVertexPtr previous;  // Used during traversal
        bool visited;
        void addNeighbor(smartVertexPtr);
        bool isNeighborTo(smartVertexPtr);

        Vertex() { };

        Vertex(std::string s) : name(s) { };

        ~Vertex();
        friend std::ostream& operator<<(std::ostream &strm, const Vertex &v) {
            std::string neighbors;
            for (auto const& neighbor: v.neighbors) {
                neighbors += neighbor->name + ", ";
            }
            neighbors = neighbors.substr(0, neighbors.length() - 2);
            return strm << "Vertex: " << v.name << " (neighbors: " << neighbors << ")";
        }
    };


    class Graph {
        std::vector<smartVertexPtr> nodes;

        void recursiveDfs(Vertex &);


        void depthLimitedDfs(Vertex &, int);

    public:
        virtual void printGraph();

        virtual void addVertex(std::string);

        smartVertexPtr getVertex(std::string);

        void prepareTraverse();

        void addEdge(std::string, std::string);

        virtual smartVertexPtr traverseToVertexBfs(std::string start_name, std::string end_name);

        smartVertexPtr traverseToVertexBfs(Vertex &start, Vertex &end);

        virtual void traverseDfsRecursive(std::string);

        void traverseDfsIterative(std::string);

        void traverseDfsIterativeDeepening(std::string);
    };
}

#endif //GRAPHS_GRAPH_H
