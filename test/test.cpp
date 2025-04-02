// email: alizalazar9@gmail.com
    
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../include/Graph.h"
#include "../include/Algorithms.h"

using namespace graph;

TEST_CASE("Graph addEdge and print") {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    CHECK_NOTHROW(g.print_graph());
}

TEST_CASE("Graph removeEdge success") {
    Graph g(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    CHECK_NOTHROW(g.removeEdge(0, 1));
    CHECK_THROWS(g.removeEdge(0, 1)); // edge already removed
}

TEST_CASE("BFS produces valid tree") {
    Graph g(5);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK_NOTHROW(bfsTree.print_graph());
}

TEST_CASE("DFS produces valid tree") {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK_NOTHROW(dfsTree.print_graph());
}

TEST_CASE("Dijkstra shortest path") {
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(0, 2, 4);

    Graph dij = Algorithms::dijkstra(g, 0);
    CHECK_NOTHROW(dij.print_graph());
}

TEST_CASE("Prim and Kruskal MSTs") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 3);

    Graph mst1 = Algorithms::prim(g);
    Graph mst2 = Algorithms::kruskal(g);
    CHECK_NOTHROW(mst1.print_graph());
    CHECK_NOTHROW(mst2.print_graph());
}
