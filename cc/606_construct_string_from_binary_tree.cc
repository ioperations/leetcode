// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given the root of a binary tree, construct a string consisting of parenthesis
and integers from a binary tree with the preorder traversal way, and return it.

Omit all the empty parenthesis pairs that do not affect the one-to-one mapping
relationship between the string and the original binary tree.

*/

//* Definition for a binary tree node.
#include <string>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Solution {
   public:
    template <typename T>
    string Tree2str(TreeNode<T>* root) {
        // pass
        std::string str;
        Tree2str(root, str);
        return str;
    }
    template <typename T>
    void Tree2str(TreeNode<T>* root, std::string& str) {
        if (root == nullptr) return;
        str += std::to_string(root->val);
        if (root->left != nullptr || root->right != nullptr) {
            str += "(";
            Tree2str(root->left, str);
            str += ")";
        }

        if (root->right != nullptr) {
            str += "(";
            Tree2str(root->right, str);
            str += ")";
        }
    }
};

#include <optional>
#include <vector>

using namespace std;

#define null optional<int>()

TEST(construct_string_from_binary_tree, t1) {
    /*
                          _________
                          |       |
                          |   1   |
                          |_______|



                 _________          _________
                 |       |          |       |
                 |   2   |          |   3   |
                 |_______|          |_______|


      _________
      |       |
      |   4   |
      |_______|

    */
    vector<optional<int>> const root = {1, 2, 3, 4};
    std::string const output = "1(2(4))(3)";
    // Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need
    // to omit all the unnecessary empty parenthesis pairs. And it will be
    // "1(2(4))(3)"
    Solution sl;
    auto* node = ConstructBinaryTree(root);
    auto ret = sl.Tree2str(node);
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}
TEST(construct_string_from_binary_tree, t2) {
  vector<optional<int>> const root = {1, 2, 3, null, 4};

  /*
                        _________
                        |       |
                        |   1   |
                        |_______|



               _________          _________
               |       |          |       |
               |   2   |          |   3   |
               |_______|          |_______|


    _________          _________
    |       |          |       |
    | null  |          |   4   |
    |_______|          |_______|

  */

  std::string const output = "1(2()(4))(3)";
  // Almost the same as the first example, except we cannot omit the first
  // parenthesis pair to break the one-to-one mapping relationship between the
  // input and the output.
  Solution sl;
  auto* node = ConstructBinaryTree(root);
  auto ret = sl.Tree2str(node);
  EXPECT_EQ(ret, output);

  FreeTreeNode(node);
}

}  // namespace
