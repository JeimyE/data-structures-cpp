#pragma once
#include <iostream>
#include <vector>
#include <stdexcept>

// Fixed-capacity ring buffer (FIFO).
// Uses modular arithmetic on indices — no shifting of elements needed.
// push and pop are both O(1).
template <typename T>
class CircularBuffer {
private:
    std::vector<T> buffer;
    std::size_t capacity_;
    std::size_t readIdx;   // next element to read (front)
    std::size_t writeIdx;  // next slot to write (back)
    std::size_t count;

public:
    explicit CircularBuffer(std::size_t capacity)
        : buffer(capacity), capacity_(capacity), readIdx(0), writeIdx(0), count(0) {
        if (capacity == 0) throw std::invalid_argument("CircularBuffer — capacity must be > 0");
    }

    // Adds an element to the back. Throws if the buffer is full.
    void push(const T& value) {
        if (isFull()) throw std::overflow_error("CircularBuffer::push — buffer is full");
        buffer[writeIdx] = value;
        writeIdx = (writeIdx + 1) % capacity_;
        ++count;
    }

    // Removes and returns the front element. Throws if empty.
    T pop() {
        if (isEmpty()) throw std::underflow_error("CircularBuffer::pop — buffer is empty");
        T val = buffer[readIdx];
        readIdx = (readIdx + 1) % capacity_;
        --count;
        return val;
    }

    // Returns the front element without removing it.
    const T& front() const {
        if (isEmpty()) throw std::underflow_error("CircularBuffer::front — buffer is empty");
        return buffer[readIdx];
    }

    bool isFull()  const { return count == capacity_; }
    bool isEmpty() const { return count == 0; }
    std::size_t size()     const { return count; }
    std::size_t capacity() const { return capacity_; }

    // Prints elements in order from front to back.
    void print() const {
        std::cout << "CircularBuffer [";
        for (std::size_t i = 0; i < count; ++i) {
            std::cout << buffer[(readIdx + i) % capacity_];
            if (i + 1 < count) std::cout << ", ";
        }
        std::cout << "] (" << count << "/" << capacity_ << ")\n";
    }
};
