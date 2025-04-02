#include "../include/Graph.h"
#include <iostream>

using namespace graph;

Graph::Graph(int numVertices) : vertices(numVertices) {
    adjList = new Node*[vertices];
    for (int i = 0; i < vertices; ++i)
        adjList[i] = nullptr;
}

Graph::~Graph() {
    for (int i = 0; i < vertices; ++i)
        deleteList(adjList[i]);
    delete[] adjList;
}

void Graph::deleteList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void Graph::addEdge(int src, int dest, int weight) {
    if (src < 0 || src >= vertices || dest < 0 || dest >= vertices)
        throw std::out_of_range("Invalid vertex index");

    Node* newNode = new Node{dest, weight, adjList[src]};
    adjList[src] = newNode;

    newNode = new Node{src, weight, adjList[dest]};
    adjList[dest] = newNode;
}

void Graph::removeEdge(int src, int dest) {
    bool removed = false;

    auto remove = [&](int u, int v) {
        Node** curr = &adjList[u];
        while (*curr) {
            if ((*curr)->dest == v) {
                Node* temp = *curr;
                *curr = (*curr)->next;
                delete temp;
                return true;
            }
            curr = &(*curr)->next;
        }
        return false;
    };

    removed |= remove(src, dest);
    removed |= remove(dest, src);

    if (!removed)
        throw std::runtime_error("Edge not found");
}

void Graph::print_graph() const {
    for (int i = 0; i < vertices; ++i) {
        std::cout << i << ": ";
        Node* temp = adjList[i];
        while (temp) {
            std::cout << "(" << temp->dest << ", w=" << temp->weight << ") ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
}
