/*Given the root of a Binary Search Tree and a target number k, return true if
 * there exist two elements in the BST such that their sum is equal to the given
 * target.*/

// * Definition for a binary tree node.
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
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
   public:
    std::unordered_map<int, bool> m;
    bool FindTarget(TreeNode* root, int k) {
        if (root == nullptr) return false;

        if (m.find(k - root->val) != m.end()) return true;
        m[root->val] = 1;

        return FindTarget(root->left, k) || FindTarget(root->right, k);
    }

    void Inorder(TreeNode* root, vector<int>& in) {
        if (root == nullptr) {
            return;
        }
        Inorder(root->left, in);
        in.push_back(root->val);
        Inorder(root->right, in);
    }

    bool FindTargetV2(TreeNode* root, int k) {
        vector<int> in;
        Inorder(root, in);

        set<int> st;

        for (int i = 0; i < (int)in.size(); i++) {
            int const target = k - in[i];
            if (st.find(target) != st.end()) {
                return true;
            }
            st.insert(in[i]);
        }

        return false;
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

#define null optional<int>()

TEST(t0, t1) {
    vector<optional<int>> root = {5, 3, 6, 2, 4, null, 7};
    int const k = 9;
    bool const output = true;
    TreeNode* node = ConstructBinaryTree(root);
    Solution sl;
    bool const ret = sl.FindTarget(node, k);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {5, 3, 6, 2, 4, null, 7};
    int const k = 28;
    bool const output = false;
    TreeNode* node = ConstructBinaryTree(root);
    Solution sl;
    bool const ret = sl.FindTarget(node, k);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
