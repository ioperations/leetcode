// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of a binary tree, return the sum of all left leaves.

A leaf is a node with no children. A left leaf is a leaf that is the left child
of another node.
*/

//* Definition for a binary tree node.
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    int SumOfLeftLeaves(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        if (root->left) {
            if (root->left->left == nullptr && root->left->right == nullptr) {
                return root->left->val + SumOfLeftLeaves(root->right);
            }
            return SumOfLeftLeaves(root->left) + SumOfLeftLeaves(root->right);
        }
        if (root->left == nullptr) {
            return SumOfLeftLeaves(root->right);
        }
        return SumOfLeftLeaves(root->right) + SumOfLeftLeaves(root->left);
    }
};

TreeNode* AddToRoot(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode* head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode(val);

    } else {
        if (root->right) {
            TreeNode* head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode(val);
    }
    return root;
}

TreeNode* ConstructTree(const std::vector<int>& elements) {
    if (!elements.size()) {
        return nullptr;
    }

    auto* root = new TreeNode(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
    }

    return root;
}

void FreeRoot(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

TEST(sum_of_left_leaves, t1) {
    const std::vector<int> elements = {7, 3, 20, 15, 9};
    TreeNode* root = ConstructTree(elements);
    Solution s;
    const int ret = s.SumOfLeftLeaves(root);
    EXPECT_EQ(ret, 12);

    FreeRoot(root);
}

TEST(sum_of_left_leaves, t3) {
    const std::vector<int> elements = {1, 2, 3, 4, 5};
    TreeNode* root = ConstructTree(elements);
    Solution s;
    const int ret = s.SumOfLeftLeaves(root);
    EXPECT_EQ(ret, 0);

    FreeRoot(root);
}

TEST(sum_of_left_leaves, t2) {
    const std::vector<int> elements = {1};
    TreeNode* root = ConstructTree(elements);
    Solution s;
    const int ret = s.SumOfLeftLeaves(root);
    EXPECT_EQ(ret, 0);

    FreeRoot(root);
}

}  // namespace
