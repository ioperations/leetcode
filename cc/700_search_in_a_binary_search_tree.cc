// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree
rooted with that node. If such a node does not exist, return null.
*/

#include "datastruct_base.hh"
using namespace Tree;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    template <typename T>
    TreeNode<T> *SearchBst(TreeNode<T> *root, T val) {
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

#include <gtest/gtest.h>

TEST(t0, t1) {
    std::vector<int> v{4, 2, 7, 1, 3};
    int val = 2;
    std::vector<int> expected{2, 1, 3};

    TreeNode<int> *node = ConstructTree(v);
    Solution sl;
    auto *out = sl.SearchBst(node, val);

    (void)out;
    FreeRoot(node);
}

TEST(t0, t2) {
    std::vector<int> v{4, 2, 7, 1, 3};
    int val = 5;
    std::vector<int> expected{};

    TreeNode<int> *node = ConstructTree(v);
    Solution sl;
    auto *out = sl.SearchBst(node, val);
    EXPECT_EQ(out, nullptr);

    FreeRoot(node);
}

}
