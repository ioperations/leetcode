// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of a binary tree, determine if it is a valid binary search tree
(BST).

A valid BST is defined as follows:

The left subtree of a node contains only nodes with keys less than the node's
key. The right subtree of a node contains only nodes with keys greater than the
node's key. Both the left and right subtrees must also be binary search trees.
*/

//* Definition for a binary tree node.
#include <limits.h>

#include <functional>
#include <limits>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    bool IsValidBstV2(TreeNode* root) {
        std::vector<int> z;
        Solve(root, z);

        for (int i = 0; i < (int)(z.size() - 1); i++) {
            if (z[i] >= z[i + 1]) {
                return false;
            }
        }
        return true;
    }
    bool IsBst(TreeNode* root, long min, long max) {
        // top to bottom approach

        // base case
        if (root == nullptr) {
            return true;
        }
        // check BST condition for root node
        if (root->val <= min || root->val >= max) {
            return false;
        }
        // check for left side
        // left side value can be within -ve infinity value to less than root
        // value
        bool is_left_part_bst = IsBst(root->left, min, root->val);
        // check for right side
        // right side value can be within greater than root value to +ve
        // infinity
        bool is_right_part_bst = IsBst(root->right, root->val, max);

        // tree is a BST if both sides are BST
        return is_left_part_bst && is_right_part_bst;
    }
    bool IsValidBst(TreeNode* root) { return IsBst(root, LONG_MIN, LONG_MAX); }

    bool IsValidBstV1(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        if (root->left) {
            if (!(root->left->val < root->val)) {
                return false;
            }
        }
        if (root->right) {
            if (!(root->right->val > root->val)) {
                return false;
            }
        }
        return IsValidBst(root->left) && IsValidBst(root->right);
    }

    void Solve(TreeNode* root, std::vector<int>& z) {
        if (root == nullptr) {
            return;
        }

        z.push_back(root->val);
        Solve(root->left, z);
        Solve(root->right, z);
    }

    bool IsValidBstV3(TreeNode* root) {
        if (root == nullptr) return true;
        std::function<bool(TreeNode*, int, int)> fun =
            [&](TreeNode* n, int left, int right) -> bool {
            if (root == nullptr) return true;

            if (n->val > right || n->val < left) {
                return false;
            }

            return fun(n->left, left, n->val) && fun(n->right, n->val, right);
            return true;
        };
        return fun(root, std::numeric_limits<int>::min(),
                   std::numeric_limits<int>::max());
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

    TreeNode* root = new TreeNode(elements[0]);

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

TEST(validate_binary_search_tree, t1) {
    std::vector<int> root = {2, 1, 3};
    bool output = true;
    TreeNode* head = ConstructTree(root);

    Solution sl;
    bool ret = sl.IsValidBst(head);
    EXPECT_EQ(ret, output);
    FreeRoot(head);
}

TEST(validate_binary_search_tree, t2) {
    // std::vector<int> root = {5,1,4,null,null,3,6};
    TreeNode head(5);
    TreeNode n1(1);
    TreeNode n2(4);
    head.left = &n1;
    head.right = &n2;

    TreeNode n3(3);
    TreeNode n4(6);

    n2.left = &n3;
    n2.right = &n4;

    Solution sl;
    bool ret = sl.IsValidBst(&head);
    EXPECT_EQ(ret, false);

    // Explanation: The root node's value is 5 but its right child's value is 4.
}

TEST(validate_binary_search_tree, t3) {
    // std::vector<int> root = {5,1,4,null,null,3,6};
    TreeNode head(5);
    TreeNode n1(4);
    TreeNode n2(6);
    head.left = &n1;
    head.right = &n2;

    TreeNode n3(3);
    TreeNode n4(7);

    n2.left = &n3;
    n2.right = &n4;

    Solution sl;
    bool ret = sl.IsValidBst(&head);
    EXPECT_EQ(ret, false);

    // Explanation: The root node's value is 5 but its right child's value is 4.
}

}  // namespace
