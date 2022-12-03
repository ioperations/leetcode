/*
You are given the root of a binary search tree (BST), where the values of
exactly two nodes of the tree were swapped by mistake. Recover the tree without
changing its structure.
*/

#include <utility>
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
    TreeNode* prev = nullptr;
    TreeNode* first = nullptr;
    TreeNode* second = nullptr;
    void RecoverTree(TreeNode* root) {
        Inorder(root);
        std::swap(first->val, second->val);
    }

    void Inorder(TreeNode* root) {
        if (root == nullptr) return;

        Inorder(root->left);

        if (prev != nullptr && root->val < prev->val) {
            if (first == nullptr) {
                first = prev;
            }
            second = root;
        }
        prev = root;
        Inorder(root->right);
    }
};

#include <gtest/gtest.h>

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
            cur->left = nullptr;
        } else {
            TreeNode* left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = nullptr;
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
#define null optional<int>()
    vector<optional<int>> root = {1, 3, null, null, 2};
    vector<optional<int>> output = {3, 1, null, null, 2};
    // Explanation: 3 cannot be a left child of 1 because 3 > 1. Swapping 1
    // and 3 makes the BST valid.
    vector<int> in;
    {
        TreeNode* input = ConstructBinaryTree(root);
        Solution sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        TreeNode* out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

TEST(t0, t2) {
#define null optional<int>()
    vector<optional<int>> root = {3, 1, 4, null, null, 2};
    vector<optional<int>> output = {2, 1, 4, null, null, 3};
    // 2 cannot be in the right subtree of 3 because 2 < 3. Swapping 2 and 3
    // makes the BST valid.

    vector<int> in;
    {
        TreeNode* input = ConstructBinaryTree(root);
        Solution sl;
        sl.RecoverTree(input);
        BfsSearch(input, in);
        FreeTreeNode(input);
    }

    vector<int> ou;
    {
        TreeNode* out = ConstructBinaryTree(output);
        BfsSearch(out, ou);
        FreeTreeNode(out);
    }
    EXPECT_EQ(ou, in);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
