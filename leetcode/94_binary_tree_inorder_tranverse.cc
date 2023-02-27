//**
// Definition for a binary tree node.
// 中序遍历
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

#include <vector>
class Solution {
   public:
    std::vector<int> InorderTraversal(TreeNode *root) {
        std::vector<int> ret;
        InorderTraversal1(root, ret);
        return ret;
    }

    void InorderTraversal1(TreeNode *root, std::vector<int> &ret) {
        if (!root) {
            return;
        }
        InorderTraversal1(root->left, ret);
        ret.push_back(root->val);
        InorderTraversal1(root->right, ret);
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

/// 按照 @elements 的顺序构造一颗二分树
TreeNode *ConstructBinaryTree(std::vector<std::optional<int>> &data) {
    data.resize(data.size() * 2);
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

TEST(t1, t0) {
#define null optional<int>()
    std::vector<optional<int>> vec = {1, null, 2, 3};
    // Output: [1,3,2]

    TreeNode *root = ConstructBinaryTree(vec);
    PrintBt(root);

    Solution s;
    auto ret = s.InorderTraversal(root);
    EXPECT_EQ(ret, (std::vector<int>{1, 3, 2}));

    FreeTreeNode(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
