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
        int const m = static_cast<int>(p.length());
        int const n = static_cast<int>(s.length());

        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp.at(0).at(0) = true;

        int st = 0;
        while (st < m && p.at(st) == '*') { dp.at(++st).at(0) = true; }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (p.at(i - 1) == s.at(j - 1) || p.at(i - 1) == '?') {
                    dp.at(i).at(j) = dp.at(i - 1).at(j - 1);
                } else if (p.at(i - 1) == '*') {
                    dp.at(i).at(j) = dp.at(i).at(j - 1) || dp.at(i - 1).at(j);
                } else {
                    dp.at(i).at(j) = false;
                }
            }
        }

        // for(int i = 0; i <= m; i++) {
        //     for(int j = 0; j <= n; j++)
        //         cout << dp[i][j] << " ";
        //     cout << endl;
        // }

        return dp.at(m).at(n);
    }
};

TEST(wildcardV, t1) {
    std::string s = "aa", p = "a";
    Solution sl;
    bool const ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, false);
}

TEST(wildcardV, t2) {
    std::string s = "aa", p = "*";
    Solution sl;
    bool const ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, true);
}

TEST(wildcardV, t3) {
    std::string s = "cb", p = "?a";
    Solution sl;
    bool const ret = sl.IsMatch(s, p);
    EXPECT_EQ(ret, false);
}

}  // namespace
