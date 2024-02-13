// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, return the same tree where every subtree (of
the given tree) not containing a 1 has been removed.

A subtree of a node node is node plus every node that is a descendant of node.*/

//* Definition for a binary tree node.
#include "datastruct_base.hh"
using namespace Tree;

class Solution {
   public:
    template <typename T>
    TreeNode<T> *PruneTree(TreeNode<T> *&root) {
        if (root == nullptr) return root;
        PruneTree(root->left);
        PruneTree(root->right);
        if (root->left == nullptr && root->right == nullptr && !root->val) {
            delete root;
            root = nullptr;
            return nullptr;
        }
        return root;
    }
};

#include <gtest/gtest.h>
using namespace std;
#define null optional<int>()

TEST(t0, t1) {
    vector<optional<int>> root = {1, null, 0, 0, 1};
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    auto *ret = sl.PruneTree(node);
    vector<optional<int>> output{1, null, 0, null, 1};

    vector<optional<int>> ret_node;
    BfsSearchV1(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1, 0, 1, 0, 0, 0, 1};
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    auto *ret = sl.PruneTree(node);
    vector<optional<int>> output{1, null, 1, null, 1};

    vector<optional<int>> ret_node;
    BfsSearchV1(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}
TEST(t0, t3) {
    vector<optional<int>> root = {1, 1, 0, 1, 1, 0, 1, 0};
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    auto *ret = sl.PruneTree(node);
    vector<optional<int>> output{1, 1, 0, 1, 1, null, 1};

    vector<optional<int>> ret_node;
    BfsSearchV1(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
