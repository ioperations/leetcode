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

class Solution {
   public:
    int minCameraCover(TreeNode *root) {
        int sum = 0;
        // if root is not monitored, we place an additional camera here
        if (dfs(root, sum) == 0) sum++;
        return sum;
    }

    int dfs(TreeNode *root, int &sum) {
        if (!root) return 1;
        int l = dfs(root->left, sum);
        int r = dfs(root->right, sum);
        // if at least 1 child is not monitored, we need to place a camera at
        // current node
        if (l == 0 || r == 0) {
            sum++;
            return 2;
        }  // if at least 1 child has camera, the current node is monitored.
           // Thus, we don't need to place a camera here
        else if (l == 2 || r == 2) {
            return 1;
        }  // if both children are monitored but have no camera, we don't need
           // to place a camera here. We place the camera at its parent node at
           // the higher level.
        else {
            return 0;
        }
        return -1;  // this return statement won't be triggered
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
using namespace std;
#define null optional<int>()
#include <algorithm>
#include <optional>
#include <queue>
#include <string>
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

TEST(t0, t1) {
    std::vector<optional<int>> v{0, 0, null, 0, 0};
    int out = 1;
    TreeNode *n = ConstructBinaryTree(v);
    Solution sl;
    int ret = sl.minCameraCover(n);
    EXPECT_EQ(ret, out);
    // One camera is enough to monitor all nodes if placed as shown.
    FreeTreeNode(n);
}

TEST(t0, t2) {
    std::vector<optional<int>> v{0, 0, null, 0, null, 0, null, null, 0};
    int out = 2;
    TreeNode *n = ConstructBinaryTree(v);
    Solution sl;
    int ret = sl.minCameraCover(n);
    EXPECT_EQ(ret, out);
    // At least two cameras are needed to monitor all nodes of the tree. The
    // above image shows one of the valid configurations of camera placement.
    FreeTreeNode(n);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
