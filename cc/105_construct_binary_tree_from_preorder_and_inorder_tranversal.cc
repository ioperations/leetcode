// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.*/

//* Definition for a binary tree node.
#include <unordered_map>
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

using namespace Tree;
using namespace std;
namespace {
class Solution {
   public:
    template <typename T>
    TreeNode<T> *Build(vector<T> &preorder, int p_start, int p_end,
                       unordered_map<int, int> &inorder_map, int i_start,
                       int i_end) {
        if (p_start > p_end || i_start > i_end) return nullptr;

        auto *root = new TreeNode(preorder[p_start]);
        int i_root = inorder_map[root->val];
        int nums_left = i_root - i_start;

        root->left = Build(preorder, p_start + 1, p_start + nums_left,
                           inorder_map, i_start, i_root - 1);
        root->right = Build(preorder, p_start + 1 + nums_left, p_end,
                            inorder_map, i_root + 1, i_end);

        return root;
    }
    template <typename T>
    TreeNode<T> *BuildTree(vector<T> &preorder, vector<T> &inorder) {
        unordered_map<int, int> inorder_map;
        for (int i = 0; i < (int)inorder.size(); i++)
            inorder_map[inorder[i]] = i;

        return Build(preorder, 0, preorder.size() - 1, inorder_map, 0,
                     inorder.size() - 1);
    }
};

using namespace std;

TEST(construct_binary_tree_from_preorder_and_inorder_tranversal, t1) {
    vector<int> preorder = {3, 9, 20, 15, 7}, inorder = {9, 3, 15, 20, 7};
    Solution sl;
    auto *node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {3, 9, 20, 15, 7};
    EXPECT_EQ(ret, output);
}

TEST(construct_binary_tree_from_preorder_and_inorder_tranversal, t2) {
    vector<int> preorder = {-1}, inorder = {-1};
    Solution sl;
    auto *node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {-1};
    EXPECT_EQ(ret, output);
}

}  // namespace
