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

#include <limits.h>

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   private:
    vector<vector<vector<int>>> mem;
    int Solve(vector<int> &houses, vector<vector<int>> &cost, int target,
              int index, int p) {
        int m = houses.size(), n = cost[0].size();
        if (index == m) {
            if (target == 0) {
                return 0;
            }
            return INT_MAX;
        }
        if (target < 0) {
            return INT_MAX;
        }
        if (mem[index][p][target] != -1) {
            return mem[index][p][target];
        }
        if (houses[index] == 0) {
            int min_cost = INT_MAX;
            for (int color = 1; color <= n; color++) {
                int ans;
                if (color == p) {
                    ans = Solve(houses, cost, target, index + 1, p);
                } else {
                    ans = Solve(houses, cost, target - 1, index + 1, color);
                }
                if (ans != INT_MAX) {
                    ans += cost[index][color - 1];
                }
                min_cost = min(min_cost, ans);
            }
            return mem[index][p][target] = min_cost;
        }
        if (houses[index] == p) {
            return mem[index][p][target] =
                       Solve(houses, cost, target, index + 1, p);
        }
        return mem[index][p][target] =
                   Solve(houses, cost, target - 1, index + 1, houses[index]);
    }

   public:
    int MinCost(vector<int> &houses, vector<vector<int>> &cost, int m, int n,
                int target) {
        mem = vector<vector<vector<int>>>(
            m, vector<vector<int>>(n + 1, vector<int>(target + 1, -1)));
        int ans = Solve(houses, cost, target, 0, 0);
        return ans == INT_MAX ? -1 : ans;
    }
};

TEST(paint_house_iii, t1) {
    vector<int> houses = {0, 0, 0, 0, 0};
    vector<vector<int>> cost = {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}};
    int m = 5, n = 2, target = 3;
    int output = 9;
    Solution sl;
    int ret = sl.MinCost(houses, cost, m, n, target);
    /*Paint houses of this way [1,2,2,1,1]
    This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
    Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.*/
    EXPECT_EQ(ret, output);
}

TEST(paint_house_iii, t2) {
    vector<int> houses = {0, 2, 1, 2, 0};
    vector<vector<int>> cost = {{1, 10}, {10, 1}, {10, 1}, {1, 10}, {5, 1}};
    int m = 5, n = 2, target = 3;
    int output = 11;
    Solution sl;
    int ret = sl.MinCost(houses, cost, m, n, target);
    /*Some houses are already painted, Paint the houses of this way [2,2,1,2,2]
    This array contains target = 3 neighborhoods, [{2,2}, {1}, {2,2}].
    Cost of paint the first and last house (10 + 1) = 11.*/
    EXPECT_EQ(ret, output);
}

TEST(paint_house_iii, t3) {
    vector<int> houses = {3, 1, 2, 3};
    vector<vector<int>> cost = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int m = 4, n = 3, target = 3;
    int output = -1;
    Solution sl;
    int ret = sl.MinCost(houses, cost, m, n, target);
    /* Houses are already painted with a total of 4 neighborhoods
    [{3},{1},{2},{3}] different of target = 3. */
    EXPECT_EQ(ret, output);
}
}  // namespace
