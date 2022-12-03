/*
Implement the BSTIterator class that represents an iterator over the in-order
traversal of a binary search tree (BST):

BSTIterator(TreeNode root) Initializes an object of the BSTIterator class. The
root of the BST is given as part of the constructor. The pointer should be
initialized to a non-existent number smaller than any element in the BST.
boolean hasNext() Returns true if there exists a number in the traversal to the
right of the pointer, otherwise returns false. int next() Moves the pointer to
the right, then returns the number at the pointer. Notice that by initializing
the pointer to a non-existent smallest number, the first call to next() will
return the smallest element in the BST.

You may assume that next() calls will always be valid. That is, there will be at
least a next number in the in-order traversal when next() is called.
*/

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
#include <stack>

class BSTIterator {
   private:
    TreeNode* pt;
    std::stack<TreeNode*> s;

    void PushStack(TreeNode* node) {
        while (node != nullptr) {
            s.push(node);
            node = node->left;
        }
    }
    // pushed the left subtree to the stack
   public:
    BSTIterator(TreeNode* root) {
        pt = root;
        PushStack(pt);
    }

    int next() {
        TreeNode* temp = s.top();
        s.pop();
        PushStack(temp->right);
        return temp->val;
    }

    // We pop the top node return its value
    // then we push its right subtree to stack to continue inorder traversal

    bool hasNext() { return !s.empty(); }
    // if stack is empty then we have already traversed out tree
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

#include <gtest/gtest.h>

#include <iostream>
#include <vector>

TreeNode* AddToRoot(TreeNode* root, int val) {
    if (root == nullptr) {
        return nullptr;
    }
    if (val < root->val) {
        if (root->left) {
            TreeNode* head = AddToRoot(root->left, val);
            root->left = head;
            return root;
        }
        root->left = new TreeNode(val);

    } else {
        if (root->right) {
            TreeNode* head = AddToRoot(root->right, val);
            root->right = head;
            return root;
        }
        root->right = new TreeNode(val);
    }
    return root;
}

TreeNode* AddToRoot(TreeNode* root, const std::vector<int>& elements) {
    for (auto& ptr : elements) {
        root = AddToRoot(root, ptr);
    }
    return root;
}

TreeNode* ConstructTree(const std::vector<int>& elements) {
    if (!elements.size()) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(elements[0]);

    for (int i = 1; i < (int)elements.size(); i++) {
        root = AddToRoot(root, elements[i]);
    }

    return root;
}

void FreeRoot(TreeNode* root) {
    if (root == nullptr) {
        return;
    }

    FreeRoot(root->left);
    FreeRoot(root->right);
    delete root;
}

TEST(t0, t1) {
    TreeNode* root = ConstructTree(std::vector<int>{1, 2, 4, 5, 6});

    BSTIterator* it = new BSTIterator(root);

    EXPECT_EQ(it->hasNext(), true);

    delete it;

    FreeRoot(root);
}

TEST(t0, t2) {
    TreeNode* root = ConstructTree(std::vector<int>{7, 3, 15, 9, 20});

    BSTIterator* it = new BSTIterator(root);
    EXPECT_EQ(it->next(), 3);
    EXPECT_EQ(it->next(), 7);
    EXPECT_EQ(it->hasNext(), true);
    EXPECT_EQ(it->next(), 9);
    EXPECT_EQ(it->hasNext(), true);
    EXPECT_EQ(it->next(), 15);
    EXPECT_EQ(it->hasNext(), true);
    EXPECT_EQ(it->next(), 20);
    EXPECT_EQ(it->hasNext(), false);

    delete it;

    FreeRoot(root);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
