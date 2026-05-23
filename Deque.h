#pragma once
#include <iostream>
#include <stdexcept>

// Double-ended queue backed by a doubly linked list.
// push/pop at both ends are O(1).
template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t count;

public:
    Deque() : head(nullptr), tail(nullptr), count(0) {}
    ~Deque() { clear(); }

    Deque(const Deque&) = delete;
    Deque& operator=(const Deque&) = delete;

    // Adds an element to the front.
    void push_front(const T& value) {
        Node* n = new Node(value);
        if (!head) { head = tail = n; }
        else { n->next = head; head->prev = n; head = n; }
        ++count;
    }

    // Adds an element to the back.
    void push_back(const T& value) {
        Node* n = new Node(value);
        if (!tail) { head = tail = n; }
        else { n->prev = tail; tail->next = n; tail = n; }
        ++count;
    }

    // Removes and returns the front element. Throws if empty.
    T pop_front() {
        if (isEmpty()) throw std::underflow_error("Deque::pop_front — deque is empty");
        T val = head->data;
        Node* del = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete del;
        --count;
        return val;
    }

    // Removes and returns the back element. Throws if empty.
    T pop_back() {
        if (isEmpty()) throw std::underflow_error("Deque::pop_back — deque is empty");
        T val = tail->data;
        Node* del = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete del;
        --count;
        return val;
    }

    // Returns a reference to the front element without removing it.
    const T& front() const {
        if (isEmpty()) throw std::underflow_error("Deque::front — deque is empty");
        return head->data;
    }

    // Returns a reference to the back element without removing it.
    const T& back() const {
        if (isEmpty()) throw std::underflow_error("Deque::back — deque is empty");
        return tail->data;
    }

    bool isEmpty() const { return head == nullptr; }
    std::size_t getSize() const { return count; }

    // Prints all elements from front to back.
    void print() const {
        std::cout << "Front [";
        for (Node* cur = head; cur; cur = cur->next) {
            std::cout << cur->data;
            if (cur->next) std::cout << " <-> ";
        }
        std::cout << "] Back\n";
    }

    void clear() {
        while (head) {
            Node* del = head;
            head = head->next;
            delete del;
        }
        tail = nullptr;
        count = 0;
    }
};
