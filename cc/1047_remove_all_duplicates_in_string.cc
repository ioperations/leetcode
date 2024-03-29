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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)
namespace {
class Solution {
   public:
    string RemoveDuplicates(const string &s, int k = 2) {
        std::size_t n = s.size();
        if (n < k) return s;

        stack<pair<char, int>> stk;
        for (std::size_t i = 0; i < n; ++i) {
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

TEST(remove_all_duplicates_in_string, t1) {
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

TEST(remove_all_duplicates_in_string, t2) {
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

}  // namespace
