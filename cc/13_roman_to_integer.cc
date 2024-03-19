// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
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
    int RomanToInt(std::string s) {
        int i = 0;
        int sum = 0;
        const int len = s.length();
        int current, next;

        for (i = 0; i < len; i++) {
            current = Basic(s[i]);
            if (i == len - 1)  // last element
            {
                sum += current;
                break;
            }
            next = Basic(s[i + 1]);
            //  cout << "current = " << current << " next = " << next << endl;

            if (current > next) {
                sum += current;
            } else if (current == next) {
                sum += current;
            } else  // left smaller than right:
            {
                sum += (next - current);
                i++;
            }
        }
        return sum;
    }

    int Basic(char c) {
        switch (c) {
            case 'I':
                return 1;
                break;
            case 'V':
                return 5;
                break;
            case 'X':
                return 10;
                break;
            case 'L':
                return 50;
                break;
            case 'C':
                return 100;
                break;
            case 'D':
                return 500;
                break;
            case 'M':
                return 1000;
                break;
            default:
                return 0;
                break;
        }
    }
};

TEST(roman_to_integer, t1) {
    Solution s;

    const std::string input = "III";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 3);
}

TEST(roman_to_integer, t2) {
    Solution s;
    const std::string input = "LVIII";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 58);
}

TEST(roman_to_integer, t3) {
    Solution s;
    const std::string input = "MCMXCIV";
    const int ret = s.RomanToInt(input);
    EXPECT_EQ(ret, 1994);
}

}  // namespace
