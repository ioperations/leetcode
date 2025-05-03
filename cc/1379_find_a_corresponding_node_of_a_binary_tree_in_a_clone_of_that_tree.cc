// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two binary trees original and cloned and given a reference to a node
target in the original tree.

The cloned tree is a copy of the original tree.

Return a reference to the same node in the cloned tree.

Note that you are not allowed to change any of the two trees or the target node
and the answer must be a reference to a node in the cloned tree.*/

//* Definition for a binary tree node.
#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace Tree;

template <typename T>
static TreeNode<T>* FindNodeInBinaryTree(TreeNode<T>* head, int target) {
  if (head == nullptr) {
    return nullptr;
  }

  if (target == head->val) {
    return head;
  }
  auto* tmp = FindNodeInBinaryTree(head->left, target);
  if (tmp == nullptr) {
    return FindNodeInBinaryTree(head->right, target);
  }
  return tmp;
}
#include <deque>
#include <optional>
#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    template <typename T>
    void DFS(TreeNode<T>* current, deque<bool>& path, TreeNode<T>*& target,
             bool& found) {
        if (current == target) {
            found = true;  // I'd like to get rid of this.
            return;
        }

        // Force it all the way left before you can RETURN and then go right for
        // each subtree.
        if (current->left && found == false)  // If the left node is non-nullptr
                                              // and a target hasn't been found.
        {
            path.push_back(true);
            DFS(current->left, path, target, found);  // recurse
            if (!found)  // If the target has been found, keep the path
                         // constant.
                path.pop_back();
        }

        if (current->right && found == false) {
            path.push_back(false);
            DFS(current->right, path, target, found);
            if (!found) path.pop_back();
        }

        return;
    }

    template <typename T>
    TreeNode<T>* GetCopyNode(deque<bool>& path, TreeNode<T>* current) {
        while (!path.empty()) {
            // Now iterating from the opposite side of the queue.
            if (path.front())  // True == left
                current = current->left;
            else  // False == right
                current = current->right;
            path.pop_front();
        }
        return current;
    }

    template <typename T>
    TreeNode<T>* GetTargetCopy(TreeNode<T>* original, TreeNode<T>* cloned,
                               TreeNode<T>* target) {
        // Passed a reference to the head of original and cloned, and the
        // reference of the target in original. Solution 1: non-unique values
        deque<bool> path =
            {};  // True -> left | Left -> right //Queue of single bits,
                 // intended to be an efficient use of space to keep track
        // of a path to follow in the clone.
        bool found = false;  // Has the target been found?

        DFS(original, path, target, found);
        return GetCopyNode(path, cloned);
    }
};

using namespace std;

#define null optional<int>()

TEST(memleak, t1) {
  std::vector<int> const v{7, 4, 3, 6, 19};

  auto* head = ConstructRight(v);
  auto* head2 = ConstructRight(v);
  int const target = 3;
  auto* target_node = FindNodeInBinaryTree(head, target);
  EXPECT_EQ(target_node->val, target);
  std::vector<int> vec;
  BfsSearch(head, vec);

  EXPECT_EQ(vec, v);

  FreeTreeNode(head);
  FreeTreeNode(head2);
}

TEST(find_a_corresponding_node_of_a_binary_tree_in_a_clone_of_that_tree, t1) {
  std::vector<optional<int>> const v{7, 4, 3, null, null, 6, 19};

  auto* head = ConstructBinaryTree(v);
  auto* head2 = ConstructBinaryTree(v);
  int const target = 3;
  Solution sl;
  auto* target_node = FindNodeInBinaryTree(head, target);
  auto* ret = sl.GetTargetCopy(head, head2, target_node);
  EXPECT_EQ(ret->val, target);

  FreeTreeNode(head);
  FreeTreeNode(head2);
}

TEST(find_a_corresponding_node_of_a_binary_tree_in_a_clone_of_that_tree, t2) {
  std::vector<optional<int>> const v{7};

  auto* head = ConstructBinaryTree(v);
  auto* head2 = ConstructBinaryTree(v);
  int const target = 7;
  Solution sl;

  auto* target_node = FindNodeInBinaryTree(head, target);
  auto* ret = sl.GetTargetCopy(head, head2, target_node);
  EXPECT_EQ(ret->val, target);

  FreeTreeNode(head);
  FreeTreeNode(head2);
}

TEST(find_a_corresponding_node_of_a_binary_tree_in_a_clone_of_that_tree, t3) {
  std::vector<optional<int>> const v{8,    null, 6,    null, 5,    null, 4,
                                     null, 3,    null, 2,    null, 1};

  auto* head = ConstructBinaryTree(v);
  auto* head2 = ConstructBinaryTree(v);
  int const target = 4;
  Solution sl;
  auto* target_node = FindNodeInBinaryTree(head, target);
  auto* ret = sl.GetTargetCopy(head, head2, target_node);

  EXPECT_EQ(ret->val, target);

  FreeTreeNode(head);
  FreeTreeNode(head2);
}

}  // namespace
