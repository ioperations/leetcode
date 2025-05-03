// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, invert the tree, and return its root.*/

//* Definition for a binary tree node.
#include <cstddef>
#include <utility>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
class Solution {
   private:
    template <typename T>
    void Invert(TreeNode<T>* root) {
        if (root == nullptr) return;
        std::swap(root->left, root->right);
        Invert(root->left);
        Invert(root->right);
    }

   public:
    template <typename T>
    TreeNode<T>* InvertTree(TreeNode<T>* root) {
        if (root == nullptr) return nullptr;
        Invert(root);
        return root;
    }
    template <typename T>

    TreeNode<T>* ZInvertTree(TreeNode<T>* root) {
        // pass
        if (root) {
            if (root->left) {
                if (root->left->left == nullptr) {
                    std::swap(root->left, root->right);
                } else {
                    InvertTree(root->left);
                    InvertTree(root->right);
                }
            }
        }

        return root;
    }
};

#include <optional>
#include <vector>

using namespace std;

TEST(invert_binary_tree, t1) {
  std::vector<optional<int>> const root = {4, 2, 7, 1, 3, 6, 9};
  std::vector<int> const output = {4, 7, 2, 9, 6, 3, 1};

  auto* head = ConstructBinaryTree(root);

  PrintBt(head);

  Solution sl;
  head = sl.InvertTree(head);

  std::vector<int> vec1;
  BfsSearch(head, vec1);
  EXPECT_EQ(vec1, output);
  FreeTreeNode(head);
};

TEST(invert_binary_tree, t2) {
  std::vector<optional<int>> const root = {
      1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
      16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
  std::vector<int> const output = {1,  3,  2,  7,  6,  5,  4,  15, 14, 13,
                                   12, 11, 10, 9,  8,  29, 28, 27, 26, 25,
                                   24, 23, 22, 21, 20, 19, 18, 17, 16};

  auto* head = ConstructBinaryTree(root);

  PrintBt(head);

  Solution sl;
  head = sl.InvertTree(head);

  std::vector<int> vec1;
  BfsSearch(head, vec1);
  EXPECT_EQ(vec1, output);
  FreeTreeNode(head);
};

TEST(invert_binary_tree, t3) {
  std::vector<optional<int>> const root = {2, 1, 3};
  std::vector<int> const output = {2, 3, 1};

  auto* head = ConstructBinaryTree(root);

  Solution sl;
  head = sl.InvertTree(head);

  std::vector<int> vec1;
  BfsSearch(head, vec1);
  EXPECT_EQ(vec1, output);
  FreeTreeNode(head);
};

}  // namespace
