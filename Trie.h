#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <array>

// Prefix tree (Trie) for lowercase ASCII strings.
// insert, search, and startsWith are O(m) where m = word length.
class Trie {
private:
    struct Node {
        std::array<Node*, 26> children;
        bool isEnd;
        Node() : children{}, isEnd(false) {}
        bool hasChildren() const {
            for (Node* c : children) if (c) return true;
            return false;
        }
    };

    Node* root;

    // Returns true when the caller should delete the child pointer.
    bool removeHelper(Node* node, const std::string& word, std::size_t depth) {
        if (depth == word.size()) {
            if (!node->isEnd) return false;
            node->isEnd = false;
            return !node->hasChildren();  // safe to delete if leaf
        }
        int idx = word[depth] - 'a';
        if (!node->children[idx]) return false;

        bool shouldDelete = removeHelper(node->children[idx], word, depth + 1);
        if (shouldDelete) {
            delete node->children[idx];
            node->children[idx] = nullptr;
        }
        return !node->isEnd && !node->hasChildren();
    }

    // Collects all words reachable from node with the given prefix.
    void collect(Node* node, std::string& prefix, std::vector<std::string>& results) const {
        if (node->isEnd) results.push_back(prefix);
        for (int i = 0; i < 26; ++i) {
            if (node->children[i]) {
                prefix.push_back(static_cast<char>('a' + i));
                collect(node->children[i], prefix, results);
                prefix.pop_back();
            }
        }
    }

    void clear(Node* node) {
        if (!node) return;
        for (Node* c : node->children) clear(c);
        delete node;
    }

public:
    Trie() : root(new Node()) {}
    ~Trie() { clear(root); }

    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Inserts a lowercase word into the trie.
    void insert(const std::string& word) {
        Node* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) cur->children[idx] = new Node();
            cur = cur->children[idx];
        }
        cur->isEnd = true;
    }

    // Returns true if the exact word exists.
    bool search(const std::string& word) const {
        Node* cur = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return cur->isEnd;
    }

    // Returns true if any stored word begins with the given prefix.
    bool startsWith(const std::string& prefix) const {
        Node* cur = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!cur->children[idx]) return false;
            cur = cur->children[idx];
        }
        return true;
    }

    // Removes the word if it exists. Returns true on success.
    bool remove(const std::string& word) {
        if (!search(word)) return false;
        removeHelper(root, word, 0);
        return true;
    }

    // Returns all stored words that start with the given prefix.
    std::vector<std::string> autocomplete(const std::string& prefix) const {
        std::vector<std::string> results;
        Node* cur = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!cur->children[idx]) return results;
            cur = cur->children[idx];
        }
        std::string p = prefix;
        collect(cur, p, results);
        return results;
    }

    // Prints all stored words in lexicographic order.
    void print() const {
        std::vector<std::string> all;
        std::string p;
        collect(root, p, all);
        std::cout << "Trie [";
        for (std::size_t i = 0; i < all.size(); ++i)
            std::cout << all[i] << (i + 1 < all.size() ? ", " : "");
        std::cout << "]\n";
    }
};
