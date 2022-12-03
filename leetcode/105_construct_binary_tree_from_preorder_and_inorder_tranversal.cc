/*Given two integer arrays preorder and inorder where preorder is the preorder
 * traversal of a binary tree and inorder is the inorder traversal of the same
 * tree, construct and return the binary tree.*/

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right)
        : val(x), left(left), right(right) {}
};
#include <unordered_map>
#include <vector>
using namespace std;
class Solution {
   public:
    TreeNode* Build(vector<int>& preorder, int p_start, int p_end,
                    unordered_map<int, int>& inorder_map, int i_start,
                    int i_end) {
        if (p_start > p_end || i_start > i_end) return nullptr;

        TreeNode* root = new TreeNode(preorder[p_start]);
        int i_root = inorder_map[root->val];
        int nums_left = i_root - i_start;

        root->left = Build(preorder, p_start + 1, p_start + nums_left,
                           inorder_map, i_start, i_root - 1);
        root->right = Build(preorder, p_start + 1 + nums_left, p_end,
                            inorder_map, i_root + 1, i_end);

        return root;
    }
    TreeNode* BuildTree(vector<int>& preorder, vector<int>& inorder) {
        unordered_map<int, int> inorder_map;
        for (int i = 0; i < (int)inorder.size(); i++)
            inorder_map[inorder[i]] = i;

        return Build(preorder, 0, preorder.size() - 1, inorder_map, 0,
                     inorder.size() - 1);
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// Decodes your encoded data to tree.
TreeNode* ConstructBinaryTree(std::vector<std::optional<int>>& data) {
    data.resize(data.size() * 3);
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
    vector<int> preorder = {3, 9, 20, 15, 7}, inorder = {9, 3, 15, 20, 7};
    Solution sl;
    TreeNode* node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {3, 9, 20, 15, 7};
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> preorder = {-1}, inorder = {-1};
    Solution sl;
    TreeNode* node = sl.BuildTree(preorder, inorder);
    std::vector<int> ret;
    BfsSearch(node, ret);

    FreeTreeNode(node);
    vector<int> output = {-1};
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
