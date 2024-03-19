// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two strings word1 and word2, return the minimum number of steps required
to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

*/

#include <string>
#include <vector>
#include <algorithm>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace { 
class Solution {
   public:
    int Lcs(string s, string t) {
        int n = s.length();
        int m = t.length();

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 0;
                } else {
                    if (s[i - 1] == t[j - 1]) {
                        dp[i][j] = 1 + dp[i - 1][j - 1];
                    } else {
                        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                    }
                }
            }
        }
        return dp[n][m];
    }

    int MinDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        return n + m - 2 * Lcs(word1, word2);
    }
};



TEST(delete_operation_for_two_strings, t1) {
    string word1 = "sea", word2 = "eat";
    int output = 2;
    // Explanation: You need one step to make "sea" to "ea" and another step to
    // make "eat" to "ea".

    Solution sl;
    int ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(delete_operation_for_two_strings, t2) {
    string word1 = "leetcode", word2 = "etco";
    int output = 4;

    Solution sl;
    int ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

}
