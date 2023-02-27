/*Given the root of a binary tree and an integer targetSum, return all
root-to-leaf paths where the sum of the node values in the path equals
targetSum. Each path should be returned as a list of the node values, not node
references.

A root-to-leaf path is a path starting from the root and ending at any leaf
node. A leaf is a node with no children.

 */

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

class Solution {
    std::vector<vector<int>> m_ret;
    void Inorder(TreeNode *root, std::vector<int> &path, int target_sum) {
        if (root == nullptr) return;
        path.push_back(root->val);
        if (root->left) {
            Inorder(root->left, path, target_sum);
        }
        if (root->right) {
            Inorder(root->right, path, target_sum);
        }

        if (!root->left && !root->right) {
            int const sum = accumulate(path.begin(), path.end(), 0);
            if (sum == target_sum) {
                m_ret.push_back(path);
            }
        }

        path.pop_back();
    }

   public:
    vector<vector<int>> PathSum(TreeNode *root, int target_sum) {
        std::vector<int> path;

        Inorder(root, path, target_sum);

        return m_ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#define null optional<int>()
#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// Decodes your encoded data to tree.
TreeNode *ConstructBinaryTree(std::vector<std::optional<int>> &data) {
    data.resize(data.size() * 3 + 11);
    if (data.size() == 0) return nullptr;

    if (!data[0].has_value()) return nullptr;
    TreeNode *root = new TreeNode(data[0].value());
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();

        if (!data[i].has_value()) {
            cur->left = NULL;
        } else {
            TreeNode *left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = NULL;
        } else {
            TreeNode *right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode *root, std::vector<string> &vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val));

        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode *root, std::vector<int> &vec) {
    queue<TreeNode *> q;
    q.push(root);

    while (q.size()) {
        TreeNode *tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

void FreeTreeNode(TreeNode *root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

void PrintBt(const std::string &prefix, const TreeNode *node, bool is_left) {
    if (node != nullptr) {
        std::cout << prefix;

        std::cout << (is_left ? "├──" : "└──");

        // print the value of the node
        std::cout << node->val << std::endl;

        // enter the next tree level - left and right branch
        PrintBt(prefix + (is_left ? "│   " : "    "), node->left, true);
        PrintBt(prefix + (is_left ? "│   " : "    "), node->right, false);
    }
}

void PrintBt(const TreeNode *node) { PrintBt("", node, false); }

TEST(t0, t1) {
    vector<optional<int>> root = {5, 4, 8,    11,   null, 13, 4,
                                  7, 2, null, null, 5,    1};
    int const target_sum = 22;
    vector<vector<int>> const output = {{5, 4, 11, 2}, {5, 8, 4, 5}};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);

    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1, 2, 3};
    int const target_sum = 5;
    vector<vector<int>> const output = {};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);

    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t3) {
    vector<optional<int>> root = {1, 2};
    int const target_sum = 0;
    vector<vector<int>> const output = {};
    /*
    Explanation:
        There are two paths whose sum equals targetSum : 5 + 4 + 11 + 2 =
           22 5 + 8 + 4 + 5 = 22
    */

    auto *node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.PathSum(node, target_sum);

    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
