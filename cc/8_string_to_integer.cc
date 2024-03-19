// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    The algorithm for myAtoi(string s) is as follows:

    Read in and ignore any leading whitespace.
    Check if the next character (if not already at the end of the string) is '-'
or
'+'. Read this character in if it is either. This determines if the final result
is negative or positive respectively. Assume the result is positive if neither
is present.
    Read in next the characters until the next non-digit character or
the end of the input is reached. The rest of the string is ignored.
    Convert these digits into an integer (i.e. "123" -> 123, "0032" -> 32). If
no digits were read, then the integer is 0. Change the sign as necessary (from
step 2). If the integer is out of the 32-bit signed integer range [-231, 231 -
1], then clamp the integer so that it remains in the range. Specifically,
integers less than -231 should be clamped to -231, and integers greater than 231
- 1 should be clamped to 231 - 1. Return the integer as the final result.
 */

#include <string>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    int MyAtoi(std::string s) {
        const bool fill = false;
        int ret = 0;

        bool negative = false;

        for (const auto &char_ref : s) {
            if ('0' <= char_ref && char_ref <= '9') {
                // if (fill) {
                ret = ret * 10 + char_ref - '0';
                //      }
            } else if (!fill && (char_ref == '-' || char_ref == '+')) {
                negative = char_ref == '-' ? true : false;
            } else {
                if (fill) {
                    break;
                }
            }
        }
        return negative ? -ret : ret;
    }
};

TEST(string_to_integer_v2, t2) {
    const std::string s = "42";
    Solution sl;
    const int ret = sl.MyAtoi(s);
    EXPECT_EQ(42, ret);
}

TEST(string_to_integer_v3, t2) {
    const std::string s = "    -42";
    Solution sl;
    const int ret = sl.MyAtoi(s);
    EXPECT_EQ(-42, ret);
}

TEST(string_to_integer_v4, t2) {
    const std::string s = "4193 with words";
    Solution sl;
    const int ret = sl.MyAtoi(s);
    EXPECT_EQ(4193, ret);
}

TEST(t4, t2) {
    const std::string s = "words with 987";
    Solution sl;
    const int ret = sl.MyAtoi(s);
    EXPECT_EQ(987, ret);
}
}  // namespace
