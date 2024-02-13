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

#include "datastruct_base.hh"
using namespace std;

using namespace Tree;
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

#include <gtest/gtest.h>
#define null optional<int>()
using namespace std;

TEST(t0, t1) {
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

TEST(t0, t2) {
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

TEST(t0, t3) {
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
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
