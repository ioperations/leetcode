// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**Given the root of a binary tree, return the zigzag level order traversal of
 * its nodes' values. (i.e., from left to right, then right to left for the next
 * level and alternate between).*/

//* Definition for a binary tree node.
#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <vector>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    vector<vector<int>> ZigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> ret;
        if (root == nullptr) return ret;

        AddToRet(root, ret, 0);
        for (int i = 1; i < (int)ret.size(); i += 2) {
            reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }

    void AddToRet(TreeNode *root, vector<vector<int>> &ret, int n = 0) {
        if (root) {
            if ((int)ret.size() <= n) ret.resize(n + 1);
            ret[n].push_back(root->val);

            AddToRet(root->left, ret, n + 1);
            AddToRet(root->right, ret, n + 1);
        }
    }
};

TEST(memleak, trandom) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = Tree::ConstructBinaryTree(elements);
    Tree::FreeTreeNode(binary_tree);
}

TEST(binary_tree_zigzag_level_order_traversal, t1) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{{3}, {20, 9}, {15, 7}};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}

TEST(binary_tree_zigzag_level_order_traversal, t2) {
    vector<optional<int>> elements{1};
    auto *binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{{1}};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}

TEST(binary_tree_zigzag_level_order_traversal, t3) {
    vector<optional<int>> elements{};
    auto *binary_tree = Tree::ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{};
    EXPECT_EQ(ret, output);
    Tree::FreeTreeNode(binary_tree);
}
}  // namespace
