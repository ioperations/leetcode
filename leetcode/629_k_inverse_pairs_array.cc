/*For an integer array nums, an inverse pair is a pair of integers [i, j] where
0 <= i < j < nums.length and nums[i] > nums[j].

Given two integers n and k, return the number of different arrays consist of
numbers from 1 to n such that there are exactly k inverse pairs. Since the
answer can be huge, return it modulo 109 + 7.*/
#include <stack>
#include <vector>
using namespace std;

class Solution {
   public:
    int KInversePairs(int n, int k) {
        std::stack<int> stack;

        // x x 1 2 3 x x
        //       ^
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        int mod = 1e+9 + 7;
        dp[1][0] = 1;  // base case and dp[1][1] = 0;
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                // d[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - i];
                dp[i][j] = dp[i - 1][j];
                if (j > 0) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
                if (j >= i)
                    dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + mod) % mod;
            }
        }

        return dp[n][k];
    }

    int KInversePairsV1(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));

        for (int i = 1; i <= n; i++)
            for (int j = 0; j <= k; j++) {
                // when j = 0(k = 0) then sorted array is the only solution
                if (j == 0)
                    dp[i][j] = 1;
                else
                    for (int p = 0; p <= min(j, i - 1); p++)
                        dp[i][j] = (dp[i][j] + dp[i - 1][j - p]) % 1000000007;
            }
        return dp[n][k];

        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 3;
    int k = 0;
    int output = 1;
    Solution sl;
    int ret = sl.KInversePairs(n, k);
    // Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly
    // 0 inverse pairs.
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 3, k = 1;
    int output = 2;
    // Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
    Solution sl;
    int ret = sl.KInversePairs(n, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
