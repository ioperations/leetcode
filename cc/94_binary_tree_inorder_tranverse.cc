// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//**
// Definition for a binary tree node.
// 中序遍历

#include <vector>

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
class Solution {
   public:
    template <typename T>
    std::vector<T> InorderTraversal(TreeNode<T> *root) {
        std::vector<T> ret;
        InorderTraversal1(root, ret);
        return ret;
    }

    template <typename T>
    void InorderTraversal1(TreeNode<T> *root, std::vector<T> &ret) {
        if (!root) {
            return;
        }
        InorderTraversal1(root->left, ret);
        ret.push_back(root->val);
        InorderTraversal1(root->right, ret);
    }
};

#include <optional>

using namespace std;

TEST(binary_tree_inorder_tranverse_v2, t0) {
#define null optional<int>()
    std::vector<optional<int>> vec = {1, null, 2, 3};
    // Output: [1,3,2]

    TreeNode<int> *root = ConstructBinaryTree(vec);
    PrintBt(root);

    Solution s;
    auto ret = s.InorderTraversal(root);
    EXPECT_EQ(ret, (std::vector<int>{1, 3, 2}));

    FreeTreeNode(root);
}

}  // namespace
