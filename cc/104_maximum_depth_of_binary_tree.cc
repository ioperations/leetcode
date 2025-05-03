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
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;
namespace {
class Solution {
   public:
    template <typename T>
    int MaxDepth(TreeNode<T>* root) {
        Z(root, 1);

        return m_ret;
    }

    template <typename T>
    void Z(TreeNode<T>* root, int n) {
        if (root == nullptr) return;
        if (n > m_ret) m_ret = n;
        Z(root->left, n + 1);
        Z(root->right, n + 1);
    }

   private:
    int m_ret = 0;
};
#include <optional>

using namespace std;

TEST(memleak, t0) {
    vector<optional<int>> const elements{
        3, 9, 20, optional<int>(), optional<int>(), 15, 7};
    auto* binary_tree = ConstructBinaryTree(elements);
    FreeTreeNode(binary_tree);
}

TEST(maximum_depth_of_binary_tree, t1) {
    vector<optional<int>> const elements{
        3, 9, 20, optional<int>(), optional<int>(), 15, 7};
    auto* binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int const ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 3);
    FreeTreeNode(binary_tree);
}

TEST(maximum_depth_of_binary_tree, t2) {
    vector<optional<int>> const elements{1, optional<int>(), 2};
    auto* binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int const ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 2);
    FreeTreeNode(binary_tree);
}

}  // namespace
