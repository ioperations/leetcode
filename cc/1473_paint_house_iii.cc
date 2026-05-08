// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*There is a row of m houses in a small city, each house must be painted with
one of the n colors (labeled from 1 to n), some houses that have been painted
last summer should not be painted again.

A neighborhood is a maximal group of continuous houses that are painted with the
same color.

For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2},
{3,3}, {2}, {1,1}]. Given an array houses, an m x n matrix cost and an integer
target where:

houses[i]: is the color of the house i, and 0 if the house is not painted yet.
cost[i][j]: is the cost of paint the house i with the color j + 1.
Return the minimum cost of painting all the remaining houses in such a way that
there are exactly target neighborhoods. If it is not possible, return -1.*/

#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;  // NOLINT

namespace {
class Solution {
   private:
    vector<vector<vector<int>>> m_mem;
    int Solve(vector<int>& houses, vector<vector<int>>& cost, int target,
              int index, int prev_color) {
        int const num_houses = static_cast<int>(houses.size());
        int const num_colors = static_cast<int>(cost.at(0).size());
        if (index == num_houses) {
            if (target == 0) {
                return 0;
            }
            return INT_MAX;
        }
        if (target < 0) {
            return INT_MAX;
        }
        if (m_mem.at(index).at(prev_color).at(target) != -1) {
            return m_mem.at(index).at(prev_color).at(target);
        }
        if (houses.at(index) == 0) {
            int min_cost = INT_MAX;
            for (int color = 1; color <= num_colors; color++) {
                int ans = 0;
                if (color == prev_color) {
                    ans = Solve(houses, cost, target, index + 1, prev_color);
                } else {
                    ans = Solve(houses, cost, target - 1, index + 1, color);
                }
                if (ans != INT_MAX) {
                    ans += cost.at(index).at(color - 1);
                }
                min_cost = min(min_cost, ans);
            }
            return m_mem.at(index).at(prev_color).at(target) = min_cost;
        }
        if (houses.at(index) == prev_color) {
            return m_mem.at(index).at(prev_color).at(target) =
                       Solve(houses, cost, target, index + 1, prev_color);
        }
        return m_mem.at(index).at(prev_color).at(target) =
                   Solve(houses, cost, target - 1, index + 1, houses.at(index));
    }

   public:
    int MinCost(vector<int>& houses, vector<vector<int>>& cost, int num_houses,
                int num_colors, int target) {
        m_mem = vector<vector<vector<int>>>(
            num_houses,
            vector<vector<int>>(num_colors + 1, vector<int>(target + 1, -1)));
        int const ans = Solve(houses, cost, target, 0, 0);
        return ans == INT_MAX ? -1 : ans;
    }
};

TEST(PaintHouseIii, t1) {
    vector<int> houses = {0, 0, 0, 0, 0};
    vector<vector<int>> cost = {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}};
    int const num_houses = 5, num_colors = 2, target = 3;
    int const output = 9;
    Solution solution;
    int const ret =
        solution.MinCost(houses, cost, num_houses, num_colors, target);
    /*Paint houses of this way [1,2,2,1,1]
    This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
    Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.*/
    EXPECT_EQ(ret, output);
}

TEST(PaintHouseIii, t2) {
    vector<int> houses = {0, 2, 1, 2, 0};
    vector<vector<int>> cost = {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}};
    int const num_houses = 5, num_colors = 2, target = 3;
    int const output = 11;
    Solution solution;
    int const ret =
        solution.MinCost(houses, cost, num_houses, num_colors, target);
    /*Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
    This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
    Cost of paint the first and last house (10 + 1) = 11.*/
    EXPECT_EQ(ret, output);
}

TEST(PaintHouseIii, t3) {
    vector<int> houses = {3, 1, 2, 3};
    vector<vector<int>> cost = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int const num_houses = 4, num_colors = 3, target = 3;
    int const output = -1;
    Solution solution;
    int const ret =
        solution.MinCost(houses, cost, num_houses, num_colors, target);
    /* Houses are already painted with a total of 4 neighborhoods
    [{3},{1},{2},{3}] different of target = 3. */
    EXPECT_EQ(ret, output);
}
}  // namespace
