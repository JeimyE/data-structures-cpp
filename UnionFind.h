#pragma once
#include <iostream>
#include <unordered_map>
#include <stdexcept>

// Disjoint-set (Union-Find) with path compression and union by rank.
// find is near-O(1) amortized (inverse-Ackermann). T must be hashable.
template <typename T = int>
class UnionFind {
private:
    mutable std::unordered_map<T, T> parent;  // mutable for path compression in const find
    std::unordered_map<T, int>       rankMap;
    int components;

public:
    UnionFind() : components(0) {}

    // Registers x as its own set. No-op if already registered.
    void makeSet(const T& x) {
        if (parent.count(x)) return;
        parent[x] = x;
        rankMap[x] = 0;
        ++components;
    }

    // Returns the representative (root) of x's set.
    // Applies iterative path compression for near-O(1) future lookups.
    T find(const T& x) const {
        if (!parent.count(x))
            throw std::invalid_argument("UnionFind::find — element not registered");

        // Find root.
        T root = x;
        while (parent.at(root) != root) root = parent.at(root);

        // Path compression: point every node on the chain directly to root.
        T curr = x;
        while (curr != root) {
            T next = parent.at(curr);
            parent[curr] = root;
            curr = next;
        }
        return root;
    }

    // Merges the sets containing x and y. Uses union by rank to keep trees shallow.
    void unionSets(const T& x, const T& y) {
        T rootX = find(x);
        T rootY = find(y);
        if (rootX == rootY) return;

        if (rankMap[rootX] < rankMap[rootY]) std::swap(rootX, rootY);
        parent[rootY] = rootX;
        if (rankMap[rootX] == rankMap[rootY]) ++rankMap[rootX];
        --components;
    }

    // Returns true if x and y belong to the same set.
    bool connected(const T& x, const T& y) const { return find(x) == find(y); }

    // Returns the current number of disjoint components.
    int getComponents() const { return components; }

    // Prints each element and its current root after path compression.
    void print() const {
        std::cout << "UnionFind (" << components << " components):\n";
        for (auto& [elem, p] : parent)
            std::cout << "  " << elem << " -> root: " << find(elem) << "\n";
    }
};
