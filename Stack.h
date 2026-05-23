#pragma once
#include <iostream>
#include <stdexcept>

// LIFO stack backed by a singly linked list — O(1) push, pop, and peek.
template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* top_node;
    std::size_t size;

public:
    Stack() : top_node(nullptr), size(0) {}

    ~Stack() { clear(); }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    Stack(Stack&& other) noexcept : top_node(other.top_node), size(other.size) {
        other.top_node = nullptr;
        other.size = 0;
    }

    // Pushes a new element onto the top of the stack.
    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = top_node;
        top_node = newNode;
        ++size;
    }

    // Removes and returns the top element. Throws if the stack is empty.
    T pop() {
        if (isEmpty()) throw std::underflow_error("Stack::pop — stack is empty");
        Node* toDelete = top_node;
        T value = toDelete->data;
        top_node = top_node->next;
        delete toDelete;
        --size;
        return value;
    }

    // Returns the top element without removing it. Throws if the stack is empty.
    const T& peek() const {
        if (isEmpty()) throw std::underflow_error("Stack::peek — stack is empty");
        return top_node->data;
    }

    bool isEmpty() const { return top_node == nullptr; }
    std::size_t getSize() const { return size; }

    // Prints all elements from top to bottom.
    void print() const {
        std::cout << "Top -> ";
        Node* current = top_node;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << "\n";
    }

    void clear() {
        while (top_node) {
            Node* toDelete = top_node;
            top_node = top_node->next;
            delete toDelete;
        }
        size = 0;
    }
};
