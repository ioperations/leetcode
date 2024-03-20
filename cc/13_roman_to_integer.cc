// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <catch2/catch_test_macros.hpp>
#include <map>
#include <string>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
class Solution {
   public:
    int RomanToInt(std::string s) {
        std::size_t i = 0;
        std::size_t sum = 0;
        const std::size_t len = s.length();
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
        return static_cast<int>(sum);
    }

    int Basic(char c) {
        const static std::map<char, int> v{{'I', 1},   {'V', 5},   {'X', 10},
                                           {'L', 50},  {'C', 100}, {'D', 500},
                                           {'M', 1000}};
        if (v.find(c) != v.end()) {
            return v.at(c);
        }
        return 0;
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
