// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, imagine yourself standing on the right side
   of it, return the values of the nodes you can see ordered from top to bottom.

 */

#include <optional>
#include <vector>

// Definition for a binary tree node.
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    vector<int> RightSideView(TreeNode<T>* root) {
        vector<int> ret;
        if (root == nullptr) return ret;
        ret.push_back(root->val);
        int h = 1;
        FindRight(root, ret, h, 1);
        return ret;
    }

    template <typename T>
    void FindRight(TreeNode<T>* root, vector<T>& ret, int& max_height,
                   int now_height) {
        // pass
        if (root == nullptr) return;

        if (now_height > max_height) {
            ret.push_back(root->val);
            max_height++;
        }
        FindRight(root->right, ret, max_height, now_height + 1);
        FindRight(root->left, ret, max_height, now_height + 1);
    }
};

TEST(binary_tree_right_side_view, t1) {
    vector<optional<int>> const root = {
        1, 2, 3, std::optional<int>(), 5, std::optional<int>(), 4};
    TreeNode<int>* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> const output = {1, 3, 4};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

TEST(binary_tree_right_side_view, t2) {
    vector<optional<int>> const root = {1, std::optional<int>(), 3};
    TreeNode<int>* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> const output = {1, 3};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

TEST(binary_tree_right_side_view, t3) {
    vector<optional<int>> const root = {};
    TreeNode<int>* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> const output = {};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

}  // namespace
