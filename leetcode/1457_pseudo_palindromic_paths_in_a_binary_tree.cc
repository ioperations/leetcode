/*Given a binary tree where node values are digits from 1 to 9. A path in the
binary tree is said to be pseudo-palindromic if at least one permutation of the
node values in the path is a palindrome.

Return the number of pseudo-palindromic paths going from the root node to leaf
nodes.*/

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
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

class Solution {
   public:
    int count = 0;
    void Dfs(TreeNode *root, vector<int> mpp) {
        if (root->left == NULL && root->right == NULL) {
            mpp[root->val]++;
            int count_odd = 0;
            for (auto i : mpp) {
                if (i % 2 == 1) {
                    count_odd++;
                }
            }
            if (count_odd <= 1) {
                count++;
            }
            return;
        }
        mpp[root->val]++;
        if (root->left != NULL) {
            Dfs(root->left, mpp);
        }
        if (root->right != NULL) {
            Dfs(root->right, mpp);
        }
        mpp[root->val] -= mpp[root->val];
    }
    int PseudoPalindromicPaths(TreeNode *root) {
        vector<int> mpp(10, 0);
        Dfs(root, mpp);
        return count;
    }
    bool IsPalindromic(std::vector<TreeNode *> n) {
        if (n.size() <= 1) return true;
        std::sort(n.begin(), n.end(),
                  [](const TreeNode *lft, const TreeNode *rht) -> bool {
                      return lft->val > rht->val;
                  });

        int last = n[0]->val;

        int count = 1;

        int size = n.size();
        bool allow = true;

        for (int j = 1; j < size; j++) {
            if (n[j]->val == last) {
                count++;
                continue;
            }
            if (count % 2 == 0) {
                count = 0;
                last = n[j]->val;
            } else if (allow) {
                allow = false;

                count = 1;
                last = n[j]->val;
            } else {
                return false;
            }
        }
        return true;
    }
    int PseudoPalindromicPathsV1(TreeNode *root) {
        if (root == nullptr) return 0;
        std::vector<TreeNode *> path;
        std::stack<TreeNode *> q;
        q.push(root);
        int sum = 0;
        while (q.size()) {
            auto *top = q.top();
            path.push_back(top);
            q.pop();
            if (top->left || top->right) {
                if (top->left) q.push(top->left);
                if (top->right) q.push(top->right);
            } else {
                if (IsPalindromic(path)) {
                    sum++;
                }
                path.pop_back();
            }
        }

        return sum;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
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

void PrintBt(const std::string &prefix, const TreeNode *node, bool is_left) {
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

void PrintBt(const TreeNode *node) { PrintBt("", node, false); }

#define null optional<int>()
TEST(t0, t1) {
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  3  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  3  |    |  1  |    |     |   |  1  |
             |_____|    |_____|    |_____|   |_____|


    */
    std::vector<optional<int>> root = {2, 3, 1, 3, 1, null, 1};
    int output = 2;
    auto *node = ConstructBinaryTree(root);

    // Explanation: The figure above represents the given binary tree. There are
    // three paths going from the root node to leaf nodes: the red path [2,3,3],
    // the green path [2,1,1], and the path [2,3,1]. Among these paths only red
    // path and green path are pseudo-palindromic paths since the red path
    // [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path
    // [2,1,1] can be rearranged in [1,2,1] (palindrome).
    Solution sl;
    int ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t2) {
    std::vector<optional<int>> root = {2,    1,    1,    1,    3, null,
                                       null, null, null, null, 1};
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  1  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  1  |    |  3  |    |     |   |     |
             |_____|    |_____|    |_____|   |_____|

       _______ ____   _____   ____
       |     | |  |   |   |  |   |
       |     | |  |   |   |  | 1 |
       |_____| |__|   |___|  |___|

    */

    int output = 1;
    auto *node = ConstructBinaryTree(root);
    // The figure above represents the given binary tree. There are three paths
    // going from the root node to leaf nodes: the green path [2,1,1], the path
    // [2,1,3,1], and the path [2,1]. Among these paths only the green path is
    // pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1]
    // (palindrome).

    Solution sl;
    int ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t0, t3) {
    std::vector<optional<int>> root = {9};
    int output = 1;
    auto *node = ConstructBinaryTree(root);

    Solution sl;
    int ret = sl.PseudoPalindromicPaths(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t1, t1) {
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  3  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  3  |    |  1  |    |     |   |  1  |
             |_____|    |_____|    |_____|   |_____|


    */
    std::vector<optional<int>> root = {2, 3, 1, 3, 1, null, 1};
    int output = 2;
    auto *node = ConstructBinaryTree(root);

    // Explanation: The figure above represents the given binary tree. There are
    // three paths going from the root node to leaf nodes: the red path [2,3,3],
    // the green path [2,1,1], and the path [2,3,1]. Among these paths only red
    // path and green path are pseudo-palindromic paths since the red path
    // [2,3,3] can be rearranged in [3,2,3] (palindrome) and the green path
    // [2,1,1] can be rearranged in [1,2,1] (palindrome).
    Solution sl;
    int ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t1, t2) {
    std::vector<optional<int>> root = {2,    1,    1,    1,    3, null,
                                       null, null, null, null, 1};
    /*
                             _______
                             |     |
                             |  2  |
                             |_____|
                      _______         _______
                      |     |         |     |
                      |  1  |         |  1  |
                      |_____|         |_____|
             _______    _______    _______   _______
             |     |    |     |    |     |   |     |
             |  1  |    |  3  |    |     |   |     |
             |_____|    |_____|    |_____|   |_____|

       _______ ____   _____   ____
       |     | |  |   |   |  |   |
       |     | |  |   |   |  | 1 |
       |_____| |__|   |___|  |___|

    */

    int output = 1;
    auto *node = ConstructBinaryTree(root);
    // The figure above represents the given binary tree. There are three paths
    // going from the root node to leaf nodes: the green path [2,1,1], the path
    // [2,1,3,1], and the path [2,1]. Among these paths only the green path is
    // pseudo-palindromic since [2,1,1] can be rearranged in [1,2,1]
    // (palindrome).

    Solution sl;
    int ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}

TEST(t1, t3) {
    std::vector<optional<int>> root = {9};
    int output = 1;
    auto *node = ConstructBinaryTree(root);

    Solution sl;
    int ret = sl.PseudoPalindromicPathsV1(node);
    EXPECT_EQ(ret, output);
    FreeTreeNode(node);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
