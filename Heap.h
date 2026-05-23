#pragma once
#include <iostream>
#include <vector>
#include <functional>
#include <stdexcept>
#include <algorithm>

// Generic binary heap backed by an array.
// Compare = std::less<T>    → MinHeap (smallest element at top).
// Compare = std::greater<T> → MaxHeap (largest element at top).
//
// Core operations are O(log n); buildHeap from a vector is O(n).
template <typename T, typename Compare = std::less<T>>
class Heap {
private:
    std::vector<T> data;
    Compare        comp;

    std::size_t parent(std::size_t i) const { return (i - 1) / 2; }
    std::size_t left  (std::size_t i) const { return 2 * i + 1; }
    std::size_t right (std::size_t i) const { return 2 * i + 2; }

    // Moves element at i upward until the heap property is restored.
    void bubbleUp(std::size_t i) {
        while (i > 0) {
            std::size_t p = parent(i);
            if (comp(data[i], data[p])) {
                std::swap(data[i], data[p]);
                i = p;
            } else break;
        }
    }

    // Moves element at i downward until the heap property is restored.
    void bubbleDown(std::size_t i) {
        std::size_t n = data.size();
        while (true) {
            std::size_t best = i;
            std::size_t l = left(i), r = right(i);
            if (l < n && comp(data[l], data[best])) best = l;
            if (r < n && comp(data[r], data[best])) best = r;
            if (best == i) break;
            std::swap(data[i], data[best]);
            i = best;
        }
    }

    // Floyd's heapify — O(n) build from an existing array.
    void buildHeap() {
        if (data.size() < 2) return;
        for (int i = static_cast<int>(data.size() / 2) - 1; i >= 0; --i)
            bubbleDown(static_cast<std::size_t>(i));
    }

public:
    Heap() = default;

    // Builds a heap from an existing array in O(n).
    explicit Heap(std::vector<T> arr) : data(std::move(arr)) { buildHeap(); }

    // Inserts a value into the heap.
    void insert(const T& value) {
        data.push_back(value);
        bubbleUp(data.size() - 1);
    }

    // Removes and returns the top element (min or max). Throws if empty.
    T extractTop() {
        if (isEmpty()) throw std::underflow_error("Heap::extractTop — heap is empty");
        T top = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!isEmpty()) bubbleDown(0);
        return top;
    }

    // Returns the top element without removing it.
    const T& peek() const {
        if (isEmpty()) throw std::underflow_error("Heap::peek — heap is empty");
        return data[0];
    }

    bool isEmpty() const { return data.empty(); }
    std::size_t size() const { return data.size(); }

    // Prints elements in internal array order (heap storage layout).
    void print() const {
        std::cout << "Heap [";
        for (std::size_t i = 0; i < data.size(); ++i) {
            std::cout << data[i];
            if (i + 1 < data.size()) std::cout << ", ";
        }
        std::cout << "]  top=" << (isEmpty() ? T{} : data[0]) << "\n";
    }
};

// Convenience aliases.
template <typename T> using MinHeap = Heap<T, std::less<T>>;
template <typename T> using MaxHeap = Heap<T, std::greater<T>>;
