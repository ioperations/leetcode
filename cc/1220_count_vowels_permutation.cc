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

TEST(count_vowels_permutation, t1) {
    int n = 1;
    int output = 5;

    // Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(count_vowels_permutation, t2) {
    int n = 2;
    int output = 10;

    // All possible strings are: "ae", "ea", "ei", "ia", "ie", "io", "iu", "oi",
    // "ou" and "ua".
    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}

TEST(count_vowels_permutation, t3) {
    int n = 5;
    int output = 68;

    Solution sl;
    int ret = sl.CountVowelPermutation(n);
    EXPECT_EQ(ret, output);
}
}  // namespace
