// email: alizalazar9@gmail.com

#include "include/Graph.h"
#include "include/Algorithms.h"
#include <iostream>


using namespace graph;

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    std::cout << "Original Graph:\n";
    g.print_graph();

    std::cout << "\nBFS Tree (from vertex 0):\n";
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();

    std::cout << "\nDFS Tree (from vertex 0):\n";
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();

    std::cout << "\nDijkstra Tree (from vertex 0):\n";
    Graph dijTree = Algorithms::dijkstra(g, 0);
    dijTree.print_graph();

    std::cout << "\nPrim MST Tree:\n";
    Graph mst = Algorithms::prim(g);
    mst.print_graph();

    std::cout << "\nKruskal MST Tree:\n";
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.print_graph();

    return 0;
}
