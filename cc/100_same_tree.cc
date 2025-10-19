// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the roots of two binary trees p and q, write a function to check if they
are the same or not.

Two binary trees are considered the same if they are structurally identical, and
the nodes have the same value.
*/

#include <queue>
#include <tuple>
#include <vector>

// * Definition for a binary tree node.
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;
namespace {
class Solution {
   public:
    template <typename T>
    bool IsSameTree(TreeNode<T>* p, TreeNode<T>* q) {
        // pass
        return SameTreeByLevel(p, q);
    }

    template <typename T>
    bool SameTreeByLevel(TreeNode<T>* p, TreeNode<T>* q) {
        std::queue<std::tuple<TreeNode<T>*, TreeNode<T>*>> queue;

        queue.emplace(p, q);

        while (!queue.empty()) {
            auto [p, q] = queue.front();
            queue.pop();

            if (p == nullptr && q == nullptr) {
                continue;
            }
            if (p == nullptr && q != nullptr) {
                return false;
            }
            if (p != nullptr && q == nullptr) {
                return false;
            }

            if (p->val != q->val) {
                return false;
            }
            queue.emplace(p->left, q->left);
            queue.emplace(p->right, q->right);
        }
        return true;
    }
};

TEST(memleak, t0) {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    auto* root = ConstructTree(p);

    auto* root2 = ConstructTree(q);
    FreeTreeNode(root);
    FreeTreeNode(root2);
}

TEST(same_tree, t1) {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    auto* root1 = ConstructTree(p);
    auto* root2 = ConstructTree(q);
    bool const expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root1);
    FreeTreeNode(root2);
}

TEST(same_tree, t2) {
    std::vector<int> p = {1, 2}, q = {1, 2};
    auto* root1 = ConstructTree(p);
    auto* root2 = ConstructTree(q);
    bool const expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root1);
    FreeTreeNode(root2);
}

TEST(same_tree, t3) {
    std::vector<int> p = {1, 2, 1}, q = {1, 1, 2};

    auto* root1 = ConstructTree(p);
    auto* root2 = ConstructTree(q);
    bool const expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root1);
    FreeTreeNode(root2);
}

TEST(same_tree, t4) {
    std::vector<int> p = {1, 2, 1}, q = {};

    auto* root1 = ConstructTree(p);
    auto* root2 = ConstructTree(q);
    bool const expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root1);
    FreeTreeNode(root2);
}

TEST(same_tree, t5) {
    std::vector<int> p = {}, q = {1, 2, 1};

    auto* root1 = ConstructTree(p);
    auto* root2 = ConstructTree(q);
    bool const expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    EXPECT_EQ(ret, expected);

    FreeTreeNode(root1);
    FreeTreeNode(root2);
}

}  // namespace
