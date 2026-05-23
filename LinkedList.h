#pragma once
#include <iostream>
#include <stdexcept>

// Singly linked list — each node holds a value and a pointer to the next node.
template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    std::size_t size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() { clear(); }

    // Disable copy to avoid double-free; enable move semantics.
    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept : head(other.head), size(other.size) {
        other.head = nullptr;
        other.size = 0;
    }

    // Adds a new node at the end of the list.
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } else {
            Node* current = head;
            while (current->next) current = current->next;
            current->next = newNode;
        }
        ++size;
    }

    // Adds a new node at the beginning of the list.
    void prepend(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    // Removes the first node whose value matches. Returns true if removed.
    bool remove(const T& value) {
        if (!head) return false;

        if (head->data == value) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            --size;
            return true;
        }

        Node* current = head;
        while (current->next && current->next->data != value)
            current = current->next;

        if (!current->next) return false;

        Node* toDelete = current->next;
        current->next = toDelete->next;
        delete toDelete;
        --size;
        return true;
    }

    // Returns true if the list contains the given value.
    bool search(const T& value) const {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    // Prints all elements separated by " -> ", ending with "nullptr".
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr\n";
    }

    // Deletes all nodes and resets the list.
    void clear() {
        while (head) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        size = 0;
    }

    std::size_t getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }
};
