// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, break it into the sum of k positive integers, where k >=
2, and maximize the product of those integers.

Return the maximum product you can get.
*/
#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int IntegerBreak(int n) {
        std::vector<int> dp(n + 1, 0);
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++) {
            int maxi = INT_MIN;
            for (int j = i - 1; j > 0; j--) {
                maxi = std::max(maxi, dp[j] * (i - j));
                maxi = std::max(maxi, (j) * (i - j));
            }
            dp[i] = maxi;
        }
        /*Since, we have to make atleast 2 groups, there are 2 possibilities:
        either multiply every sum to "i" possible i.e., (j) * (i-j) // not in 2
        groups j and i-j are independent or (i-j) * dp[j] // dp[j] contain at
        least 2 groups*/
        return dp[n];
    }
};

TEST(integer_break, t1) {
    int const n = 2;
    int const output = 1;
    Solution sl;
    int const ret = sl.IntegerBreak(n);
    EXPECT_EQ(ret, output);
    // Explanation: 2 = 1 + 1, 1 × 1 = 1.
}

TEST(integer_break, t2) {
    int const n = 10;
    int const output = 36;
    Solution sl;
    int const ret = sl.IntegerBreak(n);
    // 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
    EXPECT_EQ(ret, output);
}
}  // namespace
