// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <optional>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    int MinCameraCover(TreeNode<T> *root) {
        int sum = 0;
        // if root is not monitored, we place an additional camera here
        if (Dfs(root, sum) == 0) sum++;
        return sum;
    }

    template <typename T>
    int Dfs(TreeNode<T> *root, int &sum) {
        if (!root) return 1;
        int l = Dfs(root->left, sum);
        int r = Dfs(root->right, sum);
        // if at least 1 child is not monitored, we need to place a camera at
        // current node
        if (l == 0 || r == 0) {
            sum++;
            return 2;
        }  // if at least 1 child has camera, the current node is monitored.
           // Thus, we don't need to place a camera here
        if (l == 2 || r == 2) {
            return 1;
        }  // if both children are monitored but have no camera, we don't need
           // to place a camera here. We place the camera at its parent node at
           // the higher level.
        return 0;
    }
};

using namespace std;
#define null optional<int>()

using namespace std;

TEST(t0, t1) {
    std::vector<optional<int>> v{0, 0, null, 0, 0};
    int out = 1;
    auto *n = ConstructBinaryTree(v);
    Solution sl;
    int ret = sl.MinCameraCover(n);
    EXPECT_EQ(ret, out);
    // One camera is enough to monitor all nodes if placed as shown.
    FreeTreeNode(n);
}

TEST(t0, t2) {
    std::vector<optional<int>> v{0, 0, null, 0, null, 0, null, null, 0};
    int out = 2;
    auto *n = ConstructBinaryTree(v);
    Solution sl;
    int ret = sl.MinCameraCover(n);
    EXPECT_EQ(ret, out);
    // At least two cameras are needed to monitor all nodes of the tree. The
    // above image shows one of the valid configurations of camera placement.
    FreeTreeNode(n);
}

}  // namespace
