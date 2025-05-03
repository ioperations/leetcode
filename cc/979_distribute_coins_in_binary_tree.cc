// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given the root of a binary tree with n nodes where each node in the
    tree has node.val coins. There are n coins in total throughout the whole
   tree.

    In one move, we may choose two adjacent nodes and move one coin from one
   node to another. A move may be from parent to child, or from child to parent.

    Return the minimum number of moves required to make every node have exactly
   one coin.
*/

#include <cstdlib>
#include <optional>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   public:
    int m_steps = 0;

    template <typename T>
    int Helper(TreeNode<T>* root) {
        if (!root) return 0;

        int const left_coins_required = Helper(root->left);
        int const right_coins_required = Helper(root->right);

        m_steps +=
            abs(left_coins_required) +
            abs(right_coins_required);  // if we want or have number of excess
                                        // coins, we need to take a step, hence
                                        // abs cause in case of negative too, we
                                        // need to add one step

        return left_coins_required + right_coins_required - 1 +
               root->val;  // -1 because of root taking 1 coin for itself too.
    }

    template <typename T>
    int DistributeCoins(TreeNode<T>* root) {
        Helper(root);
        return m_steps;
    }
};

using namespace std;

TEST(distribute_coins_in_binary_tree, t1) {
  std::vector<optional<int>> const v{3, 0, 0};
  auto* root = ConstructBinaryTree(v);
  int const out = 2;
  Solution sl;
  // From the root of the tree, we move one coin to its left child, and one
  // coin to its right child.
  int const ret = sl.DistributeCoins(root);
  EXPECT_EQ(ret, out);
  FreeTreeNode(root);
}

TEST(distribute_coins_in_binary_tree, t2) {
  std::vector<optional<int>> const v{0, 3, 0};
  auto* root = ConstructBinaryTree(v);
  // From the left child of the root, we move two coins to the root [taking
  // two moves]. Then, we move one coin from the root of the tree to the right
  // child.
  int const out = 3;
  Solution sl;
  int const ret = sl.DistributeCoins(root);
  EXPECT_EQ(ret, out);
  FreeTreeNode(root);
}

}  // namespace
