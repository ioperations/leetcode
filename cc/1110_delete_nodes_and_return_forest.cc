// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a
disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result
in any order.

*/

/// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
#include <array>
#include <unordered_set>
#include <vector>

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    vector<TreeNode *> ans;
    unordered_set<int> us;
    TreeNode *Solve(TreeNode *root) {
        if (!root) return nullptr;
        root->left = Solve(root->left);
        root->right = Solve(root->right);
        if (us.find(root->val) != us.end()) {
            if (root->left) ans.push_back(root->left);
            if (root->right) ans.push_back(root->right);
            return nullptr;
        }
        return root;
    }
    vector<TreeNode *> DelNodes(TreeNode *root, vector<int> &targets) {
        for (int &target : targets) us.insert(target);
        if (us.find(root->val) == us.end()) ans.push_back(root);
        Solve(root);
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

void InOrderTranverse(TreeNode *root, std::vector<int> &vec) {
    if (root == nullptr) {
        return;
    }

    InOrderTranverse(root->left, vec);
    vec.push_back(root->val);
    InOrderTranverse(root->right, vec);
}

TEST(t, t1) {
    TreeNode nl(1);
    TreeNode nl2(2);
    TreeNode nl3(3);
    TreeNode nl4(4);
    TreeNode nl5(5);
    TreeNode nl6(6);
    TreeNode nl7(7);

    nl.left = &nl2;
    nl.right = &nl3;
    nl2.left = &nl4;
    nl2.right = &nl5;
    nl3.left = &nl6;
    nl3.right = &nl7;

    std::vector<int> to_delete = {3, 5};
    TreeNode n(1);
    TreeNode n_number_one(2);
    TreeNode n2(4);
    n.left = &n_number_one;
    n_number_one.left = &n2;
    TreeNode l1(6);
    TreeNode l2(7);
    std::array<TreeNode *, 3> expected = {&n, &l1, &l2};
    Solution sl;
    auto ret = sl.DelNodes(&nl, to_delete);

    int i = 0;
    for (auto &ptr : expected) {
        std::cout << &ptr << std::endl;
        std::vector<int> ret_p;
        InOrderTranverse(ret[i], ret_p);
        std::vector<int> ptr_p;
        InOrderTranverse(ptr, ptr_p);
        EXPECT_EQ(ret_p, ptr_p);
        i++;
    }
}

}
