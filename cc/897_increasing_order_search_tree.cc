// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
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
#include <vector>
#include <string>

#include "gtest/gtest.h"

namespace {

class Solution {
   public:
    TreeNode *IncreasingBst(TreeNode *root) {
        if (root == nullptr) {
            return nullptr;
        }

        TreeNode *right = IncreasingBst(root->right);
        TreeNode *left = IncreasingBst(root->left);
        if (left != nullptr) {
            TreeNode *left_it = left;
            while (left_it->right != nullptr) {
                left_it = left_it->right;
            }
            left_it->right = root;
            root->right = right;
            root->left = nullptr;
            return left;
        }

        root->left = nullptr;
        root->right = right;

        return root;
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

void FreeRoot(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

/**
 * @brief 向 @root 当中加入节点
 * @param @elements 节点的数组
 * @return
 */
TreeNode *AddToRoot(TreeNode *root, const std::vector<int> &elements) {
    for (auto &ptr : elements) {
        root = AddToRoot(root, ptr);
    }

    return root;
}

std::vector<int> BFS(TreeNode *root) {
    std::vector<int> ret;
    std::queue<TreeNode *> q;

    q.push(root);

    while (!q.empty()) {
        auto *c = q.front();
        if (c != nullptr) {
            q.push(c->left);
            q.push(c->right);
        }

        q.pop();

        if (c != nullptr) {
            ret.push_back(c->val);
        }
    }
    return ret;
}

TEST(memleak, t1) {
    TreeNode *root = new TreeNode(-1);

    for (int i = 0; i < 100; i++) {
        root = AddToRoot(root, i);
    }

    FreeRoot(root);
}
TEST(t0, t1) {
    TreeNode *root = new TreeNode(5);

    root = AddToRoot(root, (std::vector<int>{3, 6, 2, 4, 8, 1, 7, 9}));
    Solution s;
    root = s.IncreasingBst(root);
    auto ret = BFS(root);
    EXPECT_EQ(ret, (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}));

    FreeRoot(root);
}

TEST(t0, t2) {
    TreeNode *root = new TreeNode(5);

    root = AddToRoot(root, (std::vector<int>{1, 7}));
    Solution s;
    root = s.IncreasingBst(root);
    auto ret = BFS(root);
    EXPECT_EQ(ret, (std::vector<int>{1, 5, 7}));

    FreeRoot(root);
}

}  // namespace
