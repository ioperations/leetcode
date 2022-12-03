/*
    You are given the root of a binary tree with n nodes where each node in the
    tree has node.val coins. There are n coins in total throughout the whole
   tree.

    In one move, we may choose two adjacent nodes and move one coin from one
   node to another. A move may be from parent to child, or from child to parent.

    Return the minimum number of moves required to make every node have exactly
   one coin.
*/

#include <cstdlib>
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
    int steps = 0;

    int Helper(TreeNode* root) {
        if (!root) return 0;

        int left_coins_required = Helper(root->left);
        int right_coins_required = Helper(root->right);

        steps +=
            abs(left_coins_required) +
            abs(right_coins_required);  // if we want or have number of excess
                                        // coins, we need to take a step, hence
                                        // abs cause in case of negative too, we
                                        // need to add one step

        return left_coins_required + right_coins_required - 1 +
               root->val;  // -1 because of root taking 1 coin for itself too.
    }

    int DistributeCoins(TreeNode* root) {
        Helper(root);
        return steps;
    }
};

#include <gtest/gtest.h>

#include <iostream>
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

TEST(t0, t1) {
    std::vector<optional<int>> v{3, 0, 0};
    TreeNode* root = ConstructBinaryTree(v);
    int out = 2;
    Solution sl;
    // From the root of the tree, we move one coin to its left child, and one
    // coin to its right child.
    int ret = sl.DistributeCoins(root);
    EXPECT_EQ(ret, out);
    FreeTreeNode(root);
}

TEST(t0, t2) {
    std::vector<optional<int>> v{0, 3, 0};
    TreeNode* root = ConstructBinaryTree(v);
    // From the left child of the root, we move two coins to the root [taking
    // two moves]. Then, we move one coin from the root of the tree to the right
    // child.
    int out = 3;
    Solution sl;
    int ret = sl.DistributeCoins(root);
    EXPECT_EQ(ret, out);
    FreeTreeNode(root);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
