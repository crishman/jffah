#ifndef JFFMAH_BST_HPP
#define JFFMAH_BST_HPP

#include <iostream>
#include <memory>
#include <optional>

namespace jffah {

template <typename T>
class BST {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(T val) : data(val), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root_;

    void insert_recursive(std::unique_ptr<Node>& node, T val) {
        if (!node) {
            node = std::make_unique<Node>(val);
            return;
        }
        if (val < node->data) {
            insert_recursive(node->left, val);
        } else if (val > node->data) {
            insert_recursive(node->right, val);
        } // Duplicate values are ignored for simplicity
    }

    bool find_recursive(const std::unique_ptr<Node>& node, T val) const {
        if (!node) {
            return false;
        }
        if (val == node->data) {
            return true;
        }
        return val < node->data ? find_recursive(node->left, val) : find_recursive(node->right, val);
    }

    void print_inorder_recursive(const std::unique_ptr<Node>& node) const {
        if (node) {
            print_inorder_recursive(node->left);
            std::cout << node->data << " ";
            print_inorder_recursive(node->right);
        }
    }

public:
    BST() : root_(nullptr) {}

    void insert(T val) {
        insert_recursive(root_, val);
    }

    bool find(T val) const {
        return find_recursive(root_, val);
    }

    void print_inorder() const {
        print_inorder_recursive(root_);
        std::cout << std::endl;
    }
};

} // namespace jffah

#endif // JFFMAH_BST_HPP 