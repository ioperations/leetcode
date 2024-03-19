// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <functional>
#include <queue>
#include <vector>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using TreeNode = Tree::TreeNode<int>;

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

TEST(Kth_smallest_element_in_a_bst, t1) {
    std::vector<int> root = {3, 1, 4, 2};
    int k = 1;

    TreeNode *head = Tree::ConstructTree(root);
    Solution s;
    int ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 1);
    Tree::FreeRoot(head);
}

TEST(Kth_smallest_element_in_a_bst, t2) {
    std::vector<int> root = {5, 3, 6, 2, 4, 1};
    int k = 3;

    TreeNode *head = Tree::ConstructTree(root);
    Solution s;
    int ret = s.KthSmallest(head, k);
    EXPECT_EQ(ret, 3);
    Tree::FreeRoot(head);
}

}  // namespace
