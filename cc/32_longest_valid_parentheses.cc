// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string containing just the characters '(' and ')', find the length of
the longest valid (well-formed) parentheses substring.
*/

#include <algorithm>
#include <stack>
#include <string>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    int LongestValidParentheses(string s) {
        stack<int> st;
        int maxi = 0;
        st.push(-1);
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == '(') {
                st.push(i);
            } else {
                st.pop();
                if (st.empty()) {
                    st.push(i);
                } else {
                    maxi = max(maxi, i - st.top());
                }
            }
        }
        return maxi;
    }
};

TEST(longest_valid_parentheses, t1) {
    string s = "(()";
    int output = 2;
    // Explanation: The longest valid parentheses substring is "()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}

TEST(longest_valid_parentheses, t2) {
    string s = ")()())";
    int output = 4;
    // Explanation: The longest valid parentheses substring is "()()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}
TEST(longest_valid_parentheses, t3) {
    string s = "";
    int output = 0;

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}

}  // namespace
