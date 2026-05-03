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
    int Lcs(std::string string1, std::string string2) {
        int const n1 = static_cast<int>(string1.length());
        int const n2 = static_cast<int>(string2.length());
        vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {
                if (string1.at(i) == string2.at(j)) {
                    dp.at(i + 1).at(j + 1) = dp.at(i).at(j) + 1;
                } else {
                    dp.at(i + 1).at(j + 1) = max(dp.at(i).at(j + 1), dp.at(i + 1).at(j));
                }
            }
        }
        return dp.at(n1).at(n2);
    }
    int LongestPalindromeSubseq(string s) {
        string const k = s;
        reverse(s.begin(), s.end());
        return Lcs(s, k);
    }
};

TEST(LongestPalindromicSubsequence, t1) {
    string const s = "bbbab";
    int const output = 4;
    // Explanation: One possible longest palindromic subsequence is "bbbb".
    Solution sl;
    int const ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

TEST(LongestPalindromicSubsequence, t2) {
    string const s = "cbbd";
    int const output = 2;
    // One possible longest palindromic subsequence is "bb".
    Solution sl;
    int const ret = sl.LongestPalindromeSubseq(s);
    EXPECT_EQ(ret, output);
}

}  // namespace
