/*Given the root of a binary tree, return the average value of the nodes on each
 * level in the form of an array. Answers within 10-5 of the actual answer will
 * be accepted.*/
// Definition for a binary tree node.
#include <map>
#include <queue>
#include <vector>
#include <exception>

#include "datastruct_base.hh"

using namespace std;
class Solution {
   public:
    template <typename T>
    vector<double> AverageOfLevels(TreeNode<T> *root) {
        std::vector<double> v;
        if (root == nullptr) return v;
        queue<std::pair<TreeNode<T> *, int>> q;
        int cur_level = 1;
        int cur_count = 0;
        long cur_sum = 0;
        q.push({root, cur_level});
        while (q.size()) {
            auto &z = q.front();
            if (z.second == cur_level) {
                cur_sum += z.first->val;
                cur_count++;
            } else {
                if (cur_count == 0){
                    throw std::runtime_error("divide by zero error");
                }
                v.push_back((double)cur_sum / cur_count);
                cur_level++;
                cur_sum = z.first->val;
                cur_count = 1;
            }
            if (z.first->left) {
                q.push({z.first->left, cur_level + 1});
            }
            if (z.first->right) {
                q.push({z.first->right, cur_level + 1});
            }
            q.pop();
        }
        if (cur_count) {
            v.push_back((double)cur_sum / cur_count);
        }
        return v;
    }
};

#include <gtest/gtest.h>

#include <iostream>
#include <optional>
#include <queue>
#include <vector>
using namespace std;

#define null optional<int>()
TEST(t0, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(t0, t2) {
    vector<optional<int>> root = {3, 9, 20, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(t0, t3) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        EXPECT_DOUBLE_EQ(ptr1, output[i]);
        i++;
    }
    FreeTreeNode(rootnode);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
