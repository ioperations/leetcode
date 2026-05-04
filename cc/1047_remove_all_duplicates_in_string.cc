// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given a string s consisting of lowercase English letters. A duplicate
removal consists of choosing two adjacent and equal letters and removing them.

We repeatedly make duplicate removals on s until we no longer can.

Return the final string after all such duplicate removals have been made. It can
be proven that the answer is unique.

 */

#include <algorithm>
#include <string>
#include <utility>

using namespace std;
#include <stack>

#include "gtest/gtest.h"
namespace {
class Solution {
   public:
    [[nodiscard]] string RemoveDuplicates(const string& s, int k = 2) const {
        int const n = static_cast<int>(s.size());
        if (n < k) return s;

        stack<pair<char, int>> stk;
        for (int i = 0; i < n; ++i) {
          if (stk.empty() || stk.top().first != s.at(i)) {
            stk.emplace(s.at(i), 1);
          } else {
            auto const prev = stk.top();
            stk.pop();
            stk.emplace(s.at(i), prev.second + 1);
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

TEST(RemoveAllDuplicatesInString, t1) {
    std::string const s = "abbaca";
    string const expected = "ca";
    // Explanation: For example, in "abbaca" we could remove "bb" since the
    // letters are adjacent and equal, and this is the only possible move.  The
    // result of this move is that the string is "aaca", of which only "aa" is
    // possible, so the final string is "ca".

    Solution const sl;
    auto ret = sl.RemoveDuplicates(s);
    EXPECT_EQ(ret, expected);
}

TEST(RemoveAllDuplicatesInString, t2) {
    std::string const s = "azxxzy";
    string const expected = "ay";
    // Explanation: For example, in "abbaca" we could remove "bb" since the
    // letters are adjacent and equal, and this is the only possible move.  The
    // result of this move is that the string is "aaca", of which only "aa" is
    // possible, so the final string is "ca".

    Solution const sl;
    auto ret = sl.RemoveDuplicates(s);
    EXPECT_EQ(ret, expected);
}

}  // namespace
