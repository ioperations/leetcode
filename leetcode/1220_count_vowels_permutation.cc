// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, your task is to count how many strings of length n can be
formed under the following rules:

Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
Each vowel 'a' may only be followed by an 'e'.
Each vowel 'e' may only be followed by an 'a' or an 'i'.
Each vowel 'i' may not be followed by another 'i'.
Each vowel 'o' may only be followed by an 'i' or a 'u'.
Each vowel 'u' may only be followed by an 'a'.
Since the answer may be too large, return it modulo 10^9 + 7.*/

#include <functional>
#include <map>
#include <vector>
using namespace std;

class Solution {
   public:
    int CountVowelPermutation(int n) {
        int mod = 1e9 + 7;
        vector<vector<int>> dp(n, vector<int>(5, 0));
        int ans = 0;
        for (int i = 0; i < 5; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < n; i++) {
            dp[i][0] = (dp[i - 1][1]) % mod;
            dp[i][1] = (dp[i - 1][0] + dp[i - 1][2]) % mod;
            dp[i][2] =
                (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][3] + dp[i - 1][4]) %
                mod;
            dp[i][3] = (dp[i - 1][2] + dp[i - 1][4]) % mod;
            dp[i][4] = (dp[i - 1][0]) % mod;
        }
        for (auto num : dp[n - 1]) {
            ans = (ans + num) % mod;
        }
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 1;
    int output = 5;

    // Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 2;
    int output = 10;

    // All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi",
    // "ou" and "ua".
    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int n = 5;
    int output = 68;

    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
