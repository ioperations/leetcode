/*Given two binary trees original and cloned and given a reference to a node
target in the original tree.

The cloned tree is a copy of the original tree.

Return a reference to the same node in the cloned tree.

Note that you are not allowed to change any of the two trees or the target node
and the answer must be a reference to a node in the cloned tree.*/

//* Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* FindNodeInBinaryTree(TreeNode* head, int target) {
    if (head == nullptr) {
        return nullptr;
    }

    if (target == head->val) {
        return head;
    }
    TreeNode* tmp = FindNodeInBinaryTree(head->left, target);
    if (tmp == nullptr) {
        return FindNodeInBinaryTree(head->right, target);
    }
    return tmp;
}
#include <deque>
using namespace std;

class Solution {
   public:
    void DFS(TreeNode* current, deque<bool>& path, TreeNode*& target,
             bool& found) {
        if (current == target) {
            found = true;  // I'd like to get rid of this.
            return;
        }

        // Force it all the way left before you can RETURN and then go right for
        // each subtree.
        if (current->left && found == false)  // If the left node is non-NULL
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

    TreeNode* GetCopyNode(deque<bool>& path, TreeNode* current) {
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

    TreeNode* GetTargetCopy(TreeNode* original, TreeNode* cloned,
                            TreeNode* target) {
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

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

// Decodes your encoded data to tree.
TreeNode* ConstructBinaryTree(std::vector<std::optional<int>>& data) {
    data.resize(data.size() * 4 + 3);
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

TreeNode* ConstructRight(const std::vector<int>& arr) {
    TreeNode node(0);
    TreeNode* z = &node;

    for (auto& ptr : arr) {
        z->right = new TreeNode(ptr);
        z = z->right;
    }

    return node.right;
}

#define null optional<int>()

TEST(memleak, t1) {
    std::vector<int> v{7, 4, 3, 6, 19};

    TreeNode* head = ConstructRight(v);
    TreeNode* head2 = ConstructRight(v);
    int target = 3;
    TreeNode* target_node = FindNodeInBinaryTree(head, target);
    EXPECT_EQ(target_node->val, target);
    std::vector<int> vec;
    BfsSearch(head, vec);

    EXPECT_EQ(vec, v);

    FreeTreeNode(head);
    FreeTreeNode(head2);
}

TEST(t0, t1) {
    std::vector<optional<int>> v{7, 4, 3, null, null, 6, 19};

    TreeNode* head = ConstructBinaryTree(v);
    TreeNode* head2 = ConstructBinaryTree(v);
    int target = 3;
    Solution sl;
    TreeNode* target_node = FindNodeInBinaryTree(head, target);
    TreeNode* ret = sl.GetTargetCopy(head, head2, target_node);
    EXPECT_EQ(ret->val, target);

    FreeTreeNode(head);
    FreeTreeNode(head2);
}

TEST(t0, t2) {
    std::vector<optional<int>> v{7};

    TreeNode* head = ConstructBinaryTree(v);
    TreeNode* head2 = ConstructBinaryTree(v);
    int target = 7;
    Solution sl;

    TreeNode* target_node = FindNodeInBinaryTree(head, target);
    TreeNode* ret = sl.GetTargetCopy(head, head2, target_node);
    EXPECT_EQ(ret->val, target);

    FreeTreeNode(head);
    FreeTreeNode(head2);
}

TEST(t0, t3) {
    std::vector<optional<int>> v{8,    null, 6,    null, 5,    null, 4,
                                 null, 3,    null, 2,    null, 1};

    TreeNode* head = ConstructBinaryTree(v);
    TreeNode* head2 = ConstructBinaryTree(v);
    int target = 4;
    Solution sl;
    TreeNode* target_node = FindNodeInBinaryTree(head, target);
    TreeNode* ret = sl.GetTargetCopy(head, head2, target_node);

    EXPECT_EQ(ret->val, target);

    FreeTreeNode(head);
    FreeTreeNode(head2);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
