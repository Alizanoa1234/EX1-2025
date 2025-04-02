// email: alizalazar9@gmail.com

# GraphProject

This project implements an undirected weighted graph using an **adjacency list** in **C++**, without using the STL. It includes several core algorithms:

- Breadth-First Search (BFS)
- Depth-First Search (DFS)
- Dijkstra's Algorithm (shortest paths)
- Prim's Algorithm (Minimum Spanning Tree)
- Kruskal's Algorithm (Minimum Spanning Tree)

The graph is built using arrays and raw pointers, following the project constraints.

## 📁 Folder Structure
```
GraphProject/
├── include/           # Header files
│   ├── Graph.h
│   └── Algorithms.h
├── src/               # Implementation files
│   ├── Graph.cpp
│   └── Algorithms.cpp
├── test/              # Unit tests (using doctest)
│   └── test.cpp
├── doctest.h          # Testing library (header-only)
├── main.cpp           # Program demonstration
├── Makefile           # Build commands
├── README.md          # Project documentation
```

## Features & Algorithms

### Graph
- Implemented using adjacency list via `Node*` linked lists.
- Supports:
  - `addEdge(int src, int dest, int weight)`
  - `removeEdge(int src, int dest)`
  - `print_graph()`

### Algorithms
- All in `Algorithms` class (namespace `graph`)
- Functions:
  - `bfs(Graph g, int start)` → returns BFS tree
  - `dfs(Graph g, int start)` → returns DFS tree
  - `dijkstra(Graph g, int start)` → returns shortest path tree
  - `prim(Graph g)` → returns MST
  - `kruskal(Graph g)` → returns MST

All data structures used (queue, union-find, edge list) are manually implemented using arrays.

## Compilation

### Build & Run:
```bash
make Main
./Main
```

### Run Unit Tests:
```bash
make test
```

### Run Valgrind Memory Check:
```bash
make valgrind
```

### Clean:
```bash
make clean
```

## Submission Format
- Includes `README.md`, `Makefile`, all `.cpp/.h` files, `doctest.h`, and `submission.txt`
- Code is modular, readable, tested, and STL-free
- All memory is safely managed (`valgrind` verified)

---

Made with by Aliza Lazar

