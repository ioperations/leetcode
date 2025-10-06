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
#include "gtest/gtest.h"

using namespace Tree;

namespace {

template <typename T>
class Solution {
   public:
    TreeNode<T>* m_prev = nullptr;
    TreeNode<T>* m_first = nullptr;
    TreeNode<T>* m_second = nullptr;
    void RecoverTree(TreeNode<T>* root) {
        Inorder(root);
        std::swap(m_first->val, m_second->val);
    }

    void Inorder(TreeNode<T>* root) {
        if (root == nullptr) return;

        Inorder(root->left);

        if (m_prev != nullptr && root->val < m_prev->val) {
            if (m_first == nullptr) {
                m_first = m_prev;
            }
            m_second = root;
        }
        m_prev = root;
        Inorder(root->right);
    }
};

#include <optional>
#include <vector>

using namespace std;
#define null std::nullopt

TEST(recover_binary_search_tree, t1) {
    vector<optional<int>> const root = {1, 3, null, null, 2};
    vector<optional<int>> const output = {3, 1, null, null, 2};
    // Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1
    // and 3 makes the BST valid.
    vector<int> in;
    {
        auto* input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        TreeNode<int>* out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

TEST(recover_binary_search_tree, t2) {
    vector<optional<int>> const root = {3, 1, 4, null, null, 2};
    vector<optional<int>> const output = {2, 1, 4, null, null, 3};
    // 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3
    // makes the BST valid.

    vector<int> in;
    {
        auto* input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        auto* out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

}  // namespace
