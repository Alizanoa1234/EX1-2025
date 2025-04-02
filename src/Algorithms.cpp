#include "../include/Algorithms.h"
#include <stdexcept>

using namespace graph;

// ------------------------ BFS ------------------------

Graph Algorithms::bfs(const Graph& g, int start) {
    const int n = g.getVertexCount();
    if (start < 0 || start >= n)
        throw std::out_of_range("Invalid start vertex"); 

    Graph bfsTree(n);
    bool* visited = new bool[n];
    int* queue = new int[n];
    int front = 0, rear = 0;

    for (int i = 0; i < n; ++i) visited[i] = false;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int u = queue[front++];
        Node* temp = g.getAdjList(u);

        while (temp) {
            int v = temp->dest;
            if (!visited[v]) {
                visited[v] = true;
                bfsTree.addEdge(u, v, temp->weight);
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    delete[] visited;
    delete[] queue;
    return bfsTree;
}

// ------------------------ DFS ------------------------

void dfs_visit(const Graph& g, Graph& dfsTree, bool* visited, int u) {
    visited[u] = true;
    Node* temp = g.getAdjList(u);

    while (temp) {
        int v = temp->dest;
        if (!visited[v]) {
            dfsTree.addEdge(u, v, temp->weight);
            dfs_visit(g, dfsTree, visited, v);
        }
        temp = temp->next;
    }
}

Graph Algorithms::dfs(const Graph& g, int start) {
    const int n = g.getVertexCount();
    if (start < 0 || start >= n)
        throw std::out_of_range("Invalid start vertex");

    Graph dfsTree(n);
    bool* visited = new bool[n];
    for (int i = 0; i < n; ++i) visited[i] = false;

    dfs_visit(g, dfsTree, visited, start);

    delete[] visited;
    return dfsTree;
}

// ------------------------ dijkstra ------------------------

Graph Algorithms::dijkstra(const Graph& g, int start) {
    const int n = g.getVertexCount();
    if (start < 0 || start >= n)
        throw std::out_of_range("Invalid start vertex");

    int* dist = new int[n];
    bool* visited = new bool[n];
    int* parent = new int[n];

    for (int i = 0; i < n; ++i) {
        dist[i] = INT32_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < n; ++count) {
        // Find the unvisited node with smallest distance
        int u = -1;
        int minDist = INT32_MAX;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1) break; // No reachable node

        visited[u] = true;
        Node* temp = g.getAdjList(u);
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;
            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    // Build result graph (shortest path tree)
    Graph result(n);
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1)
            result.addEdge(v, parent[v], dist[v] - dist[parent[v]]);
    }

    delete[] dist;
    delete[] visited;
    delete[] parent;

    return result;
}

// ------------------------ prim ------------------------

Graph Algorithms::prim(const Graph& g) {
    const int n = g.getVertexCount();
    int* key = new int[n];
    bool* inMST = new bool[n];
    int* parent = new int[n];

    for (int i = 0; i < n; ++i) {
        key[i] = INT32_MAX;
        inMST[i] = false;
        parent[i] = -1;
    }

    key[0] = 0; // Start from vertex 0

    for (int count = 0; count < n; ++count) {
        // Pick min key vertex not yet in MST
        int u = -1, minKey = INT32_MAX;
        for (int i = 0; i < n; ++i) {
            if (!inMST[i] && key[i] < minKey) {
                minKey = key[i];
                u = i;
            }
        }

        if (u == -1) break; // disconnected graph
        inMST[u] = true;

        Node* temp = g.getAdjList(u);
        while (temp) {
            int v = temp->dest;
            int weight = temp->weight;
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    Graph mst(n);
    for (int v = 1; v < n; ++v) {
        if (parent[v] != -1)
            mst.addEdge(v, parent[v], key[v]);
    }

    delete[] key;
    delete[] inMST;
    delete[] parent;
    return mst;
}

struct Edge {
    int src, dest, weight;
};

int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

void union_sets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);
    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }

}

// ------------------------ kruskal ------------------------

Graph Algorithms::kruskal(const Graph& g) {
    const int n = g.getVertexCount();
    Edge* edges = new Edge[n * n];  // Max possible edges
    int edgeCount = 0;

    // Collect edges from adjacency list
    for (int u = 0; u < n; ++u) {
        Node* temp = g.getAdjList(u);
        while (temp) {
            int v = temp->dest;
            if (u < v) { // avoid duplicates in undirected graph
                edges[edgeCount++] = {u, v, temp->weight};
            }
            temp = temp->next;
        }
    }

    // Bubble sort edges by weight
    for (int i = 0; i < edgeCount - 1; ++i) {
        for (int j = 0; j < edgeCount - i - 1; ++j) {
            if (edges[j].weight > edges[j + 1].weight) {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    Graph mst(n);
    int* parent = new int[n];
    int* rank = new int[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }

    int addedEdges = 0;
    for (int i = 0; i < edgeCount && addedEdges < n - 1; ++i) {
        int u = edges[i].src;
        int v = edges[i].dest;

        int setU = find(parent, u);
        int setV = find(parent, v);

        if (setU != setV) {
            mst.addEdge(u, v, edges[i].weight);
            union_sets(parent, rank, setU, setV);
            addedEdges++;
        }
    }

    delete[] edges;
    delete[] parent;
    delete[] rank;

    return mst;
}


