/*Given the root of a binary tree, return the average value of the nodes on each
 * level in the form of an array. Answers within 10-5 of the actual answer will
 * be accepted.*/
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
#include <map>
#include <queue>
#include <vector>

using namespace std;
class Solution {
   public:
    vector<double> AverageOfLevels(TreeNode *root) {
        std::vector<double> v;
        if (root == nullptr) return v;
        queue<std::pair<TreeNode *, int>> q;
        int cur_level = 1;
        int cur_count = 0;
        long cur_sum = 0;
        q.push({root, cur_level});
        while (q.size()) {
            auto &z = q.front();
            if (z.second == cur_level) {
                cur_sum += z.first->val;
                cur_count++;
            } else {
                v.push_back((double)cur_sum / cur_count);
                cur_level++;
                cur_sum = z.first->val;
                cur_count = 1;
            }
            if (z.first->left) {
                q.push({z.first->left, cur_level + 1});
            }
            if (z.first->right) {
                q.push({z.first->right, cur_level + 1});
            }
            q.pop();
        }
        if (cur_count) {
            v.push_back((double)cur_sum / cur_count);
        }
        return v;
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

#define null optional<int>()
TEST(t0, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(t0, t2) {
    vector<optional<int>> root = {3, 9, 20, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(t0, t3) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
