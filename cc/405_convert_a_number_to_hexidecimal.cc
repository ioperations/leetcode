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

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    string ToHex(int num) {
        // pass
        if (num == 0) return "0";

        string result;
        unsigned n = num;
        while (n) {
            auto rem = n % 16;
            char value = rem >= 10 ? (rem - 10) + 'a' : rem + '0';
            result.push_back(value);
            n /= 16;
        }
        reverse(result.begin(), result.end());
        return result;
    }
};



TEST(convert_a_number_to_hexidecimal, t1) {
    int num = 26;
    std::string output = "1a";

    Solution s;
    auto ret = s.ToHex(num);
    EXPECT_EQ(ret, output);
}
TEST(convert_a_number_to_hexidecimal, t2) {
    int num = -1;

    std::string output = "ffffffff";

    Solution s;
    auto ret = s.ToHex(num);
    EXPECT_EQ(ret, output);
}
} // namespace
