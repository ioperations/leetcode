// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree
rooted with that node. If such a node does not exist, return null.
*/

#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    TreeNode<T>* SearchBst(TreeNode<T>* root, T val) {
        if (root == nullptr) return nullptr;

        if (val < root->val) {
            return SearchBst(root->left, val);
        }
        if (val > root->val) {
            return SearchBst(root->right, val);
        }
        if (val == root->val) {
            return root;
        }
        return nullptr;
    }
};

TEST(search_in_a_binary_search_tree, t1) {
    std::vector<int> const v{4, 2, 7, 1, 3};
    int const val = 2;
    std::vector<int> const expected{2, 1, 3};

    TreeNode<int>* node = ConstructTree(v);
    Solution sl;
    auto* out = sl.SearchBst(node, val);

    (void)out;
    FreeTreeNode(node);
}

TEST(search_in_a_binary_search_tree, t2) {
    std::vector<int> const v{4, 2, 7, 1, 3};
    int const val = 5;
    std::vector<int> const expected{};

    TreeNode<int>* node = ConstructTree(v);
    Solution sl;
    auto* out = sl.SearchBst(node, val);
    EXPECT_EQ(out, nullptr);

    FreeTreeNode(node);
}

}  // namespace
