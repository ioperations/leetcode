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
#include <vector>

class Solution {
   public:
    std::vector<int> PreorderTraversal(TreeNode *root) {
        std::vector<int> ret;
        Tranverse(root, ret);
        return ret;
    }

    void Tranverse(TreeNode *root, std::vector<int> &val) {
        if (root == nullptr) {
            return;
        }

        val.push_back(root->val);
        Tranverse(root->left, val);

        Tranverse(root->right, val);
    }
};

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<optional<int>> vec{1, 2, 3};
    TreeNode *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, (std::vector<int>{1, 2, 3}));

    FreeTreeNode(root);
}

TEST(t0, t2) {
    std::vector<optional<int>> vec{};
    TreeNode *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{});

    FreeTreeNode(root);
}

TEST(t0, t3) {
    std::vector<optional<int>> vec{1};
    TreeNode *root = ConstructBinaryTree(vec);
    Solution s;
    std::vector<int> ret = s.PreorderTraversal(root);

    EXPECT_EQ(ret, std::vector<int>{1});
    FreeTreeNode(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
