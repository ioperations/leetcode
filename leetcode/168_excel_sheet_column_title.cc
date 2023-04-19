// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given an integer columnNumber, return its corresponding column title as it
appears in an Excel sheet.

*/

#include <algorithm>
#include <string>
using namespace std;

class Solution {
   public:
    string ConvertToTitle(int column_number) {
        string str = "";

        while (column_number--) {
            str += 'A' + (column_number % 26);
            column_number /= 26;
        }

        reverse(str.begin(), str.end());
        return str;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    Solution s;
    auto ret = s.ConvertToTitle(1);
    EXPECT_EQ(ret, "A");
}

TEST(t0, t2) {
    Solution s;
    auto ret = s.ConvertToTitle(26);
    EXPECT_EQ(ret, "Z");
}

TEST(t0, t3) {
    Solution s;
    auto ret = s.ConvertToTitle(28);
    EXPECT_EQ(ret, "AB");
}

TEST(t0, t4) {
    Solution s;
    auto ret = s.ConvertToTitle(27);
    EXPECT_EQ(ret, "AA");
}

TEST(t0, t5) {
    Solution s;
    auto ret = s.ConvertToTitle(701);
    EXPECT_EQ(ret, "ZY");
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
