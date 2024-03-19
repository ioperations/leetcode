// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from
the root node down to the farthest leaf node.

*/

#include <vector>

//* Definition for a binary tree node.
#include <catch2/catch_test_macros.hpp>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace Tree;
namespace {
class Solution {
   public:
    template <typename T>
    int MaxDepth(TreeNode<T> *root) {
        Z(root, 1);

        return ret;
    }

    template <typename T>
    void Z(TreeNode<T> *root, int n) {
        if (root == nullptr) return;
        if (n > ret) ret = n;
        Z(root->left, n + 1);
        Z(root->right, n + 1);
    }

   private:
    int ret = 0;
};
#include <optional>

using namespace std;

TEST(memleak, maximum_depth_of_binray_tree_104) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = ConstructBinaryTree(elements);
    FreeTreeNode(binary_tree);
}

TEST(maximum_depth_of_binary_tree, t1) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 3);
    FreeTreeNode(binary_tree);
}

TEST(maximum_depth_of_binary_tree, t2) {
    vector<optional<int>> elements{1, optional<int>(), 2};
    auto *binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 2);
    FreeTreeNode(binary_tree);
}

}  // namespace
