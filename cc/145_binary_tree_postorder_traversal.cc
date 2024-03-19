// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
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

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    std::vector<int> PostorderTraversal(TreeNode<T> *root) {
        std::vector<int> ret;
        Tranverse(root, ret);
        return ret;
    }

    template <typename T>
    void Tranverse(TreeNode<T> *root, std::vector<int> &val) {
        if (root == nullptr) {
            return;
        }

        Tranverse(root->left, val);

        Tranverse(root->right, val);
        val.push_back(root->val);
    }
};

TEST(binary_tree_postorder_traversal, t1) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{1, 2, 3});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, (std::vector<int>{3, 2, 1}));

    FreeRoot(root);
}
TEST(binary_tree_postorder_traversal, t2) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{});

    FreeRoot(root);
}
TEST(binary_tree_postorder_traversal, t3) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{1});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{1});
    FreeRoot(root);
}

}  // namespace
