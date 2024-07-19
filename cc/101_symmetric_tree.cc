// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e.,
symmetric around its center).
*/

#include <functional>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using TreeNode = Tree::TreeNode<int>;

namespace {
class Solution {
   public:
    bool IsSymmetric(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        std::vector<int> p;
        std::vector<int> q;

        Inorder<true>(root->left,
                      [&p](const TreeNode *n) { p.push_back(n->val); });
        Inorder<false>(root->right,
                       [&q](const TreeNode *n) { q.push_back(n->val); });

        if (p.size() != q.size()) {
            return false;
        }

        for (int i = 0; i < (int)p.size(); i++) {
            if (p[i] != q[i]) {
                return false;
            }
        }

        return true;
    }

    template <bool from_left_to_right>
    void Inorder(TreeNode *root, std::function<void(const TreeNode *)> fun) {
        if (root == nullptr) {
            return;
        }

        if constexpr (from_left_to_right) {
            Inorder<from_left_to_right>(root->left, fun);
            fun(root);
            Inorder<from_left_to_right>(root->right, fun);
        } else {
            Inorder<from_left_to_right>(root->right, fun);
            fun(root);
            Inorder<from_left_to_right>(root->left, fun);
        }
    }
};

TEST(symmetric_tree, t1) {
    /*
                          ___
                         | 1 |
                         |___|
                    ___    |    ___
                   | 2 |   |   | 2 |
                   |___|   |   |___|
                           |
              ___     ___  |  ___     ___
             | 3 |   | 4 | | | 4 |   | 3 |
             |___|   |___| | |___|   |___|
    */

    TreeNode n(1);
    TreeNode n1(2);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n4(4);
    TreeNode n5(3);
    TreeNode n6(4);

    n.left = &n1;
    n.right = &n2;
    n1.left = &n3;
    n1.right = &n4;
    n2.left = &n6;
    n2.right = &n5;

    Solution sl;
    bool ret = sl.IsSymmetric(&n);
    EXPECT_EQ(ret, true);
}

TEST(symmetric_tree, t2) {
    /*
                          ___
                         | 1 |
                         |___|
                  ___              ___
                 | 2 |            | 2 |
                 |___|            |___|
              ___     ___     ___      ___
             |   |   | 3 |   |   |    | 3 |
             |___|   |___|   |___|    |___|
    */

    TreeNode n(1);
    TreeNode n1(2);
    TreeNode n2(2);
    TreeNode n3(3);
    TreeNode n5(3);

    n.left = &n1;
    n.right = &n2;
    n1.right = &n3;

    n2.right = &n5;

    Solution sl;
    bool ret = sl.IsSymmetric(&n);
    EXPECT_EQ(ret, false);
}

}  // namespace
