// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*
Given an integer columnNumber, return its corresponding column title as it
appears in an Excel sheet.

*/

#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
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

TEST(excel_sheet_column_title, t1) {
    Solution s;
    auto ret = s.ConvertToTitle(1);
    EXPECT_EQ(ret, "A");
}

TEST(excel_sheet_column_title, t2) {
    Solution s;
    auto ret = s.ConvertToTitle(26);
    EXPECT_EQ(ret, "Z");
}

TEST(excel_sheet_column_title, t3) {
    Solution s;
    auto ret = s.ConvertToTitle(28);
    EXPECT_EQ(ret, "AB");
}

TEST(excel_sheet_column_title, t4) {
    Solution s;
    auto ret = s.ConvertToTitle(27);
    EXPECT_EQ(ret, "AA");
}

TEST(excel_sheet_column_title, t5) {
    Solution s;
    auto ret = s.ConvertToTitle(701);
    EXPECT_EQ(ret, "ZY");
}

}  // namespace