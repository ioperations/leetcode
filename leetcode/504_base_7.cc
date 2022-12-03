/*
Given an integer num, return a string of its base 7 representation.

*/

#include <string>
using namespace std;

class Solution {
   public:
    string ConvertToBase7(int num) {
        std::string ret;
        if (num < 0) {
            return "-" + ConvertToBase7(-num);
        }
        while (num != 0) {
            int left = num % 7;
            ret = std::to_string(left) + ret;
            num = num / 7;
        }
        return ret;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int num = 100;
    string output = "202";
    Solution sl;
    auto ret = sl.ConvertToBase7(num);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int num = -7;
    string output = "-10";
    Solution sl;
    auto ret = sl.ConvertToBase7(num);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
