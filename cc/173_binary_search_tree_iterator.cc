// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

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

#include <stack>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

namespace {
template <typename T>
class BSTIterator {
   private:
    TreeNode<T>* pt;
    std::stack<TreeNode<T>*> s;

    void PushStack(TreeNode<T>* node) {
        while (node != nullptr) {
            s.push(node);
            node = node->left;
        }
    }
    // pushed the left subtree to the stack
   public:
    BSTIterator(TreeNode<T>* root) {
        pt = root;
        PushStack(pt);
    }

    int next() {
        TreeNode<T>* temp = s.top();
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

#include <vector>

TEST(binary_search_tree_iterator, t1) {
    TreeNode<int>* root = ConstructTree(std::vector<int>{1, 2, 4, 5, 6});

    BSTIterator<int>* it = new BSTIterator(root);

    EXPECT_EQ(it->hasNext(), true);

    delete it;

    FreeTreeNode(root);
}

TEST(binary_search_tree_iterator, t2) {
    TreeNode<int>* root = ConstructTree(std::vector<int>{7, 3, 15, 9, 20});

    BSTIterator<int>* it = new BSTIterator(root);
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

    FreeTreeNode(root);
}
}  // namespace
