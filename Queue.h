#pragma once
#include <iostream>
#include <stdexcept>

// FIFO queue backed by a singly linked list — O(1) enqueue and dequeue.
template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        explicit Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;  // dequeue end (front)
    Node* tail;  // enqueue end (back)
    std::size_t size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue() { clear(); }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    Queue(Queue&& other) noexcept
        : head(other.head), tail(other.tail), size(other.size) {
        other.head = other.tail = nullptr;
        other.size = 0;
    }

    // Adds a new element to the back of the queue.
    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    // Removes and returns the front element. Throws if the queue is empty.
    T dequeue() {
        if (isEmpty()) throw std::underflow_error("Queue::dequeue — queue is empty");
        Node* toDelete = head;
        T value = toDelete->data;
        head = head->next;
        if (!head) tail = nullptr;  // queue became empty
        delete toDelete;
        --size;
        return value;
    }

    // Returns the front element without removing it. Throws if the queue is empty.
    const T& front() const {
        if (isEmpty()) throw std::underflow_error("Queue::front — queue is empty");
        return head->data;
    }

    bool isEmpty() const { return head == nullptr; }
    std::size_t getSize() const { return size; }

    // Prints all elements from front to back.
    void print() const {
        std::cout << "Front -> ";
        Node* current = head;
        while (current) {
            std::cout << current->data;
            if (current->next) std::cout << " -> ";
            current = current->next;
        }
        std::cout << " <- Back\n";
    }

    void clear() {
        while (head) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
        }
        tail = nullptr;
        size = 0;
    }
};
