// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
//* Definition for a binary tree node.

#include <vector>
#include <string>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    template <typename T>
    std::vector<T> PreorderTraversal(TreeNode<T> *root) {
        std::vector<T> ret;
        Tranverse(root, ret);
        return ret;
    }

    template <typename T>
    void Tranverse(TreeNode<T> *root, std::vector<T> &val) {
        if (root == nullptr) {
            return;
        }

        val.push_back(root->val);
        Tranverse(root->left, val);

        Tranverse(root->right, val);
    }
};

#include <optional>

using namespace std;


TEST(t0, t1) {
    std::vector<optional<int>> vec{1, 2, 3};
    TreeNode<int> *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, (std::vector<int>{1, 2, 3}));

    FreeTreeNode(root);
}

TEST(t0, t2) {
    std::vector<optional<int>> vec{};
    TreeNode<int> *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{});

    FreeTreeNode(root);
}

TEST(t0, t3) {
    std::vector<optional<int>> vec{1};
    TreeNode<int> *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{1});
    FreeTreeNode(root);
}

}
