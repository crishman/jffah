#include <iostream>
#include "jffah/trees/bst.hpp"

int main() {
    jffah::BST<int> tree;

    std::cout << "Inserting 10, 5, 15, 3, 7 into the BST." << std::endl;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    std::cout << "BST in-order traversal: ";
    tree.print_inorder(); // Expected output: 3 5 7 10 15

    int val_to_find = 7;
    std::cout << "Finding value " << val_to_find << ": " 
              << (tree.find(val_to_find) ? "Found" : "Not found") << std::endl;

    val_to_find = 12;
    std::cout << "Finding value " << val_to_find << ": " 
              << (tree.find(val_to_find) ? "Found" : "Not found") << std::endl;

    return 0;
} 