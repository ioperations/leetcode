// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
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

#include <functional>
#include <optional>
#include <queue>
#include <utility>
#include <vector>

#include "datastruct_base.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Tree;

struct Mystruct {
    int val;
    int column;
    bool operator<(const Mystruct& rhs) const {
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

namespace {
class Solution {
   public:
    template <typename T>
    vector<vector<T>> VerticalTraversal(TreeNode<T>* root) {
        queue<pair<TreeNode<T>*, int>> q;
        map<int, vector<int>> mp;
        q.push(make_pair(root, 0));
        while (q.size()) {
            int n = q.size();
            map<int, priority_queue<int, vector<int>, greater<int>>> tmp;
            for (int i = 0; i < n; i++) {
                pair<TreeNode<T>*, int> curr = q.front();
                q.pop();
                auto* node = curr.first;
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
                 it != tmp.end(); ++it) {
                while (it->second.size()) {
                    mp[it->first].push_back(it->second.top());
                    it->second.pop();
                }
            }
        }
        vector<vector<int>> ans;
        for (map<int, vector<int>>::iterator it = mp.begin(); it != mp.end();
             ++it) {
            ans.push_back(it->second);
        }
        return ans;
    }

    template <typename T>
    vector<vector<T>> VerticalTraversal1(TreeNode<T>* root) {
        vector<vector<T>> ret;
        if (root == nullptr) return ret;
        priority_queue<Mystruct> q;

        queue<std::pair<TreeNode<T>*, int>> navigate;
        navigate.push({root, 0});

        while (navigate.size()) {
            auto& front = navigate.front();

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
            auto& t = q.top();
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

#define null optional<int>()

using namespace std;

TEST(vertical_order_traversal_of_a_binary_tree, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<vector<int>> output = {{9}, {3, 15}, {20}, {7}};
    auto* node = ConstructBinaryTree(root);
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

TEST(vertical_order_traversal_of_a_binary_tree, t2) {
    vector<optional<int>> root = {1, 2, 3, 4, 5, 6, 7};
    vector<vector<int>> output = {{4}, {2}, {1, 5, 6}, {3}, {7}};
    auto* node = ConstructBinaryTree(root);
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
TEST(vertical_order_traversal_of_a_binary_tree, t3) {
    vector<optional<int>> root = {1, 2, 3, 4, 6, 5, 7};
    vector<vector<int>> output = {{4}, {2}, {1, 5, 6}, {3}, {7}};
    auto* node = ConstructBinaryTree(root);
    // This case is the exact same as example 2, but with nodes 5 and 6 swapped.
    // Note that the solution remains the same since 5 and 6 are in the same
    // location and should be ordered by their values. Column -2: Only node 4 is
    Solution sl;
    auto ret = sl.VerticalTraversal(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

}  // namespace
