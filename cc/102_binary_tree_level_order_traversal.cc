// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given the root of a binary tree, return the level order traversal of its nodes'
values. (i.e., from left to right, level by level).

*/
// Definition for a binary tree node.
#include <queue>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    vector<vector<T>> LevelOrder(TreeNode<T>* root) {
        vector<vector<T>> ret;
        struct Status {
            TreeNode<T>* m_t;
            int m_level;
        };
        if (root == nullptr) return ret;

        queue<Status> q;

        Status tmp{};
        tmp.m_level = 1;
        tmp.m_t = root;

        q.push(tmp);

        vector<T> tmp_vec;

        int now_level = 1;
        while (q.size()) {
            Status const tmp = q.front();
            if (tmp.m_level == now_level) {
                tmp_vec.push_back(tmp.m_t->val);
            } else {
                ret.push_back(tmp_vec);
                tmp_vec.clear();
                now_level++;
                tmp_vec.push_back(tmp.m_t->val);
            }
            if (tmp.m_t->left) {
                q.push({tmp.m_t->left, now_level + 1});
            }
            if (tmp.m_t->right) {
                q.push({tmp.m_t->right, now_level + 1});
            }

            q.pop();
        }
        if (tmp_vec.size()) ret.push_back(tmp_vec);
        return ret;
    }
};

#include <optional>

using namespace std;

#define null \
    optional<int> {}

TEST(binary_tree_level_order_traversal, t1) {
    vector<optional<int>> const root = {3, 9, 20, null, null, 15, 7};
    vector<vector<int>> const output = {{3}, {9, 20}, {15, 7}};
    Solution sl;
    auto* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(binary_tree_level_order_traversal, t2) {
    vector<optional<int>> const root = {1};
    vector<vector<int>> const output = {{1}};
    Solution sl;
    auto* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(binary_tree_level_order_traversal, t3) {
    vector<optional<int>> const root = {};
    vector<vector<int>> const output = {};
    Solution sl;
    auto* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

}  // namespace
