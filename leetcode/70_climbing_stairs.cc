/*
You are climbing a staircase. It takes n steps to reach the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you
climb to the top?
*/

#include <functional>
#include <map>
#include <vector>
using namespace std;

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution sl;
    int ret = sl.ClimbStairs(2);

    /*
        There are two ways to climb to the top.
        1. 1 step + 1 step
        2. 2 steps
    */
    EXPECT_EQ(ret, 2);
}

TEST(t1, t1) {
    SolutionV2 sl;
    int ret = sl.ClimbStairs(2);

    /*
        There are two ways to climb to the top.
        1. 1 step + 1 step
        2. 2 steps
    */
    EXPECT_EQ(ret, 2);
}

TEST(t0, t2) {
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

TEST(t1, t2) {
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

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#include <benchmark/benchmark.h>
