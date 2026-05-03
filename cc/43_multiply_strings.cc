// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given two non-negative integers num1 and num2 represented as strings, return the
product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to
integer directly.
*/

#include <cstddef>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    [[nodiscard]]
    std::string ToStr(int num) const {
        std::string ret = "";

        while (num) {
            int const last_bit = num % 10;
            num = num / 10;
            ret = std::to_string('0' + last_bit) + ret;
        }
        return ret;
    }
    [[nodiscard]]
    std::string Multiply(std::string num1, std::string num2) const {
        if (num1 == "0" || num2 == "0") {
            return "0";
        }
        vector<int> num(num1.size() + num2.size(), 0);
        for (int i = static_cast<int>(num1.size()) - 1; i >= 0; i--) {
            for (int j = static_cast<int>(num2.size()) - 1; j >= 0; j--) {
                num.at(i + j + 1) += (num1.at(i) - '0') * (num2.at(j) - '0');
                num.at(i + j) += num.at(i + j + 1) / 10;
                num.at(i + j + 1) %= 10;
            }
        }

        size_t i = 0;
        while (i < static_cast<int>(num.size()) && num.at(i) == 0) ++i;
        string res = "";
        while (i < static_cast<int>(num.size())) {
            res.push_back(static_cast<char>(num.at(i) + '0'));
            i++;
        }
        return res;
    }
};

TEST(multiplyV, t1) {
    std::string const num1 = "2", num2 = "3";
    std::string const expected = "6";

    Solution const s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

TEST(multiplyV, t2) {
    std::string const num1 = "123", num2 = "456";
    std::string const expected = "56088";

    Solution const s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(multiplyV, t3) {
    std::string const num1 = "123456789", num2 = "987654321";
    std::string const expected = "121932631112635269";

    Solution const s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(multiplyV, t4) {
    std::string const num1 = "498828660196", num2 = "840477629533";
    std::string const expected = "419254329864656431168468";

    Solution const s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

}  // namespace
