// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given the root of a binary search tree (BST), where the values of
exactly two nodes of the tree were swapped by mistake. Recover the tree without
changing its structure.
*/

#include <utility>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace Tree;

namespace {

template <typename T>
class Solution {
   public:
    TreeNode<T> *prev = nullptr;
    TreeNode<T> *first = nullptr;
    TreeNode<T> *second = nullptr;
    void RecoverTree(TreeNode<T> *root) {
        Inorder(root);
        std::swap(first->val, second->val);
    }

    void Inorder(TreeNode<T> *root) {
        if (root == nullptr) return;

        Inorder(root->left);

        if (prev != nullptr && root->val < prev->val) {
            if (first == nullptr) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        Inorder(root->right);
    }
};

#include <optional>
#include <vector>

using namespace std;

TEST(recover_binary_search_tree, t1) {
#define null optional<int>()
    vector<optional<int>> root = {1, 3, null, null, 2};
    vector<optional<int>> output = {3, 1, null, null, 2};
    // Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1
    // and 3 makes the BST valid.
    vector<int> in;
    {
        auto *input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        TreeNode<int> *out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

TEST(recover_binary_search_tree, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 1, 4, null, null, 2};
    vector<optional<int>> output = {2, 1, 4, null, null, 3};
    // 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3
    // makes the BST valid.

    vector<int> in;
    {
        auto *input = ConstructBinaryTree(root);
        Solution<int> sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        auto *out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

}  // namespace
