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

class Solution {
   public:
    template <typename T>
    int GoodNodes(TreeNode<T> *root) {
        int count = 0;
        if (root == nullptr) return 0;

        std::function<void(TreeNode<T> *, int)> fun = [&](TreeNode<T> *n,
                                                          int val) -> void {
            if (n == nullptr) return;
            if (n->val >= val) count++;
            int z = std::max(n->val, val);
            fun(n->left, z);
            fun(n->right, z);
        };
        fun(root, root->val);
        return count;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
using namespace std;
#include <algorithm>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

TEST(t0, t1) {
#define null optional<int>()
    vector<optional<int>> root = {3, 1, 4, 3, null, 1, 5};
    int output = 4;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    /*Nodes in blue are good.
    Root Node (3) is always a good node.
    Node 4 -> (3,4) is the maximum value in the path starting from the root.
    Node 5 -> (3,4,5) is the maximum value in the path
    Node 3 -> (3,1,3) is the maximum value in the path.
    */
    FreeTreeNode(node);
}

TEST(t0, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 3, null, 4, 2};
    int output = 3;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
    FreeTreeNode(node);
}

TEST(t0, t3) {
#define null optional<int>()
    vector<optional<int>> root = {1};
    int output = 1;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}

TEST(t0, t4) {
#define null optional<int>()
    vector<optional<int>> root = {9, null, 3, 6};
    /*
     *
     *        9
     *      /    \
     *   null     3
     *          /
     *         6
     */
    int output = 1;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
