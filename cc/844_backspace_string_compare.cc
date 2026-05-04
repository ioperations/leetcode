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
    [[nodiscard]] bool BackspaceCompare(string s, string t) const {
        return Real(s) == Real(t);
    }

    [[nodiscard]] std::string Real(std::string s) const {
        std::string ret;
        std::stack<char> stack;
        for (auto& ptr : s) {
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

TEST(BackspaceStringCompare, t1) {
    std::string const s = "ab#c", t = "ad#c";
    bool const expected = true;

    Solution const sl;
    bool const ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}
TEST(BackspaceStringCompare, t2) {
    std::string const s = "ab##", t = "c#d#";
    bool const expected = true;

    Solution const sl;
    bool const ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

TEST(BackspaceStringCompare, t3) {
    std::string const s = "a#c", t = "b";
    bool const expected = false;

    Solution const sl;
    bool const ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

}  // namespace
