/*
Given the root of a binary tree, flatten the tree into a "linked list":

The "linked list" should use the same TreeNode class where the right child
pointer points to the next node in the list and the left child pointer is always
null. The "linked list" should be in the same order as a pre-order traversal of
the binary tree
*/

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
#include <queue>
#include <vector>

class Solution {
   public:
    void Flatten(TreeNode *root) {
        if (!root || (!root->left && !root->right)) return;
        std::queue<TreeNode *> q;
        Search(root, q);

        TreeNode *n = root;
        while (q.size()) {
            n->right = q.front();
            q.pop();
            n = n->right;
        }
    }

    void FlattenV2(TreeNode *root) {
        if (!root or (!root->left and !root->right)) return;
        std::queue<TreeNode *> nodes;
        Search(root, nodes);
        TreeNode *p = root;
        while (!nodes.empty()) {
            p->right = nodes.front();
            nodes.pop();
            p = p->right;
        }
    }

    void Search(TreeNode *&root, std::queue<TreeNode *> &nodes) {
        if (root) {
            nodes.push(root);
            Search(root->left, nodes);
            Search(root->right, nodes);
            root->left = nullptr;
            root->right = nullptr;
        }
    }

    std::vector<int> PreOrder(TreeNode *n) {
        std::vector<int> ret;
        PreOrder(n, ret);
        return ret;
    }

    void PreOrder(TreeNode *node, std::vector<int> &vec) {
        if (node == nullptr) {
            return;
        }
        vec.push_back(node->val);
        PreOrder(node->left, vec);
        PreOrder(node->right, vec);
    }

    void PreOrder(TreeNode *node, std::queue<TreeNode *> &q) {
        if (node == nullptr) {
            return;
        }
        q.push(node);
        PreOrder(node->left, q);
        PreOrder(node->right, q);
    }
};

#include <vector>

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

TreeNode *AddToRoot(TreeNode *root, const std::vector<int> &elements) {
    for (auto &ptr : elements) {
        root = AddToRoot(root, ptr);
    }
    return root;
}

TreeNode *ConstructTree(const std::vector<int> &elements) {
    if (!elements.size()) {
        return nullptr;
    }

    TreeNode *root = new TreeNode(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
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
#include <gtest/gtest.h>

#include <iostream>

void ExpectEqRight(TreeNode *const root, const std::vector<int> &elements) {
    TreeNode *n = root;
    int i = 0;
    while (n != nullptr) {
        EXPECT_EQ(n->val, elements[i]);
        i++;
        n = n->right;
    }
    EXPECT_EQ(i, elements.size());
}

TEST(t0, t1) {
    TreeNode *n = ConstructTree(std::vector<int>{1, 2, 5, 3, 4, 6});
    Solution s;
    auto ret = s.PreOrder(n);
    s.Flatten(n);
    ExpectEqRight(n, ret);
    FreeRoot(n);
}

TEST(t0, t2) {
    TreeNode *n = ConstructTree(std::vector<int>{});
    Solution s;
    auto ret = s.PreOrder(n);
    s.Flatten(n);
    ExpectEqRight(n, ret);
    FreeRoot(n);
}

TEST(t0, t3) {
    TreeNode *n = ConstructTree(std::vector<int>{0});
    Solution s;
    auto ret = s.PreOrder(n);
    s.Flatten(n);
    ExpectEqRight(n, ret);
    FreeRoot(n);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
