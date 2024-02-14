// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given the root of a binary search tree (BST), where the values of
exactly two nodes of the tree were swapped by mistake. Recover the tree without
changing its structure.
*/

#include <utility>

#include "datastruct_base.hh"
using namespace Tree;
#include <gtest/gtest.h>
namespace {

template <typename T>
class Solution {
   public:
    TreeNode<T> *prev = nullptr;
    TreeNode<T> *first = nullptr;
    TreeNode<T> *second = nullptr;
    void RecoverTree(TreeNode<T> *root) {
        Inorder(root);
        std::swap(first->val, second->val);
    }

    void Inorder(TreeNode<T> *root) {
        if (root == nullptr) return;

        Inorder(root->left);

        if (prev != nullptr && root->val < prev->val) {
            if (first == nullptr) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        Inorder(root->right);
    }
};

#include <gtest/gtest.h>

#include <optional>
#include <queue>
#include <vector>
using namespace std;

TEST(t0, t1) {
#define null optional<int>()
    vector<optional<int>> root = {1, 3, null, null, 2};
    vector<optional<int>> output = {3, 1, null, null, 2};
    // Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1
    // and 3 makes the BST valid.
    vector<int> in;
    {
        auto *input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        TreeNode<int> *out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

TEST(t0, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 1, 4, null, null, 2};
    vector<optional<int>> output = {2, 1, 4, null, null, 3};
    // 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3
    // makes the BST valid.

    vector<int> in;
    {
        auto *input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        auto *out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

}  // namespace
