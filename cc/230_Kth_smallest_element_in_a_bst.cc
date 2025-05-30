// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <functional>
#include <queue>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    int KthSmallest(TreeNode* root, int k) {
        // pass

        std::priority_queue<int, std::vector<int>, std::greater<>> q;

        Inorder(root, q);

        for (int i = 1; q.size() && i < k; i++) {
            q.pop();
        }

        return q.top();
    }

    void Inorder(
        TreeNode* root,
        std::priority_queue<int, std::vector<int>, std::greater<>>& q) {
        if (root == nullptr) {
            return;
        }

        q.push(root->val);
        Inorder(root->left, q);
        Inorder(root->right, q);
    }
};

TEST(Kth_smallest_element_in_a_bst, t1) {
    std::vector<int> const root = {3, 1, 4, 2};
    int const k = 1;

    TreeNode* head = Tree::ConstructTree(root);
    Solution s;
    int const ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 1);
    Tree::FreeTreeNode(head);
}

TEST(Kth_smallest_element_in_a_bst, t2) {
    std::vector<int> const root = {5, 3, 6, 2, 4, 1};
    int const k = 3;

    TreeNode* head = Tree::ConstructTree(root);
    Solution s;
    int const ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 3);
    Tree::FreeTreeNode(head);
}

}  // namespace
