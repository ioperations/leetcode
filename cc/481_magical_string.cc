// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A magical string s consists of only '1' and '2' and obeys the following rules:

The string s is magical because concatenating the number of contiguous
occurrences of characters '1' and '2' generates the string s itself. The first
few elements of s is s = "1221121221221121122……". If we group the consecutive
1's and 2's in s, it will be "1 22 11 2 1 22 1 22 11 2 11 22 ......" and the
occurrences of 1's or 2's in each group are "1 2 2 1 1 2 1 2 2 1 2 2 ......".
You can see that the occurrence sequence is s itself.

Given an integer n, return the number of 1's in the first n number in the
magical string s.
*/

#include <string>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    int MagicalString(int n) {
        // pass

        std::string magic_string = "1221121221221121122";
        char last = '2';
        int str_len = magic_string.size();
        // pass
        int i = 12;

        while (str_len < n) {
            int build_count = magic_string[i] - '0';
            i++;
            last = last == '2' ? '1' : '2';
            BuildCountBuild(magic_string, last, build_count);
            str_len += build_count;
        }
        return CountNumber(magic_string, n);
    }

    void BuildCountBuild(std::string &s, char charac, int num) {
        for (int i = 0; i < num; i++) {
            s += charac;
        }
    }

    int CountNumber(const std::string &s, int n) {
        int count = 0;
        for (int i = 0; i < n && i < (int)s.size(); i++) {
            if (s[i] == '1') {
                count++;
            }
        }
        return count;
    }
};



TEST(magical_string, t1) {
    int n = 6;
    int expected = 3;
    // Explanation: The first 6 elements of magical string s is "122112" and it
    // contains three 1's, so return 3.

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}

TEST(magical_string, t2) {
    int n = 1;
    int expected = 1;

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}

TEST(magical_string, t3) {
    int n = 36;
    int expected = 18;
    // Explanation: The first 6 elements of magical string s is "122112" and it
    // contains three 1's, so return 3.

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}

TEST(magical_string, t4) {
    int n = 37;
    int expected = 19;
    // Explanation: The first 6 elements of magical string s is "122112" and it
    // contains three 1's, so return 3.

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}
TEST(magical_string, t5) {
    int n = 38;
    int expected = 19;
    // Explanation: The first 6 elements of magical string s is "122112" and it
    // contains three 1's, so return 3.

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}

TEST(magical_string, t6) {
    int n = 9758;
    int expected = 4874;
    // Explanation: The first 6 elements of magical string s is "122112" and it
    // contains three 1's, so return 3.

    Solution s;
    int ret = s.MagicalString(n);
    EXPECT_EQ(ret, expected);
}

} // namespace
