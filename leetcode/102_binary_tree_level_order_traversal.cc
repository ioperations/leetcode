/*

Given the root of a binary tree, return the level order traversal of its nodes'
values. (i.e., from left to right, level by level).

*/
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    vector<vector<int>> LevelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        struct Status {
            TreeNode* t;
            int level;
        };
        if (root == nullptr) return ret;

        queue<Status> q;

        Status tmp;
        tmp.level = 1;
        tmp.t = root;

        q.push(tmp);

        vector<int> tmp_vec;

        int now_level = 1;
        while (q.size()) {
            Status tmp = q.front();
            if (tmp.level == now_level) {
                tmp_vec.push_back(tmp.t->val);
            } else {
                ret.push_back(tmp_vec);
                tmp_vec.clear();
                now_level++;
                tmp_vec.push_back(tmp.t->val);
            }
            if (tmp.t->left) {
                q.push({tmp.t->left, now_level + 1});
            }
            if (tmp.t->right) {
                q.push({tmp.t->right, now_level + 1});
            }

            q.pop();
        }
        if (tmp_vec.size()) ret.push_back(tmp_vec);
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <string>

using namespace std;

// Decodes your encoded data to tree.
TreeNode* ConstructBinaryTree(std::vector<std::optional<int>>& data) {
    data.resize(data.size() * 2 + 31);
    if (data.size() == 0) return nullptr;

    if (!data[0].has_value()) return nullptr;
    TreeNode* root = new TreeNode(data[0].value());
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        if (!data[i].has_value()) {
            cur->left = NULL;
        } else {
            TreeNode* left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = NULL;
        } else {
            TreeNode* right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode* root, std::vector<string>& vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val));

        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode* root, std::vector<int>& vec) {
    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
        TreeNode* tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

TEST(t0, t1) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<vector<int>> output = {{3}, {9, 20}, {15, 7}};
    Solution sl;
    TreeNode* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(t0, t2) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {1};
    vector<vector<int>> output = {{1}};
    Solution sl;
    TreeNode* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

TEST(t0, t3) {
#define null \
    optional<int> {}
    vector<optional<int>> root = {};
    vector<vector<int>> output = {};
    Solution sl;
    TreeNode* tree = ConstructBinaryTree(root);
    auto ret = sl.LevelOrder(tree);
    EXPECT_EQ(ret, output);
    FreeTreeNode(tree);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
