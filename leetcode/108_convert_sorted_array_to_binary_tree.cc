/*
Given an integer array nums where the elements are sorted in ascending order,
convert it to a height-balanced binary search tree.

A height-balanced binary tree is a binary tree in which the depth of the two
subtrees of every node never differs by more than one.
*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
#include <vector>
using namespace std;

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

#include <gtest/gtest.h>

#include <iostream>
/// 将二分树销毁掉
void FreeTreeNode(TreeNode *root) {
    if (root) {
        FreeTreeNode(root->left);
        FreeTreeNode(root->right);
        delete root;
    }
}

void InorderLeft(TreeNode *root, std::vector<int> &vec) {
    if (root == nullptr) {
        return;
    }

    InorderLeft(root->left, vec);
    vec.push_back(root->val);
    InorderLeft(root->right, vec);
}

TEST(t0, t1) {
    std::set<std::vector<int>> expected{{-10, -3, 0, 5, 9}, {0, -10, 5, -3, 9}};
    // Explanation: [0,-10,5,null,-3,null,9] is also accepted:

    Solution sl;
    std::vector<int> v{-10, -3, 0, 5, 9};
    TreeNode *root = sl.SortedArrayToBst(v);

    std::vector<int> visit;

    InorderLeft(root, visit);
    EXPECT_TRUE(expected.count(visit) != 0);

    FreeTreeNode(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
