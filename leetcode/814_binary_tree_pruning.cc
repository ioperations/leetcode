/*Given the root of a binary tree, return the same tree where every subtree (of
the given tree) not containing a 1 has been removed.

A subtree of a node node is node plus every node that is a descendant of node.*/

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
class Solution {
   public:
    TreeNode* PruneTree(TreeNode*& root) {
        if (root == nullptr) return root;
        PruneTree(root->left);
        PruneTree(root->right);
        if (root->left == nullptr && root->right == nullptr && !root->val) {
            delete root;
            root = nullptr;
            return nullptr;
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

void BfsSearch(TreeNode* root, std::vector<optional<int>>& vec) {
    queue<TreeNode*> q;
    q.push(root);

    while (q.size()) {
        TreeNode* tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        } else {
            vec.push_back(optional<int>());
        }
    }

    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
        if (!it->has_value()) {
            vec.pop_back();
            continue;
        }
        break;
    }
}

void FreeTreeNode(TreeNode* root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

void PrintBt(const std::string& prefix, const TreeNode* node, bool is_left) {
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

void PrintBt(const TreeNode* node) { PrintBt("", node, false); }

#include <gtest/gtest.h>

#include <iostream>

#define null optional<int>()
TEST(t0, t1) {
    vector<optional<int>> root = {1, null, 0, 0, 1};
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    auto* ret = sl.PruneTree(node);
    vector<optional<int>> output{1, null, 0, null, 1};

    vector<optional<int>> ret_node;
    BfsSearch(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1, 0, 1, 0, 0, 0, 1};
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    auto* ret = sl.PruneTree(node);
    vector<optional<int>> output{1, null, 1, null, 1};

    vector<optional<int>> ret_node;
    BfsSearch(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}
TEST(t0, t3) {
    vector<optional<int>> root = {1, 1, 0, 1, 1, 0, 1, 0};
    auto* node = ConstructBinaryTree(root);
    Solution sl;
    auto* ret = sl.PruneTree(node);
    vector<optional<int>> output{1, 1, 0, 1, 1, null, 1};

    vector<optional<int>> ret_node;
    BfsSearch(ret, ret_node);
    // Explanation:
    // Only the red nodes satisfy the property "every subtree not containing a
    // 1".
    // The diagram on the right represents the answer.
    EXPECT_EQ(ret_node, output);
    FreeTreeNode(node);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
