// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, return the sum of values of its deepest
 * leaves.*/

#include <algorithm>
#include <queue>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;

//* Definition for a binary tree node.
struct TreeNode : public Tree::TreeNode<int> {
    bool m_deleted = false;
    TreeNode() : Tree::TreeNode<int>() {}
    TreeNode(int x) : Tree::TreeNode<int>(x) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : Tree::TreeNode<int>(x, left, right) {}
};

namespace {
class Solution {
   public:
    int Height(Tree::TreeNode<int>* root) {
        if (!root) return 0;
        return std::max(Height(root->left), Height(root->right)) + 1;
    }
    int m_sum = 0;
    int SumAtK(Tree::TreeNode<int>* root, int k) {
        if (!root) return m_sum;
        if (k == 0 && root->val != -1) m_sum = m_sum + root->val;
        SumAtK(root->left, k - 1);
        SumAtK(root->right, k - 1);
        return m_sum;
    }

    int DeepestLeavesSum(TreeNode* root) {
        const int h = Height(root);
        const int sum = SumAtK(root, h - 1);
        return sum;
    }
};

class SolutionV2 {
   public:
    int DeepestLeavesSum(TreeNode* root) {
        if (!root) return 0;
        queue<Tree::TreeNode<int>*> q;
        q.push(root);
        q.push(nullptr);
        int sum = 0;
        while (q.size() > 1) {
            auto* curr = q.front();
            q.pop();
            if (!curr) {
                q.push(nullptr);
                sum = 0;
                continue;
            }
            sum += curr->val;
            if (curr->left) q.push(curr->left);
            if (curr->right) q.push(curr->right);
        }
        return sum;
    }
};

#define null -1

TreeNode* NewNode(int data) {
    auto* node = new TreeNode;
    node->val = data;
    node->left = node->right = nullptr;
    return node;
}

// Function to insert nodes in level order
TreeNode* InsertLevelOrder(vector<int>& arr, int i) {
    // Base case for recursion
    const int n = arr.size();
    if (i < n) {
        TreeNode* temp = NewNode(arr[i]);
        TreeNode* root = temp;

        // insert left child
        root->left = InsertLevelOrder(arr, 2 * i + 1);

        // insert right child
        root->right = InsertLevelOrder(arr, 2 * i + 2);

        if (arr[i] == -1) {
            root->m_deleted = true;
        }
        return root;
    }
    return nullptr;
}

// Function to print tree nodes in
// InOrder fashion
void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(dynamic_cast<TreeNode*>(root->left));
    FreeTreeNode(dynamic_cast<TreeNode*>(root->right));

    delete root;
}

TreeNode* ConstructTreeNode(std::vector<int>& arr) {
    return InsertLevelOrder(arr, 0);
}

TEST(deepest_leaves_sum, t1) {
    vector<int> vec = {1, 2, 3, 4, 5, null, 6, 7, null, null, null, null, 8};

    TreeNode* root = ConstructTreeNode(vec);
    const int expected = 15;

    Solution sl;
    const int ret = sl.DeepestLeavesSum(root);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root);
};

TEST(deepest_leaves_sum, t2) {
    vector<int> vec = {6, 7, 8, 2, 7, 1, 3, 9, null, 1, 4, null, null, null, 5};

    TreeNode* root = ConstructTreeNode(vec);
    const int expected = 19;

    Solution sl;
    const int ret = sl.DeepestLeavesSum(root);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root);
}
}  // namespace
