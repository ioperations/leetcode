/*Given a binary tree root, a node X in the tree is named good if in the path
from root to X there are no nodes with a value greater than X.

Return the number of good nodes in the binary tree.
*/
// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
#include <algorithm>
#include <functional>

class Solution {
   public:
    int GoodNodes(TreeNode *root) {
        int count = 0;
        if (root == nullptr) return 0;

        std::function<void(TreeNode *, int)> fun = [&](TreeNode *n,
                                                       int val) -> void {
            if (n == nullptr) return;
            if (n->val >= val) count++;
            int z = std::max(n->val, val);
            fun(n->left, z);
            fun(n->right, z);
        };
        fun(root, root->val);
        return count;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
using namespace std;
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
#define null optional<int>()
    vector<optional<int>> root = {3, 1, 4, 3, null, 1, 5};
    int output = 4;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    /*Nodes in blue are good.
    Root Node (3) is always a good node.
    Node 4 -> (3,4) is the maximum value in the path starting from the root.
    Node 5 -> (3,4,5) is the maximum value in the path
    Node 3 -> (3,1,3) is the maximum value in the path.
    */
    FreeTreeNode(node);
}

TEST(t0, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 3, null, 4, 2};
    int output = 3;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Node 2 -> (3, 3, 2) is not good, because "3" is higher than it.
    FreeTreeNode(node);
}

TEST(t0, t3) {
#define null optional<int>()
    vector<optional<int>> root = {1};
    int output = 1;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}

TEST(t0, t4) {
#define null optional<int>()
    vector<optional<int>> root = {9, null, 3, 6};
    /*
     *
     *        9
     *      /    \
     *   null     3
     *          /
     *         6
     */
    int output = 1;
    auto *node = ConstructBinaryTree(root);
    Solution sl;
    int ret = sl.GoodNodes(node);
    EXPECT_EQ(ret, output);
    // Root is considered as good.
    FreeTreeNode(node);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
