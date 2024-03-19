// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*For an integer array nums, an inverse pair is a pair of integers [i, j] where
0 <= i < j < nums.length and nums[i] > nums[j].

Given two integers n and k, return the number of different arrays consist of
numbers from 1 to n such that there are exactly k inverse pairs. Since the
answer can be huge, return it modulo 109 + 7.*/
#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int KInversePairs(int n, int k) {
        // x x 1 2 3 x x
        //       ^
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        const int mod = 1e+9 + 7;
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

TEST(k_inverse_pairs_array, t1) {
    const int n = 3;
    const int k = 0;
    const int output = 1;
    Solution sl;
    const int ret = sl.KInversePairs(n, k);
    // Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly
    // 0 inverse pairs.
    EXPECT_EQ(ret, output);
}

TEST(k_inverse_pairs_array, t2) {
    const int n = 3, k = 1;
    const int output = 2;
    // Explanation: The array [1,3,2] and [2,1,3] have exactly 1 inverse pair.
    Solution sl;
    const int ret = sl.KInversePairs(n, k);
    EXPECT_EQ(ret, output);
}

} // namespace
