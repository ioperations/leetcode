// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    std::vector<T> PostorderTraversal(TreeNode<T>* root) {
        std::vector<T> ret;
        Tranverse(root, ret);
        return ret;
    }

    template <typename T>
    void Tranverse(TreeNode<T>* root, std::vector<T>& val) {
        if (root == nullptr) {
            return;
        }

        Tranverse(root->left, val);

        Tranverse(root->right, val);
        val.push_back(root->val);
    }
};

TEST(binary_tree_postorder_traversal, t1) {
    TreeNode<int>* root = ConstructTree(std::vector{1, 2, 3});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, (std::vector{3, 2, 1}));

    FreeTreeNode(root);
}
TEST(binary_tree_postorder_traversal, t2) {
    TreeNode<int>* root = ConstructTree(std::vector<int>{});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{});

    FreeTreeNode(root);
}
TEST(binary_tree_postorder_traversal, t3) {
    TreeNode<int>* root = ConstructTree(std::vector{1});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector{1});
    FreeTreeNode(root);
}

}  // namespace
