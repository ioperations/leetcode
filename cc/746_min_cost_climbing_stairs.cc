// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an integer array cost where cost[i] is the cost of ith step on a
staircase. Once you pay the cost, you can either climb one or two steps.

You can either start from the step with index 0, or the step with index 1.

Return the minimum cost to reach the top of the floor.
*/

#include <functional>
#include <map>
#include <vector>
#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int MinCostClimbingStairs(vector<int> &cost) {
        // pass
        if ((int)cost.size() == 0) {
            return 0;
        }
        if ((int)cost.size() == 1) {
            return cost[0];
        }

        std::map<int, int> cache;

        function<int(int)> fun = [&](int now) -> int {
            if (now == (int)(cost.size() - 1)) {
                return cost.back();
            }
            if (now >= (int)(cost.size())) {
                return 0;
            }

            if (cache.count(now)) {
                return cache[now];
            }

            cache[now] = cost[now] + min(fun(now + 1), fun(now + 2));
            return cache[now];
        };

        return min(fun(0), fun(1));
    }
};



TEST(t0, t1) {
    std::vector<int> v{10, 15, 20};

    int expected = 15;
    /*
        You will start at index 1.
        - Pay 15 and climb two steps to reach the top.
        The total cost is 15.
    */

    Solution sl;
    int ret = sl.MinCostClimbingStairs(v);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::vector<int> v{1, 100, 1, 1, 1, 100, 1, 1, 100, 1};

    int expected = 6;
    /*
        You will start at index 0.
        - Pay 1 and climb two steps to reach index 2.
        - Pay 1 and climb two steps to reach index 4.
        - Pay 1 and climb two steps to reach index 6.
        - Pay 1 and climb one step to reach index 7.
        - Pay 1 and climb two steps to reach index 9.
        - Pay 1 and climb one step to reach the top .
    */
    Solution sl;
    int ret = sl.MinCostClimbingStairs(v);
    EXPECT_EQ(ret, expected);
}

}
