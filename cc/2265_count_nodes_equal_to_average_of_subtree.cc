/*
 * Given the root of a binary tree, return the number of nodes where the value
 * of the node is equal to the average of the values in its subtree.
 *
 * Note:
 *
 * The average of n elements is the sum of the n elements divided by n and
 * rounded down to the nearest integer. A subtree of root is a tree consisting
 * of root and all of its descendants.
 * */

#include <gtest/gtest.h>

#include <optional>
#include <vector>

#include "datastruct_base.hh"
using TN = Tree::TreeNode<int>;
namespace {

class Solution {
   public:
    int AverageOfSubtree(TN* root) {
        Tranverse(root);
        return result;
    }

    std::tuple<int, int> Tranverse(TN* root) {
        if (root == nullptr) {
            return {0, 0};
        }

        int leftsum = 0;
        int leftcount = 0;
        if (root->left) {
            std::tie(leftsum, leftcount) = Tranverse(root->left);
        }

        int rightsum = 0;
        int rightcount = 0;
        if (root->right) {
            std::tie(rightsum, rightcount) = Tranverse(root->right);
        }

        if ((leftsum + rightsum + root->val) / (leftcount + rightcount + 1) ==
            root->val) {
            result++;
        }

        return {leftsum + rightsum + root->val, leftcount + rightcount + 1};
    }

   private:
    int result = 0;
};
}  // namespace

#define null std::nullopt
TEST(AverageOfSubtree, t1) {
    std::vector<std::optional<int>> root = {4, 8, 5, 0, 1, null, 6};
    auto* tree = Tree::ConstructBinaryTree(root);
    int output = 5;
    Solution sl;
    int ret = sl.AverageOfSubtree(tree);
    EXPECT_EQ(output, ret);
    /*For the node with value 4: The average of its subtree is (4 + 8 + 5 + 0 +
1 + 6) / 6 = 24 / 6 = 4. For the node with value 5: The average of its subtree
is (5 + 6) / 2 = 11 / 2 = 5. For the node with value 0: The average of its
subtree is 0 / 1 = 0. For the node with value 1: The average of its subtree is 1
/ 1 = 1. For the node with value 6: The average of its subtree is 6 / 1 = 6.*/
}

TEST(AverageOfSubtree, t2) {
    std::vector<std::optional<int>> root = {1};
    auto* tree = Tree::ConstructBinaryTree(root);
    int output = 1;
    Solution sl;
    int ret = sl.AverageOfSubtree(tree);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
