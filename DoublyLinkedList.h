#pragma once
#include <iostream>
#include <stdexcept>

// Doubly linked list — each node holds a value plus pointers to both neighbors.
template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() { clear(); }

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    // Adds a new node at the end of the list.
    void append(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    // Adds a new node at the beginning of the list.
    void prepend(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++size;
    }

    // Removes the first node matching value. Returns true if removed.
    bool remove(const T& value) {
        Node* current = head;
        while (current && current->data != value)
            current = current->next;

        if (!current) return false;

        if (current->prev) current->prev->next = current->next;
        else head = current->next;          // removing head

        if (current->next) current->next->prev = current->prev;
        else tail = current->prev;          // removing tail

        delete current;
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

    // Traverses head → tail and prints each element.
    void printForward() const {
        Node* current = head;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " <-> ";
            current = current->next;
        }
        std::cout << "\n";
    }

    // Traverses tail → head and prints each element.
    void printBackward() const {
        Node* current = tail;
        while (current) {
            std::cout << current->data;
            if (current->prev) std::cout << " <-> ";
            current = current->prev;
        }
        std::cout << "\n";
    }

    // Alias so the interface matches LinkedList.
    void print() const { printForward(); }

    void clear() {
        while (head) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
        size = 0;
    }

    std::size_t getSize() const { return size; }
    bool isEmpty() const { return head == nullptr; }
};
