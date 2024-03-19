// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Roman numerals are represented by seven different symbols: I, V, X, L, C, D
and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
For example, 2 is written as II in Roman numeral, just two one's added together.
12 is written as XII, which is simply X + II. The number 27 is written as XXVII,
which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right.
However, the numeral for four is not IIII. Instead, the number four is written
as IV. Because the one is before the five we subtract it making four. The same
principle applies to the number nine, which is written as IX. There are six
instances where subtraction is used:

I can be placed before V (5) and X (10) to make 4 and 9.
X can be placed before L (50) and C (100) to make 40 and 90.
C can be placed before D (500) and M (1000) to make 400 and 900.
Given an integer, convert it to a roman numeral.


 */

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
    string IntToRoman(int num) {
        int const normal[] = {1000, 900, 500, 400, 100, 90, 50,
                              40,   10,  9,   5,   4,   1};
        int const size = sizeof(normal) / sizeof(int);
        string const roman[] = {"M",  "CM", "D",  "CD", "C",  "XC", "L",
                                "XL", "X",  "IX", "V",  "IV", "I"};
        string res;
        for (int i = 0; i < size; i++) {
            while (num >= normal[i]) {
                res.append(roman[i]);
                num -= normal[i];
            }
        }
        return res;
    }
};

TEST(integer_to_roman, t1) {
    const int num = 3;
    const string output = "III";
    // Explanation: 3 is represented as 3 ones.
    Solution sl;
    const string ret = sl.IntToRoman(num);
    EXPECT_EQ(ret, output);
}

TEST(integer_to_roman, t2) {
    const int num = 58;
    const string output = "LVIII";
    // Explanation: L = 50, V = 5, III = 3.";
    Solution sl;
    const string ret = sl.IntToRoman(num);
    EXPECT_EQ(ret, output);
}

TEST(integer_to_roman, t3) {
    const int num = 1994;
    const string output = "MCMXCIV";
    // Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
    Solution sl;
    const string ret = sl.IntToRoman(num);
    EXPECT_EQ(ret, output);
}

}  // namespace
