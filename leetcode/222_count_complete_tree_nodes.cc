/*Given the root of a complete binary tree, return the number of the nodes in
the tree.

According to Wikipedia, every level, except possibly the last, is completely
filled in a complete binary tree, and all nodes in the last level are as far
left as possible. It can have between 1 and 2h nodes inclusive at the last level
h.

Design an algorithm that runs in less than O(n) time complexity.*/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

#include <queue>

class Solution {
   public:
    int CountNodes(TreeNode *root) {
        std::queue<TreeNode *> q;
        if (root == nullptr) return 0;
        q.emplace(root);
        int count = 0;
        while (q.size()) {
            TreeNode *n = q.front();
            if (n->left) q.emplace(n->left);
            if (n->right) q.emplace(n->right);
            q.pop();
            count++;
        }
        return count;
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
    data.resize(data.size() * 3 + 100);
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
    vector<optional<int>> root = {1, 2, 3, 4, 5, 6};
    int output = 6;
    TreeNode *const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {};
    int output = 0;
    TreeNode *const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t3) {
    vector<optional<int>> root = {1};
    int output = 1;
    TreeNode *const node = ConstructBinaryTree(root);
    Solution sl;
    int const ret = sl.CountNodes(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
