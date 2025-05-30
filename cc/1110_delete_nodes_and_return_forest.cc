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
#include <functional>
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
   private:
    vector<TreeNode*> m_ans;
    unordered_set<int> m_us;

   public:
    TreeNode* Solve(TreeNode* root) {
        if (!root) return nullptr;
        root->left = Solve(root->left);
        root->right = Solve(root->right);
        if (m_us.find(root->val) != m_us.end()) {
            if (root->left) {
                m_ans.push_back(root->left);
            }
            if (root->right) {
                m_ans.push_back(root->right);
            }
            return nullptr;
        }
        return root;
    }
    vector<TreeNode*> DelNodes(TreeNode* root, const vector<int>& targets) {
        for (const int& target : targets) m_us.insert(target);
        if (m_us.find(root->val) == m_us.end()) m_ans.push_back(root);
        Solve(root);
        return m_ans;
    }
};

void InOrderTraverse(TreeNode* node, function<void(TreeNode*)> func) {
    if (node == nullptr) {
        return;
    }

    InOrderTraverse(node->left, func);
    func(node);
    InOrderTraverse(node->right, func);
}

TEST(t, t1) {
    auto* binary_tree = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{1, 2, 3, 4, 5, 6, 7});
    vector<TreeNode*> to_free;
    InOrderTraverse(binary_tree,
                    [&to_free](TreeNode* node) { to_free.push_back(node); });

    auto* n = Tree::ConstructBinaryTree(
        std::vector<std::optional<int>>{1, 2, std::optional<int>(), 4});
    ScopeGuard const free_mem([&to_free, &n]() {
        for (auto& node : to_free) {
            delete node;
        }
        Tree::FreeTreeNode(n);
    });

    std::array<TreeNode, 3> expected = {*n, TreeNode{6}, TreeNode{7}};
    Solution sl;
    auto ret = sl.DelNodes(binary_tree, {3, 5});

    int i = 0;
    for (auto& node : expected) {
        std::vector<int> ret_p;
        InOrderTraverse(ret[i],
                        [&](TreeNode* root) { ret_p.push_back(root->val); });
        std::vector<int> ptr_p;
        InOrderTraverse(&node,
                        [&](TreeNode* node) { ptr_p.push_back(node->val); });
        EXPECT_EQ(ret_p, ptr_p);
        i++;
    }
}

}  // namespace
