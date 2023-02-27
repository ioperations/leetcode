/*Given a binary tree, find the lowest common ancestor (LCA) of two given nodes
in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is
defined between two nodes p and q as the lowest node in T that has both p and q
as descendants (where we allow a node to be a descendant of itself).”*/

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
   public:
    TreeNode *LowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        // pass
        if (root == nullptr) return nullptr;

        if (root->val == p->val || root->val == q->val) return root;

        TreeNode *a = LowestCommonAncestor(root->left, p, q);
        TreeNode *b = LowestCommonAncestor(root->right, p, q);

        if (a != nullptr && b != nullptr) return root;
        if (a == nullptr && b != nullptr) return b;
        if (a != nullptr && b == nullptr) return a;

        return nullptr;
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
    data.resize(data.size() * 3 + 31);
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

TreeNode *FindInTree(TreeNode *n, int v) {
    if (n == nullptr) return nullptr;

    if (n->val == v) return n;

    TreeNode *le = FindInTree(n->left, v);
    if (le == nullptr) return FindInTree(n->right, v);
    return le;
}

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
#define null optional<int>()
    vector<optional<int>> root = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    int p = 5, q = 1;
    int output = 3;
    TreeNode *node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    TreeNode *pn = FindInTree(node, p);
    TreeNode *qn = FindInTree(node, q);
    TreeNode *ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
    int p = 5, q = 4;
    int output = 5;
    TreeNode *node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    TreeNode *pn = FindInTree(node, p);
    TreeNode *qn = FindInTree(node, q);
    TreeNode *ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

TEST(t0, t3) {
#define null optional<int>()
    vector<optional<int>> root = {1, 2};
    int p = 1, q = 2;
    int output = 1;
    TreeNode *node = ConstructBinaryTree(root);
    // Explanation: The LCA of nodes 5 and 1 is 3.
    Solution sl;
    TreeNode *pn = FindInTree(node, p);
    TreeNode *qn = FindInTree(node, q);
    TreeNode *ret = sl.LowestCommonAncestor(node, pn, qn);
    EXPECT_EQ(ret->val, output);
    FreeTreeNode(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
