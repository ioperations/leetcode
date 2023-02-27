/*
You are given the root of a binary search tree (BST) and an integer val.

Find the node in the BST that the node's value equals val and return the subtree
rooted with that node. If such a node does not exist, return null.
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
    TreeNode *SearchBst(TreeNode *root, int val) {
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

#include <iostream>

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
    std::vector<int> v{4, 2, 7, 1, 3};
    int val = 2;
    std::vector<int> expected{2, 1, 3};

    TreeNode *node = ConstructTree(v);
    Solution sl;
    auto *out = sl.SearchBst(node, val);

    (void)out;
    FreeRoot(node);
}

TEST(t0, t2) {
    std::vector<int> v{4, 2, 7, 1, 3};
    int val = 5;
    std::vector<int> expected{};

    TreeNode *node = ConstructTree(v);
    Solution sl;
    auto *out = sl.SearchBst(node, val);
    EXPECT_EQ(out, nullptr);

    FreeRoot(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
