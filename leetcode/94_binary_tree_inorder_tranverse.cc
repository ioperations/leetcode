//**
// Definition for a binary tree node.
// 中序遍历

#include <vector>

#include "datastruct_base.hh"
class Solution {
   public:
    template <typename T>
    std::vector<T> InorderTraversal(TreeNode<T> *root) {
        std::vector<T> ret;
        InorderTraversal1(root, ret);
        return ret;
    }

    template <typename T>
    void InorderTraversal1(TreeNode<T> *root, std::vector<T> &ret) {
        if (!root) {
            return;
        }
        InorderTraversal1(root->left, ret);
        ret.push_back(root->val);
        InorderTraversal1(root->right, ret);
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

TEST(t1, t0) {
#define null optional<int>()
    std::vector<optional<int>> vec = {1, null, 2, 3};
    // Output: [1,3,2]

    TreeNode<int> *root = ConstructBinaryTree(vec);
    PrintBt(root);

    Solution s;
    auto ret = s.InorderTraversal(root);
    EXPECT_EQ(ret, (std::vector<int>{1, 3, 2}));

    FreeTreeNode(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
