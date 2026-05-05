// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer num, return a string representing its hexadecimal
representation. For negative integers, two’s complement method is used.

All the letters in the answer string should be lowercase characters, and there
should not be any leading zeros in the answer except for the zero itself.

Note: You are not allowed to use any built-in library method to directly solve
this problem.
*/

#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    [[nodiscard]]
    string ToHex(int num) const {
        // pass
        if (num == 0) return "0";

        string result;
        unsigned n = num;
        while (n) {
            auto rem = n % 16;
            char const value = static_cast<char>(rem >= 10 ? (rem - 10) + 'a' : rem + '0');
            result.push_back(value);
            n /= 16;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};

TEST(ConvertANumberToHexidecimal, t1) {
    int const num = 26;
    std::string const output = "1a";

    Solution const s;
    auto ret = s.ToHex(num);
    EXPECT_EQ(ret, output);
}
TEST(ConvertANumberToHexidecimal, t2) {
    int const num = -1;

    std::string const output = "ffffffff";

    Solution const s;
    auto ret = s.ToHex(num);
    EXPECT_EQ(ret, output);
}
}  // namespace
