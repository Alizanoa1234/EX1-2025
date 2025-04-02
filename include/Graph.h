#pragma once
#include <stdexcept>

namespace graph {

    struct Node {
        int dest;
        int weight;
        Node* next;
    };

    class Graph {
    private:
        int vertices;
        Node** adjList;

        void deleteList(Node* head);

    public:
        Graph(int numVertices);
        ~Graph();

        void addEdge(int src, int dest, int weight = 1);
        void removeEdge(int src, int dest);
        void print_graph() const;
        Node* getAdjList(int v) const { return adjList[v]; }
        int getVertexCount() const { return vertices; }

    };

}
