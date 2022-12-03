
/*

Given a string containing just the characters '(' and ')', find the length of
the longest valid (well-formed) parentheses substring.

*/
#include <string>
using namespace std;
class Solution {
   public:
    int LongestValidParentheses(string s) {
        // pass
        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string s = "(()";
    int expected = 2;
    // Explanation: The longest valid parentheses substring is "()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::string s = ")()())";
    int expected = 4;
    // The longest valid parentheses substring is "()()".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t3) {
    std::string s = "";
    int expected = 0;
    // The longest valid parentheses substring is "".

    Solution sl;
    int ret = sl.LongestValidParentheses(s);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

