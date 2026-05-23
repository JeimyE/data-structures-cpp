#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <functional>
#include <stdexcept>

// Hash map with separate chaining.
// Automatically rehashes (doubles bucket count) when load factor exceeds 0.75.
// K must be hashable via std::hash<K>.
template <typename K, typename V>
class HashTable {
private:
    using Bucket = std::list<std::pair<K, V>>;

    std::vector<Bucket> buckets;
    std::size_t         numElements;
    std::size_t         numBuckets;

    static constexpr double MAX_LOAD_FACTOR = 0.75;

    std::size_t bucketIndex(const K& key) const {
        return std::hash<K>{}(key) % numBuckets;
    }

    void rehash() {
        numBuckets *= 2;
        std::vector<Bucket> newBuckets(numBuckets);
        for (auto& bucket : buckets)
            for (auto& [k, v] : bucket)
                newBuckets[std::hash<K>{}(k) % numBuckets].emplace_back(k, v);
        buckets = std::move(newBuckets);
    }

public:
    explicit HashTable(std::size_t initialBuckets = 16)
        : buckets(initialBuckets), numElements(0), numBuckets(initialBuckets) {}

    // Inserts a key-value pair. If key exists, the value is updated.
    void insert(const K& key, const V& value) {
        if (loadFactor() > MAX_LOAD_FACTOR) rehash();
        std::size_t idx = bucketIndex(key);
        for (auto& [k, v] : buckets[idx]) {
            if (k == key) { v = value; return; }
        }
        buckets[idx].emplace_back(key, value);
        ++numElements;
    }

    // Returns true if the key exists.
    bool contains(const K& key) const {
        for (auto& [k, v] : buckets[bucketIndex(key)])
            if (k == key) return true;
        return false;
    }

    // Returns a reference to the value associated with key.
    // Throws std::out_of_range if key does not exist.
    V& get(const K& key) {
        for (auto& [k, v] : buckets[bucketIndex(key)])
            if (k == key) return v;
        throw std::out_of_range("HashTable::get — key not found");
    }

    const V& get(const K& key) const {
        for (auto& [k, v] : buckets[bucketIndex(key)])
            if (k == key) return v;
        throw std::out_of_range("HashTable::get — key not found");
    }

    // Removes the entry for key. Returns true if it existed.
    bool remove(const K& key) {
        auto& bucket = buckets[bucketIndex(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --numElements;
                return true;
            }
        }
        return false;
    }

    std::size_t size()   const { return numElements; }
    bool isEmpty()       const { return numElements == 0; }
    double loadFactor()  const {
        return static_cast<double>(numElements) / static_cast<double>(numBuckets);
    }

    // Prints all non-empty buckets.
    void print() const {
        std::cout << "HashTable (" << numElements << " entries, load="
                  << loadFactor() << "):\n";
        for (std::size_t i = 0; i < numBuckets; ++i) {
            if (buckets[i].empty()) continue;
            std::cout << "  [" << i << "]: ";
            for (auto& [k, v] : buckets[i])
                std::cout << "{" << k << ":" << v << "} ";
            std::cout << "\n";
        }
    }
};
