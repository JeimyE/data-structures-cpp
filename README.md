# C++ Data Structures — Complete Library

A header-only, template-based implementation of **14 fundamental data structures** and **5 sorting algorithms** in modern C++17. No external dependencies beyond the standard library.

## Table of Contents

| # | Structure | File | Category |
|---|---|---|---|
| 1 | Singly Linked List | `LinkedList.h` | Linear |
| 2 | Doubly Linked List | `DoublyLinkedList.h` | Linear |
| 3 | Stack | `Stack.h` | Linear |
| 4 | Queue | `Queue.h` | Linear |
| 5 | Deque | `Deque.h` | Linear |
| 6 | Circular Buffer | `CircularBuffer.h` | Linear |
| 7 | Binary Search Tree | `BinarySearchTree.h` | Tree |
| 8 | AVL Tree | `AVLTree.h` | Tree |
| 9 | Heap (Min / Max) | `Heap.h` | Tree |
| 10 | Trie | `Trie.h` | Tree |
| 11 | Hash Table | `HashTable.h` | Hashing |
| 12 | Graph | `Graph.h` | Graph |
| 13 | Union-Find | `UnionFind.h` | Graph |
| 14 | Sorting Algorithms | `SortingAlgorithms.h` | Algorithms |

## Project Structure

```
data-structures-cpp/
├── LinkedList.h          # Singly linked list
├── DoublyLinkedList.h    # Doubly linked list
├── Stack.h               # LIFO stack
├── Queue.h               # FIFO queue
├── Deque.h               # Double-ended queue
├── CircularBuffer.h      # Fixed-capacity ring buffer
├── BinarySearchTree.h    # Binary search tree
├── AVLTree.h             # Self-balancing AVL tree
├── Heap.h                # Min-heap / Max-heap
├── Trie.h                # Prefix tree for strings
├── HashTable.h           # Hash map (separate chaining)
├── Graph.h               # Weighted graph (BFS / DFS / Dijkstra)
├── UnionFind.h           # Disjoint-set with path compression
├── SortingAlgorithms.h   # Bubble, Selection, Insertion, Merge, Quick
└── main.cpp              # Demo program for all structures
```

## How to Compile

### Linux / macOS

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o demo main.cpp
```

### Windows — MinGW / MSYS2

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o demo.exe main.cpp
```

### Windows — MSVC (Developer Command Prompt)

```bash
cl /std:c++17 /W4 /O2 /EHsc main.cpp /Fe:demo.exe
```

## How to Run

```bash
./demo       # Linux / macOS
demo.exe     # Windows
```

---

## Linear Structures

### 1. Singly Linked List — `LinkedList.h`

Each node holds a value and a pointer to the next node.

| Method | Complexity |
|---|---|
| `append(value)` | O(n) |
| `prepend(value)` | O(1) |
| `remove(value)` | O(n) |
| `search(value)` | O(n) |
| `print()` | O(n) |

```cpp
#include "LinkedList.h"

LinkedList<int> list;
list.append(10);
list.append(20);
list.prepend(5);    // 5 -> 10 -> 20 -> nullptr

list.search(10);    // true
list.remove(10);
list.print();       // 5 -> 20 -> nullptr
```

---

### 2. Doubly Linked List — `DoublyLinkedList.h`

Each node has `prev` and `next` pointers, enabling O(1) removal by node and bidirectional traversal.

```cpp
#include "DoublyLinkedList.h"

DoublyLinkedList<int> list;
list.append(10); list.append(20); list.append(30);

list.printForward();   // 10 <-> 20 <-> 30
list.printBackward();  // 30 <-> 20 <-> 10
list.remove(20);
list.printForward();   // 10 <-> 30
```

---

### 3. Stack — `Stack.h`

LIFO structure. All core operations are O(1). Throws `std::underflow_error` on `pop`/`peek` of an empty stack.

```cpp
#include "Stack.h"

Stack<int> stack;
stack.push(1); stack.push(2); stack.push(3);

stack.peek();   // 3  (no removal)
stack.pop();    // 3
stack.pop();    // 2
```

