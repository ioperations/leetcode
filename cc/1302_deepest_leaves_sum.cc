// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, return the sum of values of its deepest
 * leaves.*/

#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

//* Definition for a binary tree node.
struct TreeNode {
    int m_val;
    TreeNode* m_left;
    TreeNode* m_right;
    bool m_deleted = false;
    TreeNode() : m_val(0), m_left(nullptr), m_right(nullptr) {}
    TreeNode(int x) : m_val(x), m_left(nullptr), m_right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : m_val(x), m_left(left), m_right(right) {}
};

namespace {
class Solution {
   public:
    int Height(TreeNode* root) {
        if (!root) return 0;
        return std::max(Height(root->m_left), Height(root->m_right)) + 1;
    }
    int m_sum = 0;
    int SumAtK(TreeNode* root, int k) {
        if (!root) return m_sum;
        if (k == 0 && root->m_val != -1) m_sum = m_sum + root->m_val;
        SumAtK(root->m_left, k - 1);
        SumAtK(root->m_right, k - 1);
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
        queue<TreeNode*> q;
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
            sum += curr->m_val;
            if (curr->m_left) q.push(curr->m_left);
            if (curr->m_right) q.push(curr->m_right);
        }
        return sum;
    }
};

#define null -1

TreeNode* NewNode(int data) {
    auto* node = new TreeNode;
    node->m_val = data;
    node->m_left = node->m_right = nullptr;
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
        root->m_left = InsertLevelOrder(arr, 2 * i + 1);

        // insert right child
        root->m_right = InsertLevelOrder(arr, 2 * i + 2);

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

    FreeTreeNode(root->m_left);
    FreeTreeNode(root->m_right);

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
