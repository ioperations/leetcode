// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/**Given the root of a binary tree, return the zigzag level order traversal of
 * its nodes' values. (i.e., from left to right, then right to left for the next
 * level and alternate between).*/

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

#include <algorithm>
#include <optional>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> ZigzagLevelOrder(TreeNode *root) {
        vector<vector<int>> ret;
        if (root == nullptr) return ret;

        AddToRet(root, ret, 0);
        for (int i = 1; i < (int)ret.size(); i += 2) {
            reverse(ret[i].begin(), ret[i].end());
        }
        return ret;
    }

    void AddToRet(TreeNode *root, vector<vector<int>> &ret, int n = 0) {
        if (root) {
            if ((int)ret.size() <= n) ret.resize(n + 1);
            ret[n].push_back(root->val);

            AddToRet(root->left, ret, n + 1);
            AddToRet(root->right, ret, n + 1);
        }
    }
};

#include <gtest/gtest.h>

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
        vec.emplace_back(std::to_string(root->val));

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

TEST(memleak, t0) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = ConstructBinaryTree(elements);
    FreeTreeNode(binary_tree);
}

TEST(t0, t1) {
    vector<optional<int>> elements{3,  9, 20, optional<int>(), optional<int>(),
                                   15, 7};
    auto *binary_tree = ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{{3}, {20, 9}, {15, 7}};
    EXPECT_EQ(ret, output);
    FreeTreeNode(binary_tree);
}

TEST(t0, t2) {
    vector<optional<int>> elements{1};
    auto *binary_tree = ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{{1}};
    EXPECT_EQ(ret, output);
    FreeTreeNode(binary_tree);
}

TEST(t0, t3) {
    vector<optional<int>> elements{};
    auto *binary_tree = ConstructBinaryTree(elements);

    Solution sl;
    auto ret = sl.ZigzagLevelOrder(binary_tree);
    vector<vector<int>> output{};
    EXPECT_EQ(ret, output);
    FreeTreeNode(binary_tree);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
