// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
*/

#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IsValid(string s) {
        std::stack<char> stack;
        for (auto& ptr : s) {
            if (ptr == '(' || ptr == '[' || ptr == '{') {
                stack.push(ptr);
            } else {
                if (stack.empty()) {
                    return false;
                }
                switch (ptr) {
                    case ']': {
                        if (stack.top() == '[') {
                            stack.pop();
                            break;
                        }
                        return false;
                    }
                    case ')': {
                        if (stack.top() == '(') {
                            stack.pop();
                            break;
                        }
                        return false;
                    }
                    case '}': {
                        if (stack.top() == '{') {
                            stack.pop();
                            break;
                        }
                        return false;
                    }
                    default:
                        break;
                }
            }
        }
        if (stack.size()) return false;
        return true;
    }
};

TEST(valid_parentheses, t1) {
    string const s = "()";
    bool const output = true;

    Solution sl;
    bool const ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_parentheses, t2) {
    string const s = "()[]{}";
    bool const output = true;

    Solution sl;
    bool const ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_parentheses, t3) {
    string const s = "(]";

    bool const output = false;

    Solution sl;
    bool const ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

TEST(valid_parentheses, t4) {
    string const s = "([)]";
    Solution sl;
    bool const ret = sl.IsValid(s);
    EXPECT_EQ(ret, false);
}

TEST(valid_parentheses, t5) {
    string const s = "{[]}";
    Solution sl;
    bool const ret = sl.IsValid(s);
    EXPECT_EQ(ret, true);
}

}  // namespace
