// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

Given two strings s and t, return true if they are equal when both are typed
into empty text editors. '#' means a backspace character.

Note that after backspacing an empty text, the text will continue empty.
*/

#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    bool BackspaceCompare(string s, string t) {
        // pass
        return Real(s) == Real(t);
    }

    std::string Real(std::string s) {
        std::string ret;
        std::stack<char> stack;
        for (auto &ptr : s) {
            if (ptr == '#') {
                if (stack.size()) {
                    stack.pop();
                }
            } else {
                stack.push(ptr);
            }
        }

        while (stack.size()) {
            ret += stack.top();
            stack.pop();
        }
        // reverse(ret.begin(), ret.end());

        return ret;
    }
};



TEST(t0, t1) {
    std::string s = "ab#c", t = "ad#c";
    bool expected = true;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}
TEST(t0, t2) {
    std::string s = "ab##", t = "c#d#";
    bool expected = true;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

TEST(t0, t3) {
    std::string s = "a#c", t = "b";
    bool expected = false;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

}
