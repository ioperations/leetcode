// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching
with support for '?' and '*' where:

'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
*/
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IsMatch(string s, string p) {
        // 0 <= s.length, p.length <= 2000
        // s contains only lowercase English letters.
        // p contains only lowercase English letters, '?' or '*'.
        int m = p.length();
        int n = s.length();

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[0][0] = true;

        int st = 0;
        while (st < m && p[st] == '*') dp[++st][0] = true;

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p[i - 1] == s[j - 1] || p[i - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if (p[i - 1] == '*')
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                else
                    dp[i][j] = false;
            }
        }

        // for(int i = 0; i <= m; i++) {
        //     for(int j = 0; j <= n; j++)
        //         cout << dp[i][j] << " ";
        //     cout << endl;
        // }

        return dp[m][n];
    }
};

TEST(wildcard_matching, t1) {
    std::string s = "aa", p = "a";
    Solution sl;
    bool ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, false);
}

TEST(wildcard_matching, t2) {
    std::string s = "aa", p = "*";
    Solution sl;
    bool ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, true);
}

TEST(wildcard_matching, t3) {
    std::string s = "cb", p = "?a";
    Solution sl;
    bool ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, false);
}

}  // namespace
