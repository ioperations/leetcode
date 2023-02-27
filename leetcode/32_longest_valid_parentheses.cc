/*
Given a string containing just the characters '(' and ')', find the length of
the longest valid (well-formed) parentheses substring.
*/

#include <stack>
#include <string>
using namespace std;
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "(()";
    int output = 2;
    // Explanation: The longest valid parentheses substring is "()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = ")()())";
    int output = 4;
    // Explanation: The longest valid parentheses substring is "()()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}
TEST(t0, t3) {
    string s = "";
    int output = 0;

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
