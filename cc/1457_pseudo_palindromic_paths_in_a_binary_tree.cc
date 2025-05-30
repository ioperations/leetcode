// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a binary tree where node values are digits from 1 to 9. A path in the
binary tree is said to be pseudo-palindromic if at least one permutation of the
node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf
nodes.*/

#include <cstddef>
// Definition for a binary tree node.
#include <algorithm>
#include <stack>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

namespace {
class Solution {
   public:
    int m_count = 0;
    template <typename T>
    void Dfs(TreeNode<T>* root, vector<T> mpp) {
        if (root->left == nullptr && root->right == nullptr) {
            mpp[root->val]++;
            int count_odd = 0;
            for (auto i : mpp) {
                if (i % 2 == 1) {
                    count_odd++;
                }
            }
            if (count_odd <= 1) {
                m_count++;
            }
            return;
        }
        mpp[root->val]++;
        if (root->left != nullptr) {
            Dfs(root->left, mpp);
        }
        if (root->right != nullptr) {
            Dfs(root->right, mpp);
        }
        mpp[root->val] -= mpp[root->val];
    }
    template <typename T>
    int PseudoPalindromicPaths(TreeNode<T>* root) {
        vector<int> const mpp(10, 0);
        Dfs(root, mpp);
        return m_count;
    }
    template <typename T>
    bool IsPalindromic(std::vector<TreeNode<T>*> n) {
        if (n.size() <= 1) return true;
        std::sort(n.begin(), n.end(),
                  [](const TreeNode<T>* lft, const TreeNode<T>* rht) -> bool {
                      return lft->val > rht->val;
                  });

        int last = n[0]->val;

        int count = 1;

        int const size = n.size();
        bool allow = true;

        for (int j = 1; j < size; j++) {
            if (n[j]->val == last) {
                count++;
                continue;
            }
            if (count % 2 == 0) {
                count = 0;
                last = n[j]->val;
            } else if (allow) {
                allow = false;

                count = 1;
                last = n[j]->val;
            } else {
                return false;
            }
        }
        return true;
    }
    template <typename T>
    int PseudoPalindromicPathsV1(TreeNode<T>* root) {
        if (root == nullptr) return 0;
        std::vector<TreeNode<T>*> path;
        std::stack<TreeNode<T>*> q;
        q.push(root);
        int sum = 0;
        while (q.size()) {
            auto* top = q.top();
            path.push_back(top);
            q.pop();
            if (top->left || top->right) {
                if (top->left) q.push(top->left);
                if (top->right) q.push(top->right);
            } else {
                if (IsPalindromic(path)) {
                    sum++;
                }
                path.pop_back();
            }
        }

        return sum;
    }
};

#include <optional>

using namespace std;

#define null optional<int>()
TEST(pseudo_palindromic_paths_in_a_binary_tree, t1) {
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  3  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  3  |    |  1  |    |     |   |  1  |
             |_____|    |_____|    |_____|   |_____|


    */
    std::vector<optional<int>> const root = {2, 3, 1, 3, 1, null, 1};
    int const output = 2;
    auto* node = ConstructBinaryTree(root);

    // Explanation: The figure above represents the given binary tree. There are
    // three paths going from the root node to leaf nodes: the red path [2,3,3],
    // the green path [2,1,1], and the path [2,3,1]. Among these paths only red
    // path and green path are pseudo-palindromic paths since the red path
    // [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path
    // [2,1,1] can be rearranged in [1,2,1] (palindrome).
    Solution sl;
    int const ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(pseudo_palindromic_paths_in_a_binary_tree, t2) {
    std::vector<optional<int>> const root = {2,    1,    1,    1,    3, null,
                                             null, null, null, null, 1};
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  1  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  1  |    |  3  |    |     |   |     |
             |_____|    |_____|    |_____|   |_____|

       _______ ____   _____   ____
       |     | |  |   |   |  |   |
       |     | |  |   |   |  | 1 |
       |_____| |__|   |___|  |___|

    */

    int const output = 1;
    auto* node = ConstructBinaryTree(root);
    // The figure above represents the given binary tree. There are three paths
    // going from the root node to leaf nodes: the green path [2,1,1], the path
    // [2,1,3,1], and the path [2,1]. Among these paths only the green path is
    // pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1]
    // (palindrome).

    Solution sl;
    int const ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(pseudo_palindromic_paths_in_a_binary_tree, t3) {
    std::vector<optional<int>> const root = {9};
    int const output = 1;
    auto* node = ConstructBinaryTree(root);

    Solution sl;
    int const ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(pseudo_palindromic_paths_in_a_binary_tree_v2, t1) {
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  3  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  3  |    |  1  |    |     |   |  1  |
             |_____|    |_____|    |_____|   |_____|


    */
    std::vector<optional<int>> const root = {2, 3, 1, 3, 1, null, 1};
    int const output = 2;
    auto* node = ConstructBinaryTree(root);

    // Explanation: The figure above represents the given binary tree. There are
    // three paths going from the root node to leaf nodes: the red path [2,3,3],
    // the green path [2,1,1], and the path [2,3,1]. Among these paths only red
    // path and green path are pseudo-palindromic paths since the red path
    // [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path
    // [2,1,1] can be rearranged in [1,2,1] (palindrome).
    Solution sl;
    int const ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(pseudo_palindromic_paths_in_a_binary_tree_v2, t2) {
    std::vector<optional<int>> const root = {2,    1,    1,    1,    3, null,
                                             null, null, null, null, 1};
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  1  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  1  |    |  3  |    |     |   |     |
             |_____|    |_____|    |_____|   |_____|

       _______ ____   _____   ____
       |     | |  |   |   |  |   |
       |     | |  |   |   |  | 1 |
       |_____| |__|   |___|  |___|

    */

    int const output = 1;
    auto* node = ConstructBinaryTree(root);
    // The figure above represents the given binary tree. There are three paths
    // going from the root node to leaf nodes: the green path [2,1,1], the path
    // [2,1,3,1], and the path [2,1]. Among these paths only the green path is
    // pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1]
    // (palindrome).

    Solution sl;
    int const ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(pseudo_palindromic_paths_in_a_binary_tree_v2, t3) {
    std::vector<optional<int>> const root = {9};
    int const output = 1;
    auto* node = ConstructBinaryTree(root);

    Solution sl;
    int const ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

}  // namespace
