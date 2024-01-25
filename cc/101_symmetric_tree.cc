// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of a binary tree, check whether it is a mirror of itself (i.e.,
symmetric around its center).
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

class Solution {
   public:
    bool IsSymmetric(TreeNode *root) {
        if (root == nullptr) {
            return true;
        }

        std::vector<int> p;
        std::vector<int> q;

        InorderLeft(root->left, p);
        InorderRight(root->right, q);

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

    void InorderLeft(TreeNode *root, std::vector<int> &vec) {
        if (root == nullptr) {
            return;
        }

        InorderLeft(root->left, vec);
        vec.push_back(root->val);
        InorderLeft(root->right, vec);
    }
    void InorderRight(TreeNode *root, std::vector<int> &vec) {
        if (root == nullptr) {
            return;
        }

        InorderRight(root->right, vec);
        vec.push_back(root->val);
        InorderRight(root->left, vec);
    }
};

#include <gtest/gtest.h>

#include <vector>

TEST(t0, t1) {
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

TEST(t0, t2) {
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
