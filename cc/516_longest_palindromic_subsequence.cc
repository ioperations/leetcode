// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s, find the longest palindromic subsequence's length in s.

A subsequence is a sequence that can be derived from another sequence by
deleting some or no elements without changing the order of the remaining
elements.
*/
#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    int Lcs(string string1, string string2) {
        int n1 = string1.length();
        int n2 = string2.length();
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (string1[i] == string2[j])
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                else
                    dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
            }
        }
        return dp[n1][n2];
    }
    int LongestPalindromeSubseq(string s) {
        string k = s;
        reverse(s.begin(), s.end());
        return Lcs(s, k);
    }
};



TEST(t0, t1) {
    string s = "bbbab";
    int output = 4;
    // Explanation: One possible longest palindromic subsequence is "bbbb".
    Solution sl;
    int ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "cbbd";
    int output = 2;
    // One possible longest palindromic subsequence is "bb".
    Solution sl;
    int ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

}
