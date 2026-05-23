#include <iostream>
#include <vector>
#include <string>
#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "Stack.h"
#include "Queue.h"
#include "BinarySearchTree.h"
#include "SortingAlgorithms.h"
#include "Deque.h"
#include "CircularBuffer.h"
#include "AVLTree.h"
#include "Heap.h"
#include "HashTable.h"
#include "Trie.h"
#include "Graph.h"
#include "UnionFind.h"

// ── Helpers ──────────────────────────────────────────────────────────────────

static void printSection(const std::string& title) {
    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(60, '=') << "\n";
}

static void printVec(const std::string& label, const std::vector<int>& v) {
    std::cout << label << ": [";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

// ── Original demos ────────────────────────────────────────────────────────────

void demoLinkedList() {
    printSection("Singly Linked List");

    LinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.prepend(5);
    std::cout << "After append(10,20,30) and prepend(5):\n  ";
    list.print();

    std::cout << "Search 20: " << (list.search(20) ? "found" : "not found") << "\n";
    std::cout << "Search 99: " << (list.search(99) ? "found" : "not found") << "\n";

    list.remove(20);
    std::cout << "After remove(20):\n  ";
    list.print();
    std::cout << "Size: " << list.getSize() << "\n";
}

void demoDoublyLinkedList() {
    printSection("Doubly Linked List");

    DoublyLinkedList<int> list;
    list.append(10);
    list.append(20);
    list.append(30);
    list.prepend(5);

    std::cout << "Forward:  ";
    list.printForward();
    std::cout << "Backward: ";
    list.printBackward();

    list.remove(5);
    list.remove(30);
    std::cout << "After remove(5) and remove(30) — Forward: ";
    list.printForward();
}

void demoStack() {
    printSection("Stack (LIFO)");

    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << "After push(1,2,3):\n  ";
    stack.print();

    std::cout << "Peek: " << stack.peek() << "\n";
    std::cout << "Pop:  " << stack.pop()  << "\n";
    std::cout << "Pop:  " << stack.pop()  << "\n";
    std::cout << "After two pops:\n  ";
    stack.print();

    Stack<int> empty;
    try {
        empty.pop();
    } catch (const std::underflow_error& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
}

void demoQueue() {
    printSection("Queue (FIFO)");

    Queue<std::string> queue;
    queue.enqueue("Alice");
    queue.enqueue("Bob");
    queue.enqueue("Carol");
    std::cout << "After enqueue(Alice, Bob, Carol):\n  ";
    queue.print();

    std::cout << "Front: " << queue.front() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "Dequeue: " << queue.dequeue() << "\n";
    std::cout << "After two dequeues:\n  ";
    queue.print();
}

void demoBST() {
    printSection("Binary Search Tree");

    BinarySearchTree<int> bst;
    for (int v : {50, 30, 70, 20, 40, 60, 80})
        bst.insert(v);

    std::cout << "Tree structure:\n";
    bst.print();
    std::cout << "\n";

    bst.inorder();
    bst.preorder();
    bst.postorder();

    std::cout << "Search 40: " << (bst.search(40) ? "found" : "not found") << "\n";
    std::cout << "Search 99: " << (bst.search(99) ? "found" : "not found") << "\n";

    bst.remove(30);
    std::cout << "\nAfter remove(30) — ";
    bst.inorder();
}

void demoSorting() {
    printSection("Sorting Algorithms");

    const std::vector<int> original = {64, 34, 25, 12, 22, 11, 90};
    printVec("Original     ", original);

    auto run = [&](const std::string& name, auto sortFn) {
        std::vector<int> arr = original;
        sortFn(arr);
        printVec(name, arr);
    };

    run("Bubble Sort  ", Sorting::bubbleSort<int>);
    run("Selection    ", Sorting::selectionSort<int>);
    run("Insertion    ", Sorting::insertionSort<int>);
    run("Merge Sort   ", Sorting::mergeSort<int>);
    run("Quick Sort   ", Sorting::quickSort<int>);
}

// ── New demos ─────────────────────────────────────────────────────────────────

void demoDeque() {
    printSection("Deque (Double-Ended Queue)");

    Deque<int> dq;
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);
    dq.push_front(1);
    std::cout << "After push_back(10,20) and push_front(5,1):\n  ";
    dq.print();

    std::cout << "Front: " << dq.front() << "  Back: " << dq.back() << "\n";
    std::cout << "pop_front: " << dq.pop_front() << "\n";
    std::cout << "pop_back:  " << dq.pop_back()  << "\n";
    std::cout << "After one pop from each end:\n  ";
    dq.print();
}

void demoCircularBuffer() {
    printSection("Circular Buffer (Ring Buffer)");

    CircularBuffer<int> buf(5);
    buf.push(1);
    buf.push(2);
    buf.push(3);
    buf.print();

    std::cout << "Pop: " << buf.pop() << "\n";
    buf.push(4);
    buf.push(5);
    buf.push(6);
    buf.print();

    // Overflow is caught cleanly.
    try {
        buf.push(7);
    } catch (const std::overflow_error& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
}

void demoAVLTree() {
    printSection("AVL Tree (Self-Balancing BST)");

    AVLTree<int> avl;
    // Inserting in ascending order would degenerate a plain BST to O(n),
    // but the AVL tree auto-balances via rotations.
    for (int v : {10, 20, 30, 40, 50, 25})
        avl.insert(v);

    std::cout << "Tree (height=" << avl.height() << "):\n";
    avl.print();
    avl.inorder();

    avl.remove(30);
    std::cout << "\nAfter remove(30) — height=" << avl.height() << ":\n";
    avl.print();
}

void demoHeap() {
    printSection("Heap — MinHeap and MaxHeap");

    MinHeap<int> minH;
    for (int v : {5, 3, 8, 1, 7, 2}) minH.insert(v);
    std::cout << "MinHeap peek: " << minH.peek() << "\n";
    std::cout << "Extract order: ";
    while (!minH.isEmpty()) std::cout << minH.extractTop() << " ";
    std::cout << "\n";

    MaxHeap<int> maxH;
    for (int v : {5, 3, 8, 1, 7, 2}) maxH.insert(v);
    std::cout << "MaxHeap peek: " << maxH.peek() << "\n";
    std::cout << "Extract order: ";
    while (!maxH.isEmpty()) std::cout << maxH.extractTop() << " ";
    std::cout << "\n";

    // O(n) buildHeap from an existing vector.
    MinHeap<int> built(std::vector<int>{9, 4, 7, 1, 6, 3});
    std::cout << "MinHeap built from {9,4,7,1,6,3} — peek: " << built.peek() << "\n";
}

void demoHashTable() {
    printSection("Hash Table (Separate Chaining)");

    HashTable<std::string, int> table;
    table.insert("alice",  30);
    table.insert("bob",    25);
    table.insert("carol",  35);
    table.insert("dave",   28);
    table.print();

    std::cout << "get(\"alice\"): " << table.get("alice") << "\n";
    std::cout << "contains(\"bob\"): " << (table.contains("bob") ? "yes" : "no") << "\n";

    table.remove("bob");
    std::cout << "After remove(\"bob\") — contains: "
              << (table.contains("bob") ? "yes" : "no") << "\n";

    // Update an existing key.
    table.insert("alice", 31);
    std::cout << "After update alice=31 — get: " << table.get("alice") << "\n";
}

void demoTrie() {
    printSection("Trie (Prefix Tree)");

    Trie trie;
    for (const std::string& w : {"apple", "app", "application", "apply", "apt", "banana"})
        trie.insert(w);
    trie.print();

    std::cout << "search(\"app\"):       " << (trie.search("app")    ? "found" : "not found") << "\n";
    std::cout << "search(\"ap\"):        " << (trie.search("ap")     ? "found" : "not found") << "\n";
    std::cout << "startsWith(\"app\"):   " << (trie.startsWith("app")? "yes"   : "no")        << "\n";

    std::cout << "autocomplete(\"app\"): ";
    for (const std::string& s : trie.autocomplete("app")) std::cout << s << " ";
    std::cout << "\n";

    trie.remove("app");
    std::cout << "After remove(\"app\") — search(\"app\"):   "
              << (trie.search("app")   ? "found" : "not found") << "\n";
    std::cout << "After remove(\"app\") — search(\"apple\"): "
              << (trie.search("apple") ? "found" : "not found") << "\n";
}

void demoGraph() {
    printSection("Graph — BFS / DFS / Dijkstra");

    //  Graph:
    //   1 --4-- 2
    //   |       |
    //   2       5
    //   |       |
    //   3 --1-- 4 --2-- 5
    //       \--3--/
    Graph<int> g(false);  // undirected
    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 1);
    g.addEdge(3, 5, 3);
    g.addEdge(4, 5, 2);
    g.print();

    auto bfsResult = g.bfs(1);
    std::cout << "BFS from 1: ";
    for (int v : bfsResult) std::cout << v << " ";
    std::cout << "\n";

    auto dfsResult = g.dfs(1);
    std::cout << "DFS from 1: ";
    for (int v : dfsResult) std::cout << v << " ";
    std::cout << "\n";

    std::cout << "Dijkstra shortest distances from 1:\n";
    for (auto& kv : g.dijkstra(1))
        std::cout << "  1 -> " << kv.first << " = " << kv.second << "\n";
}

void demoUnionFind() {
    printSection("Union-Find (Disjoint Set)");

    UnionFind<int> uf;
    for (int i = 1; i <= 6; ++i) uf.makeSet(i);
    std::cout << "Initial components: " << uf.getComponents() << "\n";

    uf.unionSets(1, 2);
    uf.unionSets(3, 4);
    uf.unionSets(5, 6);
    std::cout << "After union(1,2), union(3,4), union(5,6): "
              << uf.getComponents() << " components\n";

    uf.unionSets(1, 4);
    std::cout << "After union(1,4): " << uf.getComponents() << " components\n";

    std::cout << "connected(1, 3): " << (uf.connected(1, 3) ? "yes" : "no") << "\n";
    std::cout << "connected(1, 5): " << (uf.connected(1, 5) ? "yes" : "no") << "\n";
    uf.print();
}

// ── Entry point ───────────────────────────────────────────────────────────────

int main() {
    std::cout << "C++ Data Structures — Complete Library Demo\n";

    // ── Original six ────────────────────────────────────────
    demoLinkedList();
    demoDoublyLinkedList();
    demoStack();
    demoQueue();
    demoBST();
    demoSorting();

    // ── Eight additions ──────────────────────────────────────
    demoDeque();
    demoCircularBuffer();
    demoAVLTree();
    demoHeap();
    demoHashTable();
    demoTrie();
    demoGraph();
    demoUnionFind();

    std::cout << "\n" << std::string(60, '=') << "\n";
    std::cout << "  All 14 demos completed successfully.\n";
    std::cout << std::string(60, '=') << "\n";
    return 0;
}
