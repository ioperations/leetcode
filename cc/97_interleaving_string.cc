// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1
and s2.

An interleaving of two strings s and t is a configuration where they are divided
into non-empty substrings such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3
+ s3 + ... Note: a + b is the concatenation of strings a and b.
*/

#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool Helper(const string& s1, const string& s2, const string& s3) {
        int const l1 = static_cast<int>(s1.length()), l2 = static_cast<int>(s2.length());
        vector<int> q1, q2;  // queue;
        vector<vector<int>> table(s1.length() + 1,
                                  vector<int>(s2.length() + 1, false));
        char c1 = 0, c2 = 0, c3 = 0;

        q1.push_back(0);
        q2.push_back(0);
        table[0][0] = true;

        while (q1.size()) {
            int const tmp1 = q1.at(0), tmp2 = q2.at(0);
            if (tmp1 == l1 && tmp2 == l2) return true;

            if (tmp1 == l1) {
                c1 = '0';
            } else {
                c1 = s1.at(tmp1);
            }
            if (tmp2 == l2) {
                c2 = '0';
            } else {
                c2 = s2.at(tmp2);
            }
            c3 = s3.at(tmp1 + tmp2);

            q1.erase(q1.begin());
            q2.erase(q2.begin());
            table[tmp1][tmp2] = false;

            if (c1 == c3) {
                if (table[tmp1 + 1][tmp2] == false) {
                    q1.push_back(tmp1 + 1);
                    q2.push_back(tmp2);
                    table[tmp1 + 1][tmp2] = true;
                }
            }
            if (c2 == c3) {
                if (table[tmp1][tmp2 + 1] == false) {
                    q1.push_back(tmp1);
                    q2.push_back(tmp2 + 1);
                    table[tmp1][tmp2 + 1] = true;
                }
            }
        }
        return false;
    }

    bool IsInterleave(const string& s1, const string& s2, const string& s3) {
        if (s1.length() + s2.length() != s3.length()) return false;
        if (s1.length() == 0) return true;
        return Helper(s1, s2, s3);
    }

    bool IsInterleaveV1(const string& s1, const string& s2, const string& s3) {
        if (s1 == "") return s2 == s3;
        if (s2 == "") return s1 == s3;
        int const n1 = static_cast<int>(s1.size()), n2 = static_cast<int>(s2.size()), n3 = static_cast<int>(s3.size());
        if (n1 + n2 != n3) return false;
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1));

        for (int i = 0; i <= n1; i++) {
            for (int j = 0; j <= n2; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = true;
                } else if (i == 0) {
                    dp[i][j] = dp[i][j - 1] && s2.at(j - 1) == s3.at(i + j - 1);
                } else if (j == 0) {
                    dp[i][j] = dp[i - 1][j] && s1.at(i - 1) == s3.at(i + j - 1);
                } else {
                    dp[i][j] = ((dp[i - 1][j] && s1.at(i - 1) == s3.at(i + j - 1)) ||
                                (dp[i][j - 1] && s2.at(j - 1) == s3.at(i + j - 1)));
                }
            }
        }
        return dp[n1][n2];
    }
};

TEST(interleavingV, t1) {
    string string1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
    bool const output = true;

    Solution sl;
    bool ret = sl.IsInterleave(string1, s2, s3);
    EXPECT_EQ(ret, output);

    ret = sl.IsInterleaveV1(string1, s2, s3);
    EXPECT_EQ(ret, output);
}

TEST(interleavingV, t2) {
    string string1 = "", s2 = "", s3 = "";
    bool const output = true;

    Solution sl;
    bool ret = sl.IsInterleave(string1, s2, s3);
    EXPECT_EQ(ret, output);
    ret = sl.IsInterleaveV1(string1, s2, s3);
    EXPECT_EQ(ret, output);
}

}  // namespace
