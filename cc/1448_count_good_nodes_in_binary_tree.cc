// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a binary tree root, a node X in the tree is named good if in the path
from root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.
*/
// Definition for a binary tree node.
#include <algorithm>
#include <functional>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    int GoodNodes(TreeNode<T>* root) {
        int count = 0;
        if (root == nullptr) return 0;

        std::function<void(TreeNode<T>*, int)> fun = [&](TreeNode<T>* n,
                                                         int val) -> void {
            if (n == nullptr) return;
            if (n->val >= val) count++;
            int const z = std::max(n->val, val);
            fun(n->left, z);
            fun(n->right, z);
        };
        fun(root, root->val);
        return count;
    }
};

#include <optional>

using namespace std;
#include <vector>

using namespace std;
#define null std::nullopt

TEST(count_good_nodes_in_binary_tree, t1) {
    vector<optional<int>> const root = {3, 1, 4, 3, null, 1, 5};
    int const output = 4;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    /*Nodes in blue are good.
    Root Node (3) is always a good node.
    Node 4 -> (3,4) is the maximum value in the path starting from the root.
    Node 5 -> (3,4,5) is the maximum value in the path
    Node 3 -> (3,1,3) is the maximum value in the path.
    */
    FreeTreeNode(node);
}

TEST(count_good_nodes_in_binary_tree, t2) {
    vector<optional<int>> const root = {3, 3, null, 4, 2};
    int const output = 3;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
    FreeTreeNode(node);
}

TEST(count_good_nodes_in_binary_tree, t3) {
    vector<optional<int>> const root = {1};
    int const output = 1;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}

TEST(count_good_nodes_in_binary_tree, t4) {
    vector<optional<int>> const root = {9, null, 3, 6};
    /*
     *
     *        9
     *      /    \
     *   null     3
     *          /
     *         6
     */
    int const output = 1;
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}

}  // namespace
