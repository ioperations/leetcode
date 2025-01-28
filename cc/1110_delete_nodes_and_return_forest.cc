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

#include <array>
#include <optional>
#include <unordered_set>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

/// Definition for a binary tree node.
using TreeNode = Tree::TreeNode<int>;
using namespace std;

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
            if (root->left) {
                ans.push_back(root->left);
            }
            if (root->right) {
                ans.push_back(root->right);
            }
            return nullptr;
        }
        return root;
    }
    vector<TreeNode *> DelNodes(TreeNode *root, const vector<int> &targets) {
        for (const int &target : targets) us.insert(target);
        if (us.find(root->val) == us.end()) ans.push_back(root);
        Solve(root);
        return ans;
    }
};

template <typename T>
void InOrderTranverse(TreeNode *root, std::vector<T> &vec) {
    if (root == nullptr) {
        return;
    }

    InOrderTranverse(root->left, vec);
    vec.push_back(root);
    InOrderTranverse(root->right, vec);
}

void InOrderTranverse(TreeNode *root, std::vector<int> &vec) {
    if (root == nullptr) {
        return;
    }

    InOrderTranverse(root->left, vec);
    vec.push_back(root->val);
    InOrderTranverse(root->right, vec);
}

TEST(t, t1) {
    std::vector<std::optional<int>> data{1, 2, 3, 4, 5, 6, 7};
    auto *binaryTree = Tree::ConstructBinaryTree(data);
    vector<TreeNode *> toFree;
    InOrderTranverse(binaryTree, toFree);
    ScopeGuard freeMem([&toFree]() {
        for (auto &node : toFree) {
            delete node;
        }
    });

    TreeNode n(1);
    TreeNode n_number_one(2);
    TreeNode n2(4);
    n.left = &n_number_one;
    n_number_one.left = &n2;
    TreeNode l1(6);
    TreeNode l2(7);
    std::array<TreeNode *, 3> expected = {&n, &l1, &l2};
    Solution sl;
    auto ret = sl.DelNodes(binaryTree, {3, 5});

    int i = 0;
    for (auto &node : expected) {
        std::vector<int> ret_p;
        InOrderTranverse(ret[i], ret_p);
        std::vector<int> ptr_p;
        InOrderTranverse(node, ptr_p);
        EXPECT_EQ(ret_p, ptr_p);
        i++;
    }
}

}  // namespace
