/*
Given two non-negative integers num1 and num2 represented as strings, return the
product of num1 and num2, also represented as a string.

Note: You must not use any built-in BigInteger library or convert the inputs to
integer directly.
*/

#include <string>
#include <vector>
using namespace std;

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string num1 = "2", num2 = "3";
    std::string expected = "6";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::string num1 = "123", num2 = "456";
    std::string expected = "56088";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(t0, t3) {
    std::string num1 = "123456789", num2 = "987654321";
    std::string expected = "121932631112635269";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}
TEST(t0, t4) {
    std::string num1 = "498828660196", num2 = "840477629533";
    std::string expected = "419254329864656431168468";

    Solution s;
    auto ret = s.Multiply(num1, num2);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
