// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <functional>
#include <vector>
#include <string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

#include <queue>

#include "gtest/gtest.h"

namespace { 
class Solution {
   public:
    int KthSmallest(TreeNode *root, int k) {
        // pass

        std::priority_queue<int, std::vector<int>, std::greater<int>> q;

        Inorder(root, q);

        for (int i = 1; q.size() && i < k; i++) {
            q.pop();
        }

        return q.top();
    }

    void Inorder(
        TreeNode *root,
        std::priority_queue<int, std::vector<int>, std::greater<int>> &q) {
        if (root == nullptr) {
            return;
        }

        q.push(root->val);
        Inorder(root->left, q);
        Inorder(root->right, q);
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

TreeNode *AddToRoot(TreeNode *root, const std::vector<int> &elements) {
    for (auto &ptr : elements) {
        root = AddToRoot(root, ptr);
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



TEST(t0, t1) {
    std::vector<int> root = {3, 1, 4, 2};
    int k = 1;

    TreeNode *head = ConstructTree(root);
    Solution s;
    int ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 1);
    FreeRoot(head);
}

TEST(t0, t2) {
    std::vector<int> root = {5, 3, 6, 2, 4, 1};
    int k = 3;

    TreeNode *head = ConstructTree(root);
    Solution s;
    int ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 3);
    FreeRoot(head);
}

}