---

### 4. Queue — `Queue.h`

FIFO structure. All core operations are O(1). Throws `std::underflow_error` on empty access.

```cpp
#include "Queue.h"

Queue<std::string> q;
q.enqueue("Alice"); q.enqueue("Bob"); q.enqueue("Carol");

q.front();      // "Alice"
q.dequeue();    // "Alice"
q.dequeue();    // "Bob"
```

---

### 5. Deque — `Deque.h`

Double-ended queue backed by a doubly linked list. Push and pop at both ends in O(1).

```cpp
#include "Deque.h"

Deque<int> dq;
dq.push_back(10);
dq.push_front(5);   // [5 <-> 10]
dq.push_back(20);   // [5 <-> 10 <-> 20]

dq.front();         // 5
dq.back();          // 20
dq.pop_front();     // 5  → [10 <-> 20]
dq.pop_back();      // 20 → [10]
```

---

### 6. Circular Buffer — `CircularBuffer.h`

Fixed-capacity FIFO ring buffer. O(1) push and pop with no element shifting. Throws `std::overflow_error` when full, `std::underflow_error` when empty.

```cpp
#include "CircularBuffer.h"

CircularBuffer<int> buf(4);
buf.push(1); buf.push(2); buf.push(3);
buf.pop();              // 1
buf.push(4); buf.push(5);
buf.print();            // [2, 3, 4, 5] (4/4)

buf.isFull();           // true
buf.push(6);            // throws std::overflow_error
```

---

## Tree Structures

### 7. Binary Search Tree — `BinarySearchTree.h`

Left subtree holds smaller values; right subtree holds larger values.

| Method | Average | Worst (unbalanced) |
|---|---|---|
| `insert` / `search` / `remove` | O(log n) | O(n) |
| Traversals | O(n) | O(n) |

```cpp
#include "BinarySearchTree.h"

BinarySearchTree<int> bst;
for (int v : {50, 30, 70, 20, 40}) bst.insert(v);

bst.search(40);   // true
bst.inorder();    // 20 30 40 50 70

bst.remove(30);
bst.inorder();    // 20 40 50 70
bst.print();      // ASCII diagram
```

---

### 8. AVL Tree — `AVLTree.h`

Self-balancing BST. After every insert and remove, the tree rebalances via rotations to keep height O(log n), guaranteeing O(log n) in all cases — even for sorted input.

```cpp
#include "AVLTree.h"

AVLTree<int> avl;
// Inserting in order would make a plain BST O(n), but AVL rebalances automatically.
for (int v : {10, 20, 30, 40, 50}) avl.insert(v);

avl.height();     // 2 (balanced)
avl.inorder();    // 10 20 30 40 50
avl.print();      // ASCII diagram annotated with node heights
avl.remove(30);
```

---

### 9. Heap — `Heap.h`

Array-based binary heap. The comparator determines whether it is a min-heap or max-heap.

| Alias | Top element | Extract order |
|---|---|---|
| `MinHeap<T>` | smallest | ascending |
| `MaxHeap<T>` | largest | descending |

| Method | Complexity |
|---|---|
| `insert` | O(log n) |
| `extractTop` / `peek` | O(log n) / O(1) |
| `Heap(vector)` — buildHeap | O(n) |

```cpp
#include "Heap.h"

MinHeap<int> minH;
for (int v : {5, 3, 8, 1}) minH.insert(v);
minH.peek();         // 1
minH.extractTop();   // 1, 3, 5, 8 ...

MaxHeap<int> maxH;
for (int v : {5, 3, 8, 1}) maxH.insert(v);
maxH.peek();         // 8

// O(n) build from existing data:
MinHeap<int> built(std::vector<int>{9, 4, 7, 1, 6});
built.peek();        // 1
```

---

### 10. Trie — `Trie.h`

Prefix tree for lowercase ASCII strings. Each edge represents a character; `isEnd` marks complete words.

