// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a Binary Search Tree and a target number k, return true if
 * there exist two elements in the BST such that their sum is equal to the given
 * target.*/

// * Definition for a binary tree node.

#include <optional>
#include <set>
#include <unordered_map>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Solution {
   public:
    std::unordered_map<int, bool> m_m;
    template <typename T>
    bool FindTarget(TreeNode<T>* root, int k) {
        if (root == nullptr) return false;

        if (m_m.find(k - root->val) != m_m.end()) return true;
        m_m[root->val] = 1;

        return FindTarget(root->left, k) || FindTarget(root->right, k);
    }

    template <typename T>
    void Inorder(TreeNode<T>* root, vector<int>& in) {
        if (root == nullptr) {
            return;
        }
        Inorder(root->left, in);
        in.push_back(root->val);
        Inorder(root->right, in);
    }

    template <typename T>
    bool FindTargetV2(TreeNode<T>* root, int k) {
        vector<int> in;
        Inorder(root, in);

        set<int> st;

        for (int const i : in) {
            int const target = k - i;
            if (st.find(target) != st.end()) {
                return true;
            }
            st.insert(i);
        }

        return false;
    }
};

using namespace std;

#define null optional<int>()

TEST(two_sum_iv_input_is_a_bst, t1) {
    vector<optional<int>> const root = {5, 3, 6, 2, 4, null, 7};
    int const k = 9;
    bool const output = true;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    bool const ret = sl.FindTarget(node, k);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(two_sum_iv_input_is_a_bst, t2) {
    vector<optional<int>> const root = {5, 3, 6, 2, 4, null, 7};
    int const k = 28;
    bool const output = false;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    bool const ret = sl.FindTarget(node, k);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

}  // namespace
