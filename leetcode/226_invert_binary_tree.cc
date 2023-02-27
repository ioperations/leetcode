/*Given the root of a binary tree, invert the tree, and return its root.*/

//* Definition for a binary tree node.
#include <cstddef>
#include <utility>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    bool deleted = false;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution {
   public:
   private:
    void Invert(TreeNode *root) {
        if (root == NULL) return;
        std::swap(root->left, root->right);
        Invert(root->left);
        Invert(root->right);
    }

   public:
    TreeNode *InvertTree(TreeNode *root) {
        if (root == NULL) return NULL;
        Invert(root);
        return root;
    }

    TreeNode *ZInvertTree(TreeNode *root) {
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

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// Decodes your encoded data to tree.
TreeNode *ConstructBinaryTree(std::vector<std::optional<int>> &data) {
    data.resize(data.size() * 3);
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
    std::vector<optional<int>> root = {4, 2, 7, 1, 3, 6, 9};
    std::vector<int> output = {4, 7, 2, 9, 6, 3, 1};

    TreeNode *head = ConstructBinaryTree(root);

    PrintBt(head);

    Solution sl;
    head = sl.InvertTree(head);

    std::vector<int> vec1;
    BfsSearch(head, vec1);
    EXPECT_EQ(vec1, output);
    FreeTreeNode(head);
};

TEST(t0, t2) {
    std::vector<optional<int>> root = {1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                                       11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                                       21, 22, 23, 24, 25, 26, 27, 28, 29};
    std::vector<int> output = {1,  3,  2,  7,  6,  5,  4,  15, 14, 13,
                               12, 11, 10, 9,  8,  29, 28, 27, 26, 25,
                               24, 23, 22, 21, 20, 19, 18, 17, 16};

    TreeNode *head = ConstructBinaryTree(root);

    PrintBt(head);

    Solution sl;
    head = sl.InvertTree(head);

    std::vector<int> vec1;
    BfsSearch(head, vec1);
    EXPECT_EQ(vec1, output);
    FreeTreeNode(head);
};

TEST(t0, t3) {
    std::vector<optional<int>> root = {2, 1, 3};
    std::vector<int> output = {2, 3, 1};

    TreeNode *head = ConstructBinaryTree(root);

    Solution sl;
    head = sl.InvertTree(head);

    std::vector<int> vec1;
    BfsSearch(head, vec1);
    EXPECT_EQ(vec1, output);
    FreeTreeNode(head);
};

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
