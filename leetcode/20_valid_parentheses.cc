/*
Given a string s containing just the characters '(', ')', '{', '}', '[' and ']',
determine if the input string is valid.

An input string is valid if:

Open brackets must be closed by the same type of brackets.
Open brackets must be closed in the correct order.
*/

#include <stack>
#include <string>
using namespace std;
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string s = "()";
    bool output = true;

    Solution sl;
    bool ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string s = "()[]{}";
    bool output = true;

    Solution sl;
    bool ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string s = "(]";

    bool output = false;

    Solution sl;
    bool ret = sl.IsValid(s);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
