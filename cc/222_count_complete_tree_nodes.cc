// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a complete binary tree, return the number of the nodes in
the tree.

According to Wikipedia, every level, except possibly the last, is completely
filled in a complete binary tree, and all nodes in the last level are as far
left as possible. It can have between 1 and 2h nodes inclusive at the last level
h.

Design an algorithm that runs in less than O(n) time complexity.*/

#include <queue>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    int CountNodes(TreeNode<T>* root) {
        std::queue<TreeNode<T>*> q;
        if (root == nullptr) return 0;
        q.emplace(root);
        int count = 0;
        while (!q.empty()) {
            auto* n = q.front();
            if (n->left) q.emplace(n->left);
            if (n->right) q.emplace(n->right);
            q.pop();
            count++;
        }
        return count;
    }
};

#include <optional>
#include <vector>

using namespace std;

TEST(count_complete_tree_nodes, t1) {
    vector<optional<int>> root = {1, 2, 3, 4, 5, 6};
    int output = 6;
    auto* const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(count_complete_tree_nodes, t2) {
    vector<optional<int>> root = {};
    int output = 0;
    auto* const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(count_complete_tree_nodes, t3) {
    vector<optional<int>> root = {1};
    int output = 1;
    auto* const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

}  // namespace
