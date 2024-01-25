// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, return the least number of perfect square numbers that sum
to n.

A perfect square is an integer that is the square of an integer; in other words,
it is the product of some integer with itself. For example, 1, 4, 9, and 16 are
perfect squares while 3 and 11 are not.*/

#include <algorithm>
#include <climits>
#include <functional>
#include <vector>

class Solution {
   public:
    int NumSquares(int n) {
        // vector for updating the dp array/values
        std::vector<int> dp(n + 1, INT_MAX);
        // base case
        dp[0] = 0;
        int count = 1;
        while (count * count <= n) {
            int sq = count * count;
            for (int i = sq; i < n + 1; i++) {
                dp[i] = std::min(dp[i - sq] + 1, dp[i]);
            }
            count++;
        }
        return dp[n];
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 12;
    int const output = 3;
    // Explanation: 12 = 4 + 4 + 4.
    Solution sl;
    int const ret = sl.NumSquares(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 13;
    int const output = 2;
    // Explanation: 12 = 4 + 9
    Solution sl;
    int const ret = sl.NumSquares(n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
