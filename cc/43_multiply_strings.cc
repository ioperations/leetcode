// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given two non-negative integers num1 and num2 represented as strings, return the
product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to
integer directly.
*/

#include <stddef.h>

#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    std::string ToStr(int num) {
        std::string ret = "";

        while (num) {
            int last_bit = num % 10;
            num = num / 10;
            ret = std::to_string('0' + last_bit) + ret;
        }
        return ret;
    }
    string Multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        vector<int> num(num1.size() + num2.size(), 0);
        for (int i = num1.size() - 1; i >= 0; i--) {
            for (int j = num2.size() - 1; j >= 0; j--) {
                num[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
                num[i + j] += num[i + j + 1] / 10;
                num[i + j + 1] %= 10;
            }
        }

        size_t i = 0;
        while (i < num.size() && num[i] == 0) ++i;
        string res = "";
        while (i < num.size()) {
            res.push_back(num[i] + '0');
            i++;
        }
        return res;
    }
};

TEST(multiply_strings, t1) {
    std::string num1 = "2", num2 = "3";
    std::string expected = "6";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

TEST(multiply_strings, t2) {
    std::string num1 = "123", num2 = "456";
    std::string expected = "56088";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(multiply_strings, t3) {
    std::string num1 = "123456789", num2 = "987654321";
    std::string expected = "121932631112635269";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(multiply_strings, t4) {
    std::string num1 = "498828660196", num2 = "840477629533";
    std::string expected = "419254329864656431168468";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

}  // namespace
