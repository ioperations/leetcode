/*

Given the root of a Binary Search Tree (BST), convert it to a Greater Tree such
that every key of the original BST is changed to the original key plus the sum
of all keys greater than the original key in BST.

As a reminder, a binary search tree is a tree that satisfies these constraints:

The left subtree of a node contains only nodes with keys less than the node's
key. The right subtree of a node contains only nodes with keys greater than the
node's key. Both the left and right subtrees must also be binary search trees.
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

class Solution {
   public:
    int Dfs(TreeNode *root, int above_sum) {
        if (!root) return 0;

        int right = Dfs(root->right, above_sum);
        int left = Dfs(root->left, right + root->val + above_sum);

        int sum_below = root->val + left + right;

        root->val += above_sum + right;

        return sum_below;
    }

    TreeNode *ConvertBst(TreeNode *root) {
        Dfs(root, 0);
        return root;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <queue>

TreeNode *AddToRoot(TreeNode *root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode *head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode(val);

    } else {
        if (root->right) {
            TreeNode *head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode(val);
    }
    return root;
}

void FreeRoot(TreeNode *root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

/**
 * @brief 向 @root 当中加入节点
 * @param @elements 节点的数组
 * @return
 */
TreeNode *AddToRoot(TreeNode *root, const std::vector<int> &elements) {
    for (auto &ptr : elements) {
        root = AddToRoot(root, ptr);
    }

    return root;
}

std::vector<int> BFS(TreeNode *root) {
    std::vector<int> ret;
    std::queue<TreeNode *> q;

    q.push(root);

    while (!q.empty()) {
        auto *c = q.front();
        if (c != nullptr) {
            q.push(c->left);
            q.push(c->right);
        }

        q.pop();

        if (c != nullptr) {
            ret.push_back(c->val);
        }
    }
    return ret;
}

TEST(memleak, t1) {
    TreeNode *root = new TreeNode(-1);

    for (int i = 0; i < 100; i++) {
        root = AddToRoot(root, i);
    }

    FreeRoot(root);
}

TEST(t0, t1) {
    // root = [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    // Output: [4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
    TreeNode *root = new TreeNode(4);
    root = AddToRoot(root, std::vector<int>{1, 6, 0, 2, 5, 7, 3, 8});

    {
        auto ret = BFS(root);
        EXPECT_EQ(ret, (std::vector<int>{4, 1, 6, 0, 2, 5, 7, 3, 8}));
    }

    {
        Solution s;
        root = s.ConvertBst(root);
    }

    {
        auto ret = BFS(root);
        EXPECT_EQ(ret, (std::vector<int>{30, 36, 21, 36, 35, 26, 15, 33, 8}));
    }

    FreeRoot(root);
}

TEST(t0, t2) {
    // Input: root = [0,null,1]
    // Output: [1,null,1]

    TreeNode *root = new TreeNode(0);
    root = AddToRoot(root, std::vector<int>{1});

    {
        auto ret = BFS(root);
        EXPECT_EQ(ret, (std::vector<int>{0, 1}));
    }
    {
        Solution s;
        root = s.ConvertBst(root);
    }
    {
        auto ret = BFS(root);
        EXPECT_EQ(ret, (std::vector<int>{1, 1}));
    }

    FreeRoot(root);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
