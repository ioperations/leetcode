/**
Given the root of a binary tree, return its maximum depth.

A binary tree's maximum depth is the number of nodes along the longest path from
the root node down to the farthest leaf node.

*/

//* Definition for a binary tree node.
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
    int MaxDepth(TreeNode* root) {
        Z(root, 1);

        return ret;
    }

    void Z(TreeNode* root, int n) {
        if (root == nullptr) return;
        if (n > ret) ret = n;
        Z(root->left, n + 1);
        Z(root->right, n + 1);
    }

   private:
    int ret = 0;
};
#include <algorithm>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using namespace std;
TreeNode* ConstructBinaryTree(vector<optional<int>>& elements) {
    if (elements.size() == 0) return nullptr;

    queue<TreeNode*> q;

    TreeNode* node = new TreeNode(elements[0].value());
    q.push(node);
    int size = elements.size();

    for (int i = 1; i < size;) {
        TreeNode* now = q.front();
        if (elements[i].has_value()) {
            now->left = new TreeNode(elements[i].value());
            q.push(now->left);
        } else {
            now->left = nullptr;
        }
        i++;
        if (i >= size) break;

        if (elements[i].has_value()) {
            now->right = new TreeNode(elements[i].value());
            q.push(now->right);
        } else {
            now->right = nullptr;
        }
        q.pop();
        i++;
    }

    return node;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode* root, std::vector<string>& vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val));

        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode* root, std::vector<int>& vec) {
    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
        TreeNode* tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

#include <gtest/gtest.h>

#include <iostream>

TEST(memleak, t0) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto* binary_tree = ConstructBinaryTree(elements);
    FreeTreeNode(binary_tree);
}

TEST(t0, t1) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto* binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 3);
    FreeTreeNode(binary_tree);
}

TEST(t0, t2) {
    vector<optional<int>> elements{1, optional<int>(), 2};
    auto* binary_tree = ConstructBinaryTree(elements);
    Solution sl;
    int ret = sl.MaxDepth(binary_tree);
    EXPECT_EQ(ret, 2);
    FreeTreeNode(binary_tree);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
