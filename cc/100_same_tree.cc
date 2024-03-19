// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the roots of two binary trees p and q, write a function to check if they
are the same or not.

Two binary trees are considered the same if they are structurally identical, and
the nodes have the same value.
*/

#include <catch2/catch_test_macros.hpp>
#include <vector>

#include "datastruct_base.hh"

using namespace Tree;
namespace {
class Solution {
   public:
    template <typename T>
    bool IsSameTree(TreeNode<T> *p, TreeNode<T> *q) {
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

TEST_CASE("memleak", "t0") {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    auto *root = ConstructTree(p);

    auto *root2 = ConstructTree(q);
    FreeRoot(root);
    FreeRoot(root2);
}

TEST_CASE("same_tree_t1", "t1") {
    std::vector<int> p = {1, 2, 3}, q = {1, 2, 3};

    auto *root1 = ConstructTree(p);
    auto *root2 = ConstructTree(q);
    bool expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    REQUIRE(ret == expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST_CASE("same_tree_t2", "t2") {
    std::vector<int> p = {1, 2}, q = {1, 2};
    auto *root1 = ConstructTree(p);
    auto *root2 = ConstructTree(q);
    bool expected = true;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    REQUIRE(ret == expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST_CASE("same_tree_t3", "t3") {
    std::vector<int> p = {1, 2, 1}, q = {1, 1, 2};

    auto *root1 = ConstructTree(p);
    auto *root2 = ConstructTree(q);
    bool expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    REQUIRE(ret == expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST_CASE("same_tree_t4", "t4") {
    std::vector<int> p = {1, 2, 1}, q = {};

    auto *root1 = ConstructTree(p);
    auto *root2 = ConstructTree(q);
    bool expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    REQUIRE(ret == expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

TEST_CASE("same_tree_t5", "t5") {
    std::vector<int> p = {}, q = {1, 2, 1};

    auto *root1 = ConstructTree(p);
    auto *root2 = ConstructTree(q);
    bool expected = false;

    Solution s;
    auto ret = s.IsSameTree(root1, root2);
    REQUIRE(ret == expected);

    FreeRoot(root1);
    FreeRoot(root2);
}

}  // namespace
