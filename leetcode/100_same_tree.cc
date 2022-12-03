/*
Given the roots of two binary trees p and q, write a function to check if they
are the same or not.

Two binary trees are considered the same if they are structurally identical, and
the nodes have the same value.
*/

// * Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    bool IsSameTree(TreeNode* p, TreeNode* q) {
        // pass

        if (p == nullptr && q == nullptr) {
            return true;
        }
        if (p == nullptr && q != nullptr) {
            return false;
        }
        if (p != nullptr && q == nullptr) {
            return false;
        }
        if (p->val == q->val) {
            return IsSameTree(p->left, q->left) &&
                   IsSameTree(p->right, q->right);
        }
        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

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

TreeNode* AddToRoot(TreeNode* root, const std::vector<int>& elements) {
    for (auto& ptr : elements) {
        root = AddToRoot(root, ptr);
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

TEST(memleak, t0) {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    TreeNode* root = ConstructTree(p);

    TreeNode* root2 = ConstructTree(q);
    FreeRoot(root);
    FreeRoot(root2);
}

TEST(t0, t1) {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    TreeNode* root1 = ConstructTree(p);
    TreeNode* root2 = ConstructTree(q);
    bool expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST(t0, t2) {
    std::vector<int> p = {1, 2}, q = {1, 2};
    TreeNode* root1 = ConstructTree(p);
    TreeNode* root2 = ConstructTree(q);
    bool expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST(t0, t3) {
    std::vector<int> p = {1, 2, 1}, q = {1, 1, 2};

    TreeNode* root1 = ConstructTree(p);
    TreeNode* root2 = ConstructTree(q);
    bool expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeRoot(root1);
    FreeRoot(root2);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
