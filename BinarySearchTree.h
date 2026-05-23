#pragma once
#include <iostream>
#include <stdexcept>

// Binary Search Tree — left subtree holds smaller values, right holds larger.
template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        explicit Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // ── Private recursive helpers ──────────────────────────────────────────

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data)       node->left  = insert(node->left,  value);
        else if (value > node->data)  node->right = insert(node->right, value);
        // Duplicate values are silently ignored.
        return node;
    }

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (value == node->data) return true;
        return value < node->data ? search(node->left, value)
                                  : search(node->right, value);
    }

    // Finds the leftmost (minimum) node in a subtree.
    Node* findMin(Node* node) const {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, const T& value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            // Found the node to delete.
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // Node has two children: replace with inorder successor.
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = remove(node->right, successor->data);
        }
        return node;
    }

    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {
        if (!node) return;
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // Prints a visual tree structure (rotated 90°, right subtree on top).
    void printTree(Node* node, int indent, bool isRight) const {
        if (!node) return;
        printTree(node->right, indent + 4, true);
        std::cout << std::string(indent, ' ');
        if (indent > 0) std::cout << (isRight ? "/" : "\\") << "-- ";
        std::cout << node->data << "\n";
        printTree(node->left, indent + 4, false);
    }

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(root); }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Inserts a value into the BST (duplicates are ignored).
    void insert(const T& value) { root = insert(root, value); }

    // Returns true if the value exists in the BST.
    bool search(const T& value) const { return search(root, value); }

    // Removes the node with the given value, if it exists.
    void remove(const T& value) { root = remove(root, value); }

    // Left → Root → Right (produces sorted order).
    void inorder() const {
        std::cout << "Inorder:   ";
        inorder(root);
        std::cout << "\n";
    }

    // Root → Left → Right.
    void preorder() const {
        std::cout << "Preorder:  ";
        preorder(root);
        std::cout << "\n";
    }

    // Left → Right → Root.
    void postorder() const {
        std::cout << "Postorder: ";
        postorder(root);
        std::cout << "\n";
    }

    // Prints an ASCII representation of the tree.
    void print() const { printTree(root, 0, false); }

    bool isEmpty() const { return root == nullptr; }
};
