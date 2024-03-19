// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the root of a binary tree, return the average value of the nodes on each
 * level in the form of an array. Answers within 10-5 of the actual answer will
 * be accepted.*/
// Definition for a binary tree node.
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "datastruct_base.hh"

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
using namespace Tree;

namespace {
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
                if (cur_count == 0) {
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

#include <optional>

using namespace std;

#define null optional<int>()
TEST(average_of_levels_in_binary_tree, t1) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        REQUIRE(ptr1 == Catch::Approx(output[i]));
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(average_of_levels_in_binary_tree, t2) {
    vector<optional<int>> root = {3, 9, 20, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        REQUIRE(ptr1 == Catch::Approx(output[i]));
        i++;
    }
    FreeTreeNode(rootnode);
}

TEST(average_of_levels_in_binary_tree, t3) {
    vector<optional<int>> root = {3, 9, 20, null, null, 15, 7};
    vector<double> output = {3.00000, 14.50000, 11.00000};
    // Explanation: The average value of nodes on level 0 is 3, on level 1
    // is 14.5, and on level 2 is 11. Hence return [3, 14.5, 11].
    Solution sl;
    auto *rootnode = ConstructBinaryTree(root);
    auto ret = sl.AverageOfLevels(rootnode);
    int i = 0;
    for (auto ptr1 : ret) {
        REQUIRE(ptr1 == Catch::Approx(output[i]));
        i++;
    }
    FreeTreeNode(rootnode);
}

}  // namespace
