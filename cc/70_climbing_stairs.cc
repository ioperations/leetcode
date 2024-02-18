// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?
*/

#include <functional>
#include <map>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;


namespace {
class Solution {
   public:
    int ClimbStairs(int n) {
        vector<int> dp(n + 1);
        dp[0] = dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

class SolutionV2 {
   public:
    int ClimbStairs(int n) {
        // 到达第n级台阶之后后面有多少种爬楼梯的方法
        // 1 <= n <= 45
        if (n == 1) {
            return 1;
        }
        std::map<int, int> cache;
        function<int(int)> fun = [&](int i) -> int {
            if (i >= n) {
                return 1;
            }
            if (i == n - 1) {
                return 1;
            }
            if (i == n - 2) {
                return 2;
            }
            if (cache.count(i)) {
                return cache[i];
            }

            cache[i] = fun(i + 1) + fun(i + 2);
            return cache[i];
        };

        return fun(1) + fun(2);
    }
};



TEST(climbing_stairs, t1) {
    Solution sl;
    int ret = sl.ClimbStairs(2);

    /*
        There are two ways to climb to the top.
        1. 1 step + 1 step
        2. 2 steps
    */
    EXPECT_EQ(ret, 2);
}

TEST(climbing_stairs_v2, t1) {
    SolutionV2 sl;
    int ret = sl.ClimbStairs(2);

    /*
        There are two ways to climb to the top.
        1. 1 step + 1 step
        2. 2 steps
    */
    EXPECT_EQ(ret, 2);
}

TEST(climbing_stairs, t2) {
    Solution sl;
    int ret = sl.ClimbStairs(3);

    /*
        There are three ways to climb to the top.
        1. 1 step + 1 step + 1 step
        2. 1 step + 2 steps
        3. 2 steps + 1 step
    */
    EXPECT_EQ(ret, 3);
}

TEST(climbing_stairs_v2, t2) {
    SolutionV2 sl;
    int ret = sl.ClimbStairs(3);

    /*
        There are three ways to climb to the top.
        1. 1 step + 1 step + 1 step
        2. 1 step + 2 steps
        3. 2 steps + 1 step
    */
    EXPECT_EQ(ret, 3);
}

}  // namespace
