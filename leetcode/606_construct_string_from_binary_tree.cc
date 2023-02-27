/*
Given the root of a binary tree, construct a string consisting of parenthesis
and integers from a binary tree with the preorder traversal way, and return it.

Omit all the empty parenthesis pairs that do not affect the one-to-one mapping
relationship between the string and the original binary tree.

*/

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
#include <string>
using namespace std;

class Solution {
   public:
    string Tree2str(TreeNode *root) {
        // pass
        std::string str;
        Tree2str(root, str);
        return str;
    }
    void Tree2str(TreeNode *root, std::string &str) {
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
#define null optional<int>()

TEST(t0, t1) {
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
    vector<optional<int>> root = {1, 2, 3, 4};
    std::string output = "1(2(4))(3)";
    // Explanation: Originally, it needs to be "1(2(4)())(3()())", but you need
    // to omit all the unnecessary empty parenthesis pairs. And it will be
    // "1(2(4))(3)"
    Solution sl;
    auto *node = ConstructBinaryTree(root);
    auto ret = sl.Tree2str(node);
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}
TEST(t0, t2) {
    vector<optional<int>> root = {1, 2, 3, null, 4};

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

    std::string output = "1(2()(4))(3)";
    // Almost the same as the first example, except we cannot omit the first
    // parenthesis pair to break the one-to-one mapping relationship between the
    // input and the output.
    Solution sl;
    auto *node = ConstructBinaryTree(root);
    auto ret = sl.Tree2str(node);
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
