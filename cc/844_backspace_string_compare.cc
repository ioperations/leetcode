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

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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

TEST(backspace_string_compare, t1) {
    std::string s = "ab#c", t = "ad#c";
    bool expected = true;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}
TEST(backspace_string_compare, t2) {
    std::string s = "ab##", t = "c#d#";
    bool expected = true;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

TEST(backspace_string_compare, t3) {
    std::string s = "a#c", t = "b";
    bool expected = false;

    Solution sl;
    bool ret = sl.BackspaceCompare(s, t);
    EXPECT_EQ(ret, expected);
    // Explanation: Both s and t become "ac".
}

}  // namespace
