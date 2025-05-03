// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given the root of a binary search tree (BST) with duplicates, return all the
mode(s) (i.e., the most frequently occurred element) in it.

If the tree has more than one mode, return them in any order.

Assume a BST is defined as follows:

The left subtree of a node contains only nodes with keys less than or equal to
the node's key. The right subtree of a node contains only nodes with keys
greater than or equal to the node's key. Both the left and right subtrees must
also be binary search trees.
*/

#include <limits>
#include <map>
#include <stack>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using TreeNode = Tree::TreeNode<int>;
using namespace std;

namespace {
class Solution {
   public:
    vector<int> FindMode(TreeNode* root) {
        vector<int> sol;
        if (!root) return sol;

        map<int, int> freq;
        int maxfreq = std::numeric_limits<int>::min();

        stack<TreeNode*> myst;
        myst.push(root);
        while (myst.size()) {
            TreeNode* curr = myst.top();
            myst.pop();

            freq[curr->val]++;
            maxfreq = (freq[curr->val] > maxfreq) ? freq[curr->val] : maxfreq;

            if (curr->left) myst.push(curr->left);
            if (curr->right) myst.push(curr->right);
        }

        for (auto each : freq)
            if (each.second == maxfreq) sol.push_back(each.first);

        return sol;
    }

    void InorderLeft(TreeNode* root, std::map<int, int>& count) {
        if (root == nullptr) {
            return;
        }

        InorderLeft(root->left, count);
        count[root->val]++;
        InorderLeft(root->right, count);
    }
};

TEST(find_mode_in_binary_search_tree, t1) {
    std::vector<int> root = {1, 2, 2};
    std::vector<int> output{2};

    TreeNode* node = Tree::ConstructTree(root);

    Solution sl;
    auto ret = sl.FindMode(node);

    EXPECT_EQ(ret, output);

    Tree::FreeTreeNode(node);
}

TEST(find_mode_in_binary_search_tree, t2) {
    std::vector<int> root = {1};
    std::vector<int> output{1};

    TreeNode* node = Tree::ConstructTree(root);

    Solution sl;
    auto ret = sl.FindMode(node);

    EXPECT_EQ(ret, output);

    Tree::FreeTreeNode(node);
}
}  // namespace
