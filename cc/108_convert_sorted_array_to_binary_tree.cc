// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums where the elements are sorted in ascending order,
convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree in which the depth of the two
subtrees of every node never differs by more than one.
*/

#include <catch2/catch_test_macros.hpp>
#include <set>
#include <vector>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using TreeNode = Tree::TreeNode<int>;
using namespace std;

namespace {
class Solution {
   public:
    TreeNode *SortedArrayToBst(std::vector<int> &nums) {
        return Helper(nums, 0, nums.size() - 1);
    }

    TreeNode *Helper(vector<int> &nums, int start, int end) {
        if (start > end) return nullptr;
        int mid = start + (end - start) / 2;
        TreeNode *bs_ttree = new TreeNode(nums[mid]);
        bs_ttree->left = Helper(nums, start, mid - 1);
        bs_ttree->right = Helper(nums, mid + 1, end);
        return bs_ttree;
    }
};

void InorderLeft(TreeNode *root, std::vector<int> &vec) {
    if (root == nullptr) {
        return;
    }

    InorderLeft(root->left, vec);
    vec.push_back(root->val);
    InorderLeft(root->right, vec);
}

TEST(convert_sorted_array_to_binary_tree, t1) {
    std::set<std::vector<int>> expected{{-10, -3, 0, 5, 9}, {0, -10, 5, -3, 9}};
    // Explanation: [0,-10,5,null,-3,null,9] is also accepted:

    Solution sl;
    std::vector<int> v{-10, -3, 0, 5, 9};
    TreeNode *root = sl.SortedArrayToBst(v);

    std::vector<int> visit;

    InorderLeft(root, visit);
    REQUIRE(expected.count(visit) != 0);

    Tree::FreeTreeNode(root);
}

}  // namespace
