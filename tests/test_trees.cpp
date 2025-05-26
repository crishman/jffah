#include "gtest/gtest.h"
#include "jffah/trees/bst.hpp"

TEST(BSTTest, InsertAndFind) {
    jffah::BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    EXPECT_TRUE(tree.find(10));
    EXPECT_TRUE(tree.find(5));
    EXPECT_TRUE(tree.find(15));
    EXPECT_FALSE(tree.find(7));
}

TEST(BSTTest, InOrderPrint) {
    jffah::BST<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    // Redirect cout to a stringstream to capture output
    std::stringstream ss;
    std::streambuf* old_cout_buf = std::cout.rdbuf();
    std::cout.rdbuf(ss.rdbuf());

    tree.print_inorder();

    // Restore cout
    std::cout.rdbuf(old_cout_buf);

    EXPECT_EQ(ss.str(), "3 5 7 10 15 \n");
} 