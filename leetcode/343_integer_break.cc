/*Given an integer n, break it into the sum of k positive integers, where k >=
2, and maximize the product of those integers.

Return the maximum product you can get.
*/
#include <limits.h>

#include <vector>

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 2;
    int output = 1;
    Solution sl;
    int ret = sl.IntegerBreak(n);
    EXPECT_EQ(ret, output);
    // Explanation: 2 = 1 + 1, 1 × 1 = 1.
}

TEST(t0, t2) {
    int n = 10;
    int output = 36;
    Solution sl;
    int ret = sl.IntegerBreak(n);
    // 10 = 3 + 3 + 4, 3 × 3 × 4 = 36.
    EXPECT_EQ(ret, output);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
