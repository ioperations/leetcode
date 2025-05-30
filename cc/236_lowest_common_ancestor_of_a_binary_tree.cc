// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”*/

// Definition for a binary tree node.
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    TreeNode<T>* LowestCommonAncestor(TreeNode<T>* root, TreeNode<T>* p,
                                      TreeNode<T>* q) {
        // pass
        if (root == nullptr) return nullptr;

        if (root->val == p->val || root->val == q->val) return root;

        auto* a = LowestCommonAncestor(root->left, p, q);
        auto* b = LowestCommonAncestor(root->right, p, q);

        if (a != nullptr && b != nullptr) return root;
        if (a == nullptr && b != nullptr) return b;
        if (a != nullptr && b == nullptr) return a;

        return nullptr;
    }
};

#include <optional>
#include <vector>

using namespace std;

TEST(lowest_common_ancestor_of_a_binary_tree, t1) {
#define null optional<int>()
    vector<optional<int>> const root = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    int p = 5, q = 1;
    int const output = 3;
    auto* node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    auto* pn = FindInTree(node, p);
    auto* qn = FindInTree(node, q);
    auto* ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

TEST(lowest_common_ancestor_of_a_binary_tree, t2) {
#define null optional<int>()
    vector<optional<int>> const root = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    int p = 5, q = 4;
    int const output = 5;
    auto* node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    auto* pn = FindInTree(node, p);
    auto* qn = FindInTree(node, q);
    auto* ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

TEST(lowest_common_ancestor_of_a_binary_tree, t3) {
#define null optional<int>()
    vector<optional<int>> const root = {1, 2};
    int p = 1, q = 2;
    int const output = 1;
    auto* node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    auto* pn = FindInTree(node, p);
    auto* qn = FindInTree(node, q);
    auto* ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

}  // namespace
