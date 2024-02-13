// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.
#include <vector>

#include "datastruct_base.hh"
using namespace Tree;

class Solution {
   public:
    template <typename T>
    std::vector<int> PostorderTraversal(TreeNode<T> *root) {
        std::vector<int> ret;
        Tranverse(root, ret);
        return ret;
    }

    template <typename T>
    void Tranverse(TreeNode<T> *root, std::vector<int> &val) {
        if (root == nullptr) {
            return;
        }

        Tranverse(root->left, val);

        Tranverse(root->right, val);
        val.push_back(root->val);
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{1, 2, 3});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, (std::vector<int>{3, 2, 1}));

    FreeRoot(root);
}
TEST(t0, t2) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{});

    FreeRoot(root);
}
TEST(t0, t3) {
    TreeNode<int> *root = ConstructTree(std::vector<int>{1});
    Solution s;
    std::vector<int> ret = s.PostorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{1});
    FreeRoot(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
