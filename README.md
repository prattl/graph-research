# Graph Project
Simple project to brush up on some data structures and algorithms, 
and also to re-familiarize with C++ and learn some of the new features introduced in 11 and 14.

# To Do:
- [x] Graphs
  - [x] Data structures (adjacency lists)
  - [x] BFS traversal
  - [x] Recursive DFS traversal
  - [x] Iterative DFS traversal
  - [x] Iterative Deepening DFS traversal
- [ ] Hypergraphs
  - [x] Data structures
  - [x] BFS traversal
  - [x] DFS traversal
  - [ ] Shortest path
- [ ] Simple parser (with Boost Spirit?) to construct graphs
- [x] Smart pointers
- [x] Use const when possible
- [x] Move vertex & edge data to struct (pimpl)
- [ ] Subgraph isomorphism
- [ ] Add Uuids to vertices and edges and use those to check for uniqueness instead of labels
- [ ] Make sure members are initialized properly

# Notes
After refactoring the Edge and Vertex classes to hold pairs of Vertices and lists of edges (respectively), some of the derived semantics were broken. The issue comes down to whether it makes sense for vertices to own their originating edges (makes sense for directed graphs), or if they should only know about a list of their neighbors. Either approach works for graphs, but extending the idea to hypergraphs makes it more complicated because hyperedges might need to be able to store a dynamic list of vertices. If we want vertices to hold a list of edges, then this isn't easily adaptable to hypergraphs because of how they interpret directionality. In order to extend this idea to hypergraphs, the Vertex interface should only expose neighbors and not edges.

The idea of a vertex owning an originating edge doesn't have a clear meaning when dealing with a hypergraph. For example, do hyperedges know about the vertices they contain, or do vertices know about the edges they belong to (or both)? It seems that certain types of traversal could benefit from either. Also, the definition of a directed hypergraph does not seem immediately clear. In a directed graph, an edge signifies a unidirectional path from a source vertex to a destination vertex. Movement across this edge is possible at any point as long as it is in the correct direction. In a hypergraph though, an edge can connect any number of vertices, so the idea of an edge connecting a source and a destination vertex is only relevant during traversal. It would seem that one approach is to mark vertices beloning to a hyperedge as either a source, destination, or both, and traversal can only move from a source to a destination within the hyperedge. But this seems arbitrary because then the logic of determining an edge's directionality lies in its vertices and not the edge itself. Another possibility is that each vertex within a hyperedge would also have a directed pseudo-edge to each of its neighbors within the hyperedge. But this almost makes it seem like the idea of a hyperedge is really just a graph with vertices that can link to vertices belonging to other graphs.