| Method | Complexity |
|---|---|
| `insert` / `search` / `startsWith` | O(m) — m = word length |
| `autocomplete(prefix)` | O(m + k) — k = results |

```cpp
#include "Trie.h"

Trie trie;
trie.insert("apple");
trie.insert("app");
trie.insert("application");

trie.search("app");          // true
trie.search("ap");           // false (not a complete word)
trie.startsWith("app");      // true

trie.autocomplete("app");    // {"app", "apple", "application"}

trie.remove("app");
trie.search("app");          // false
trie.search("apple");        // true  (prefix still valid)
```

---

## Hashing

### 11. Hash Table — `HashTable.h`

Hash map with separate chaining. Automatically rehashes (doubling bucket count) when the load factor exceeds 0.75. Requires `std::hash<K>` to exist for the key type.

| Method | Average | Worst (all in one bucket) |
|---|---|---|
| `insert` / `get` / `remove` | O(1) | O(n) |

```cpp
#include "HashTable.h"

HashTable<std::string, int> table;
table.insert("alice", 30);
table.insert("bob",   25);

table.contains("alice");   // true
table.get("alice");        // 30

// Inserting an existing key updates the value:
table.insert("alice", 31);
table.get("alice");        // 31

table.remove("bob");
table.contains("bob");     // false
```

---

## Graph Structures

### 12. Graph — `Graph.h`

Weighted adjacency-list graph (directed or undirected). Supports BFS, DFS, and Dijkstra's shortest paths. Requires `std::hash<T>` for the vertex type.

| Algorithm | Complexity |
|---|---|
| BFS / DFS | O(V + E) |
| Dijkstra | O((V + E) log V) |

```cpp
#include "Graph.h"

Graph<int> g(false);  // undirected
g.addEdge(1, 2, 4);
g.addEdge(1, 3, 2);
g.addEdge(3, 4, 1);
g.addEdge(2, 4, 5);

g.bfs(1);         // {1, 2, 3, 4}
g.dfs(1);         // {1, 2, 4, 3}

auto dist = g.dijkstra(1);
// dist[1]=0, dist[2]=4, dist[3]=2, dist[4]=3

// Directed graph example:
Graph<int> dg(true);
dg.addEdge(1, 2);
dg.addEdge(2, 3);
dg.hasEdge(2, 1);  // false (directed)
```

---

### 13. Union-Find — `UnionFind.h`

Disjoint-set data structure with **path compression** and **union by rank**, giving near-O(1) amortized `find` and `union` operations (inverse-Ackermann complexity).

```cpp
#include "UnionFind.h"

UnionFind<int> uf;
for (int i = 1; i <= 6; ++i) uf.makeSet(i);

uf.unionSets(1, 2);
uf.unionSets(3, 4);
uf.unionSets(5, 6);
uf.getComponents();  // 3

uf.unionSets(1, 4);
uf.getComponents();  // 2

uf.connected(1, 3);  // true  (merged via 1-2 and 3-4 then 1-4)
uf.connected(1, 5);  // false
```

---

## Sorting Algorithms — `SortingAlgorithms.h`

All algorithms sort `std::vector<T>` in-place inside the `Sorting` namespace.

| Algorithm | Best | Average | Worst | Space | Notes |
|---|---|---|---|---|---|
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) | Early-exit optimization |
| Selection Sort | O(n²) | O(n²) | O(n²) | O(1) | Minimal swaps |
| Insertion Sort | O(n) | O(n²) | O(n²) | O(1) | Fast on nearly-sorted data |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) | Stable |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) | Median-of-three pivot |

```cpp
#include "SortingAlgorithms.h"
#include <vector>

std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};

Sorting::bubbleSort(data);      // {11, 12, 22, 25, 34, 64, 90}
Sorting::selectionSort(data);
Sorting::insertionSort(data);
Sorting::mergeSort(data);
Sorting::quickSort(data);
```

---

## Requirements

- C++17 or later (`-std=c++17`)
- Any standard-conforming compiler: GCC 7+, Clang 5+, MSVC 2017+

## License

Released for educational use. Feel free to study, adapt, and share.
