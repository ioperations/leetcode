// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Write a function that reverses a string. The input string is given as an array
of characters s.

You must do this by modifying the input array in-place with O(1) extra memory.

*/

#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    void ReverseString(std::vector<char>& s) {
        // pass
        std::reverse(s.begin(), s.end());
    }

    void ReverseStringV2(std::vector<char>& s) {
        std::stack<char> sk;
        for (auto& ptr : s) {
            sk.push(ptr);
        }

        int i = 0;
        while (sk.size()) {
            s[i] = sk.top();
            sk.pop();
            i++;
        }
    }
};

TEST(reverse_string, t1) {
    std::vector<char> s = {'h', 'e', 'l', 'l', 'o'};
    std::vector<char> const output = {'o', 'l', 'l', 'e', 'h'

    };
    Solution sl;
    sl.ReverseString(s);

    EXPECT_EQ(s, output);

    sl.ReverseString(s);

    sl.ReverseStringV2(s);
    EXPECT_EQ(s, output);
}
TEST(reverse_string, t2) {
    std::vector<char> s = {'H', 'a', 'n', 'n', 'a', 'h'};
    std::vector<char> const output = {'h', 'a', 'n', 'n', 'a', 'H'};
    Solution sl;
    sl.ReverseString(s);

    EXPECT_EQ(s, output);
}
}  // namespace
