// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in
the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”

*/

//* Definition for a binary tree node.
#include <vector>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    TreeNode *Solve(TreeNode *root, int &p, int &q) {
        if (root == nullptr) return nullptr;
        if (root->val == p || root->val == q) return root;
        auto *left = Solve(root->left, p, q);
        auto *right = Solve(root->right, p, q);
        if (left == nullptr && right == nullptr) return nullptr;
        if (left != nullptr && right != nullptr) return root;
        return left != nullptr ? left : right;
    }

   public:
    // Solution() { ios::sync_with_stdio(false), cin.tie(0), cout.tie(0); }
    TreeNode *LowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        return Solve(root, p->val, q->val);
    }
};

TreeNode *AddToRoot(TreeNode *root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode *head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode(val);

    } else {
        if (root->right) {
            TreeNode *head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode(val);
    }
    return root;
}

TreeNode *ConstructTree(const std::vector<int> &elements) {
    if (!elements.size()) {
        return nullptr;
    }

    TreeNode *root = new TreeNode(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
    }

    return root;
}

void FreeRoot(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

TreeNode *FindTreeNode(TreeNode *root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (root->val == val) {
        return root;
    }
    if (root->val > val) {
        return FindTreeNode(root->left, val);
    }
    return FindTreeNode(root->right, val);
}

TEST(lowest_commom_ancestor_of_a_binary_tree, t1) {
    /**
                  ___
                 | 3 |
              ___|___|___
             /           \
            /             \
        ___/               \___
       | 5 |               | 1 |
       |___|               |___|
      /    \               /   \
    _/_     \___       ___/     \___
   | 6 |    | 2 |     | 0 |     | 8 |
   |___|    |___|     |___|     |___|
            /  \
        ___/    \___
       | 7 |    | 4 |
       |___|    |___|

    */
    std::vector<int> list = {3, 5, 1, 6, 2, 0, 8, 7, 4};
    int p = 5, q = 1;
    int expeced = 3;

    TreeNode *root = ConstructTree(list);
    Solution s;

    TreeNode *p_node = FindTreeNode(root, p), *q_node = FindTreeNode(root, q);

    auto *ret = s.LowestCommonAncestor(root, p_node, q_node);
    EXPECT_EQ(ret->val, expeced);
    FreeRoot(root);
}

TEST(lowest_commom_ancestor_of_a_binary_tree, t2) {
    /**
                  ___
                 | 3 |
              ___|___|___
             /           \
            /             \
        ___/               \___
       | 5 |               | 1 |
       |___|               |___|
      /    \               /   \
    _/_     \___       ___/     \___
   | 6 |    | 2 |     | 0 |     | 8 |
   |___|    |___|     |___|     |___|
            /  \
        ___/    \___
       | 7 |    | 4 |
       |___|    |___|

    */

    std::vector<int> list = {3, 5, 1, 6, 2, 0, 8, 7, 4};
    int p = 5, q = 4;
    int expeced = 5;

    TreeNode *root = ConstructTree(list);
    Solution s;

    TreeNode *p_node = FindTreeNode(root, p), *q_node = FindTreeNode(root, q);

    auto *ret = s.LowestCommonAncestor(root, p_node, q_node);
    EXPECT_EQ(ret->val, expeced);
    FreeRoot(root);
}

TEST(lowest_commom_ancestor_of_a_binary_tree, t3) {
    /**
                  ___
                 | 1 |
              ___|___|___
             /           \
            /             \
        ___/               \___
       |   |               | 2 |
       |___|               |___|

    */

    std::vector<int> list = {1, 2};

    int p = 1, q = 2;
    int expeced = 1;

    TreeNode *root = ConstructTree(list);
    Solution s;

    TreeNode *p_node = FindTreeNode(root, p), *q_node = FindTreeNode(root, q);

    auto *ret = s.LowestCommonAncestor(root, p_node, q_node);
    EXPECT_EQ(ret->val, expeced);
    FreeRoot(root);
}
}  // namespace
