// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**Given the root of a binary tree, return the zigzag level order traversal of
 * its nodes' values. (i.e., from left to right, then right to left for the next
 * level and alternate between).*/

//* Definition for a binary tree node.
#include <algorithm>
#include <cstddef>
#include <optional>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    vector<vector<int>> ZigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (root == nullptr) return ret;

        AddToRet(root, ret, 0);
        for (size_t i = 1; i < ret.size(); i += 2) {
          reverse(ret.at(i).begin(), ret.at(i).end());
        }
        return ret;
    }

    void AddToRet(TreeNode* root, vector<vector<int>>& ret, size_t n = 0) {
        if (root) {
          if (ret.size() <= n) ret.resize(n + 1);
          ret.at(n).push_back(root->val);

          AddToRet(root->left, ret, n + 1);
          AddToRet(root->right, ret, n + 1);
        }
    }
};

TEST(Memleak, t0) {
    vector<optional<int>> const elements{
        3, 9, 20, optional<int>(), optional<int>(), 15, 7};
    auto* binary_tree = Tree::ConstructBinaryTree(elements);
    Tree::FreeTreeNode(binary_tree);
}

TEST(BinaryTreeZigzagLevelOrderTraversal, t1) {
    vector<optional<int>> const elements{
        3, 9, 20, optional<int>(), optional<int>(), 15, 7};
    auto* binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> const output{{3}, {20, 9}, {15, 7}};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}

TEST(BinaryTreeZigzagLevelOrderTraversal, t2) {
    vector<optional<int>> const elements{1};
    auto* binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> const output{{1}};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}

TEST(BinaryTreeZigzagLevelOrderTraversal, t3) {
    vector<optional<int>> const elements{};
    auto* binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> const output{};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}
}  // namespace
