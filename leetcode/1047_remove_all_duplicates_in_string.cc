/*
You are given a string s consisting of lowercase English letters. A duplicate
removal consists of choosing two adjacent and equal letters and removing them.

We repeatedly make duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It can
be proven that the answer is unique.

 */

#include <algorithm>
#include <string>
using namespace std;
#include <stack>

class Solution {
   public:
    string RemoveDuplicates(string s, int k = 2) {
        int n = s.size();
        if (n < k) return s;

        stack<pair<char, int>> stk;
        for (int i = 0; i < (int)n; ++i) {
            if (stk.empty() || stk.top().first != s[i])
                stk.push({s[i], 1});
            else {
                auto prev = stk.top();
                stk.pop();
                stk.push({s[i], prev.second + 1});
            }
            if (stk.top().second == k) stk.pop();
        }

        string ans = "";
        while (!stk.empty()) {
            auto cur = stk.top();
            stk.pop();
            while (cur.second--) {
                ans.push_back(cur.first);
            }
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string s = "abbaca";
    string expected = "ca";
    // Explanation: For example, in "abbaca" we could remove "bb" since the
    // letters are adjacent and equal, and this is the only possible move.  The
    // result of this move is that the string is "aaca", of which only "aa" is
    // possible, so the final string is "ca".

    Solution sl;
    auto ret = sl.RemoveDuplicates(s);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::string s = "azxxzy";
    string expected = "ay";
    // Explanation: For example, in "abbaca" we could remove "bb" since the
    // letters are adjacent and equal, and this is the only possible move.  The
    // result of this move is that the string is "aaca", of which only "aa" is
    // possible, so the final string is "ca".

    Solution sl;
    auto ret = sl.RemoveDuplicates(s);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
