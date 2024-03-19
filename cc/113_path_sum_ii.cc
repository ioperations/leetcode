// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree and an integer targetSum, return all
root-to-leaf paths where the sum of the node values in the path equals
targetSum. Each path should be returned as a list of the node values, not node
references.

A root-to-leaf path is a path starting from the root and ending at any leaf
node. A leaf is a node with no children.

 */

// Definition for a binary tree node.

#include <numeric>
#include <optional>
#include <vector>

#include "datastruct_base.hh"
#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

using namespace Tree;
namespace {
class Solution {
    std::vector<vector<int>> m_ret;
    template <typename T>
    void Inorder(TreeNode<T> *root, std::vector<int> &path, int target_sum) {
        if (root == nullptr) return;
        path.push_back(root->val);
        if (root->left) {
            Inorder(root->left, path, target_sum);
        }
        if (root->right) {
            Inorder(root->right, path, target_sum);
        }

        if (!root->left && !root->right) {
            int const sum = accumulate(path.begin(), path.end(), 0);
            if (sum == target_sum) {
                m_ret.push_back(path);
            }
        }

        path.pop_back();
    }

   public:
    template <typename T>
    vector<vector<int>> PathSum(TreeNode<T> *root, int target_sum) {
        std::vector<int> path;

        Inorder(root, path, target_sum);

        return m_ret;
    }
};

#define null optional<int>()

TEST(path_sum_ii, t1) {
    vector<optional<int>> root = {5, 4, 8,    11,   null, 13, 4,
                                  7, 2, null, null, 5,    1};
    int const target_sum = 22;
    vector<vector<int>> const output = {{5, 4, 11, 2}, {5, 8, 4, 5}};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);

    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(path_sum_ii, t2) {
    vector<optional<int>> root = {1, 2, 3};
    int const target_sum = 5;
    vector<vector<int>> const output = {};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);

    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(path_sum_ii, t3) {
    vector<optional<int>> root = {1, 2};
    int const target_sum = 0;
    vector<vector<int>> const output = {};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}
}  // namespace
