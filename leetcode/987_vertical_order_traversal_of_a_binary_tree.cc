/*
Given the root of a binary tree, calculate the vertical order traversal of the
binary tree.

For each node at position (row, col), its left and right children will be at
positions (row + 1, col - 1) and (row + 1, col + 1) respectively. The root of
the tree is at (0, 0).

The vertical order traversal of a binary tree is a list of top-to-bottom
orderings for each column index starting from the leftmost column and ending on
the rightmost column. There may be multiple nodes in the same row and same
column. In such a case, sort these nodes by their values.

Return the vertical order traversal of the binary tree.*/

//* Definition for a binary tree node.
#include <cstddef>
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

using namespace std;

struct Mystruct {
    int val;
    int column;
    bool operator<(const Mystruct &rhs) const {
        if (column > rhs.column) {
            return true;
        }
        // column >= rhs.column
        if (val > rhs.val) {
            return true;
        }
        // column >= rhs.column  && val >= rhs.val
        return false;
    }
};

#include <map>

class Solution {
   public:
    vector<vector<int>> VerticalTraversal(TreeNode *root) {
        queue<pair<TreeNode *, int>> q;
        map<int, vector<int>> mp;
        q.push(make_pair(root, 0));
        while (q.size()) {
            int n = q.size();
            map<int, priority_queue<int, vector<int>, greater<int>>> tmp;
            for (int i = 0; i < n; i++) {
                pair<TreeNode *, int> curr = q.front();
                q.pop();
                TreeNode *node = curr.first;
                int col = curr.second;
                tmp[col].push(node->val);
                if (node->left) {
                    q.push(make_pair(node->left, col - 1));
                }
                if (node->right) {
                    q.push(make_pair(node->right, col + 1));
                }
            }
            for (map<int,
                     priority_queue<int, vector<int>, greater<int>>>::iterator
                     it = tmp.begin();
                 it != tmp.end(); it++) {
                while (it->second.size()) {
                    mp[it->first].push_back(it->second.top());
                    it->second.pop();
                }
            }
        }
        vector<vector<int>> ans;
        for (map<int, vector<int>>::iterator it = mp.begin(); it != mp.end();
             it++) {
            ans.push_back(it->second);
        }
        return ans;
    }

    vector<vector<int>> VerticalTraversal1(TreeNode *root) {
        vector<vector<int>> ret;
        if (root == nullptr) return ret;
        priority_queue<Mystruct> q;

        queue<std::pair<TreeNode *, int>> navigate;
        navigate.push({root, 0});

        while (navigate.size()) {
            auto &front = navigate.front();

            if (front.first->left) {
                navigate.push({front.first->left, front.second - 1});
            }
            if (front.first->right) {
                navigate.push({front.first->right, front.second + 1});
            }

            q.push({front.first->val, front.second});

            navigate.pop();
        }

        vector<int> tmp;
        int flag = q.top().column;
        while (q.size()) {
            auto &t = q.top();
            if (t.column == flag) {
                tmp.push_back(t.val);

            } else {
                ret.push_back(tmp);
                tmp.clear();
                flag = t.column;
                tmp.push_back(t.val);
            }
            q.pop();
        }

        if (tmp.size()) {
            ret.push_back(tmp);
        }

        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#define null optional<int>()
#include <algorithm>
#include <optional>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// Decodes your encoded data to tree.
TreeNode *ConstructBinaryTree(std::vector<std::optional<int>> &data) {
    data.resize(data.size() * 3 + 11);
    if (data.size() == 0) return nullptr;

    if (!data[0].has_value()) return nullptr;
    TreeNode *root = new TreeNode(data[0].value());
    queue<TreeNode *> q;
    q.push(root);

    int i = 1;

    while (!q.empty()) {
        TreeNode *cur = q.front();
        q.pop();

        if (!data[i].has_value()) {
            cur->left = NULL;
        } else {
            TreeNode *left_n = new TreeNode(data[i].value());
            cur->left = left_n;
            q.push(left_n);
        }
        i++;

        if (!data[i].has_value()) {
            cur->right = NULL;
        } else {
            TreeNode *right_n = new TreeNode(data[i].value());
            cur->right = right_n;
            q.push(right_n);
        }
        i++;
    }
    return root;
}

// Function to print tree nodes in
// InOrder fashion
void InOrder(TreeNode *root, std::vector<string> &vec) {
    if (root != nullptr) {
        InOrder(root->left, vec);
        vec.push_back(std::to_string(root->val));

        InOrder(root->right, vec);
    }
}

void BfsSearch(TreeNode *root, std::vector<int> &vec) {
    queue<TreeNode *> q;
    q.push(root);

    while (q.size()) {
        TreeNode *tmp = q.front();

        q.pop();

        if (tmp != nullptr) {
            q.push(tmp->left);
            q.push(tmp->right);
            vec.push_back(tmp->val);
        }
    }
}

void FreeTreeNode(TreeNode *root) {
    if (root == nullptr) return;

    FreeTreeNode(root->left);
    FreeTreeNode(root->right);

    delete root;
}

TEST(t0, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<vector<int>> output = {{9}, {3, 15}, {20}, {7}};
    auto *node = ConstructBinaryTree(root);
    // Explanation:
    // Column -1: Only node 9 is in this column.
    // Column 0: Nodes 3 and 15 are in this column in that order from top to
    // bottom. Column 1: Only node 20 is in this column. Column 2: Only node 7
    // is in this column.

    Solution sl;
    auto ret = sl.VerticalTraversal(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    vector<optional<int>> root = {1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> output = {{4}, {2}, {1, 5, 6}, {3}, {7}};
    auto *node = ConstructBinaryTree(root);
    // Column -2: Only node 4 is in this column.
    // Column -1: Only node 2 is in this column.
    // Column 0: Nodes 1, 5, and 6 are in this column.
    //           1 is at the top, so it comes first.
    //           5 and 6 are at the same position (2, 0), so we order them by
    //           their value, 5 before 6.
    // Column 1: Only node 3 is in this column.
    // Column 2: Only node 7 is in this column.
    Solution sl;
    auto ret = sl.VerticalTraversal(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}
TEST(t0, t3) {
    vector<optional<int>> root = {1, 2, 3, 4, 6, 5, 7};
    vector<vector<int>> output = {{4}, {2}, {1, 5, 6}, {3}, {7}};
    auto *node = ConstructBinaryTree(root);
    // This case is the exact same as example 2, but with nodes 5 and 6 swapped.
    // Note that the solution remains the same since 5 and 6 are in the same
    // location and should be ordered by their values. Column -2: Only node 4 is
    Solution sl;
    auto ret = sl.VerticalTraversal(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
