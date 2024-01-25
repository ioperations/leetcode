// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two strings word1 and word2, return the minimum number of steps required
to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

*/

#include <string>
#include <vector>

using namespace std;

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string word1 = "sea", word2 = "eat";
    int output = 2;
    // Explanation: You need one step to make "sea" to "ea" and another step to
    // make "eat" to "ea".

    Solution sl;
    int ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string word1 = "leetcode", word2 = "etco";
    int output = 4;

    Solution sl;
    int ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
