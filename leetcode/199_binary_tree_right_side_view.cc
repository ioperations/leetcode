/*Given the root of a binary tree, imagine yourself standing on the right side
   of it, return the values of the nodes you can see ordered from top to bottom.

 */

#include <vector>

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
using namespace std;

class Solution {
   public:
    vector<int> RightSideView(TreeNode* root) {
        vector<int> ret;
        if (root == nullptr) return ret;
        ret.push_back(root->val);
        int h = 1;
        FindRight(root, ret, h, 1);
        return ret;
    }

    void FindRight(TreeNode* root, vector<int>& ret, int& max_height,
                   int now_height) {
        // pass
        if (root == nullptr) return;

        if (now_height > max_height) {
            ret.push_back(root->val);
            max_height++;
        }
        FindRight(root->right, ret, max_height, now_height + 1);
        FindRight(root->left, ret, max_height, now_height + 1);
    }
};

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Decodes your encoded data to tree.
TreeNode* ConstructBinaryTree(std::vector<std::optional<int>>& data) {
    data.resize(data.size() * 3 + 11);
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
    vector<optional<int>> root = {
        1, 2, 3, std::optional<int>(), 5, std::optional<int>(), 4};
    TreeNode* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> output = {1, 3, 4};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1, std::optional<int>(), 3};
    TreeNode* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> output = {1, 3};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

TEST(t0, t3) {
    vector<optional<int>> root = {};
    TreeNode* node = ConstructBinaryTree(root);
    Solution sl;
    auto ret = sl.RightSideView(node);
    vector<int> output = {};
    EXPECT_EQ(ret, output);

    FreeTreeNode(node);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
