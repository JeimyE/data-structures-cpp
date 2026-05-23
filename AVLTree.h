#pragma once
#include <iostream>
#include <algorithm>
#include <string>

// AVL tree — a self-balancing BST that keeps |height(left) - height(right)| <= 1
// at every node via rotations, guaranteeing O(log n) for all operations.
template <typename T>
class AVLTree {
private:
    struct Node {
        T    data;
        Node* left;
        Node* right;
        int  height;
        explicit Node(const T& value)
            : data(value), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root;

    // ── Height helpers ──────────────────────────────────────────────────────

    int height(Node* n) const { return n ? n->height : -1; }

    // Positive = right-heavy, negative = left-heavy.
    int balanceFactor(Node* n) const {
        return n ? height(n->right) - height(n->left) : 0;
    }

    void updateHeight(Node* n) {
        if (n) n->height = 1 + std::max(height(n->left), height(n->right));
    }

    // ── Rotations ───────────────────────────────────────────────────────────
    //
    //  Right rotation (fix left-heavy node y):
    //       y              x
    //      / \            / \
    //     x   C   →      A   y
    //    / \                / \
    //   A   B              B   C

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* B = x->right;
        x->right = y;
        y->left  = B;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    //  Left rotation (fix right-heavy node x):
    //    x                y
    //   / \              / \
    //  A   y    →       x   C
    //     / \          / \
    //    B   C        A   B

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* B = y->left;
        y->left  = x;
        x->right = B;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    // Rebalances n if needed and updates its height. Returns the new subtree root.
    Node* rebalance(Node* n) {
        updateHeight(n);
        int bf = balanceFactor(n);

        if (bf > 1) {                                // right-heavy
            if (balanceFactor(n->right) < 0)         // right-left case
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        if (bf < -1) {                               // left-heavy
            if (balanceFactor(n->left) > 0)          // left-right case
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        return n;
    }

    // ── Core recursive operations ────────────────────────────────────────────

    Node* insert(Node* n, const T& value) {
        if (!n) return new Node(value);
        if      (value < n->data) n->left  = insert(n->left,  value);
        else if (value > n->data) n->right = insert(n->right, value);
        // Duplicates are silently ignored.
        return rebalance(n);
    }

    Node* findMin(Node* n) const {
        while (n->left) n = n->left;
        return n;
    }

    Node* remove(Node* n, const T& value) {
        if (!n) return nullptr;
        if      (value < n->data) n->left  = remove(n->left,  value);
        else if (value > n->data) n->right = remove(n->right, value);
        else {
            if (!n->left)  { Node* r = n->right; delete n; return r; }
            if (!n->right) { Node* l = n->left;  delete n; return l; }
            // Replace with inorder successor (smallest in right subtree).
            Node* succ = findMin(n->right);
            n->data  = succ->data;
            n->right = remove(n->right, succ->data);
        }
        return rebalance(n);
    }

    bool search(Node* n, const T& value) const {
        if (!n) return false;
        if (value == n->data) return true;
        return value < n->data ? search(n->left, value) : search(n->right, value);
    }

    void inorder(Node* n) const {
        if (!n) return;
        inorder(n->left);
        std::cout << n->data << " ";
        inorder(n->right);
    }

    void preorder(Node* n) const {
        if (!n) return;
        std::cout << n->data << " ";
        preorder(n->left);
        preorder(n->right);
    }

    void postorder(Node* n) const {
        if (!n) return;
        postorder(n->left);
        postorder(n->right);
        std::cout << n->data << " ";
    }

    // Prints a 90°-rotated ASCII tree (right subtree at top).
    void printTree(Node* n, int indent, bool isRight) const {
        if (!n) return;
        printTree(n->right, indent + 4, true);
        std::cout << std::string(indent, ' ');
        if (indent > 0) std::cout << (isRight ? "/" : "\\") << "-- ";
        std::cout << n->data << " (h=" << n->height << ")\n";
        printTree(n->left, indent + 4, false);
    }

    void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clear(root); }

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    // Inserts a value, rebalancing as needed. Duplicates are ignored.
    void insert(const T& value) { root = insert(root, value); }

    // Removes the value if it exists, rebalancing as needed.
    void remove(const T& value) { root = remove(root, value); }

    // Returns true if the value exists in the tree.
    bool search(const T& value) const { return search(root, value); }

    void inorder()   const { std::cout << "Inorder:   "; inorder(root);   std::cout << "\n"; }
    void preorder()  const { std::cout << "Preorder:  "; preorder(root);  std::cout << "\n"; }
    void postorder() const { std::cout << "Postorder: "; postorder(root); std::cout << "\n"; }

    // Prints an ASCII diagram of the tree, annotated with node heights.
    void print() const { printTree(root, 0, false); }

    // Returns the height of the root (-1 for an empty tree).
    int  height()  const { return height(root); }
    bool isEmpty() const { return root == nullptr; }
};
