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

#include "gtest/gtest.h"

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
  string const s = "(()";
  int const output = 2;
  // Explanation: The longest valid parentheses substring is "()".

  Solution sl;
  int const ret = sl.LongestValidParentheses(s);
  EXPECT_EQ(ret, output);
}

TEST(longest_valid_parentheses, t2) {
  string const s = ")()())";
  int const output = 4;
  // Explanation: The longest valid parentheses substring is "()()".

  Solution sl;
  int const ret = sl.LongestValidParentheses(s);
  EXPECT_EQ(ret, output);
}
TEST(longest_valid_parentheses, t3) {
  string const s = "";
  int const output = 0;

  Solution sl;
  int const ret = sl.LongestValidParentheses(s);
  EXPECT_EQ(ret, output);
}

}  // namespace
