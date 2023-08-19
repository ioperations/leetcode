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
using namespace std;

namespace { 
class Solution {
   public:
    template <typename T>
    vector<vector<T>> LevelOrder(TreeNode<T> *root) {
        vector<vector<T>> ret;
        struct Status {
            TreeNode<T> *t;
            int level;
        };
        if (root == nullptr) return ret;

        queue<Status> q;

        Status tmp;
        tmp.level = 1;
        tmp.t = root;

        q.push(tmp);

        vector<T> tmp_vec;

        int now_level = 1;
        while (q.size()) {
            Status tmp = q.front();
            if (tmp.level == now_level) {
                tmp_vec.push_back(tmp.t->val);
            } else {
                ret.push_back(tmp_vec);
                tmp_vec.clear();
                now_level++;
                tmp_vec.push_back(tmp.t->val);
            }
            if (tmp.t->left) {
                q.push({tmp.t->left, now_level + 1});
            }
            if (tmp.t->right) {
                q.push({tmp.t->right, now_level + 1});
            }

            q.pop();
        }
        if (tmp_vec.size()) ret.push_back(tmp_vec);
        return ret;
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <string>

using namespace std;

#define null \
    optional<int> {}

namespace { 
TEST(t0, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<vector<int>> output = {{3}, {9, 20}, {15, 7}};
    Solution sl;
    auto *tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1};
    vector<vector<int>> output = {{1}};
    Solution sl;
    auto *tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(t0, t3) {
    vector<optional<int>> root = {};
    vector<vector<int>> output = {};
    Solution sl;
    auto *tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

}
