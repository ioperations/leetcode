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
    string ConvertToTitle(int column_number) const {
        string str = "";

        while (column_number--) {
            str += 'A' + (column_number % 26);
            column_number /= 26;
        }

        reverse(str.begin(), str.end());
        return str;
    }
};

TEST(ExcelSheetColumnTitle, t1) {
    Solution const s;
    auto ret = s.ConvertToTitle(1);
    EXPECT_EQ("A", ret);
}

TEST(ExcelSheetColumnTitle, t2) {
    Solution const s;
    auto ret = s.ConvertToTitle(26);
    EXPECT_EQ("Z", ret);
}

TEST(ExcelSheetColumnTitle, t3) {
    Solution const s;
    auto ret = s.ConvertToTitle(28);
    EXPECT_EQ("AB", ret);
}

TEST(ExcelSheetColumnTitle, t4) {
    Solution const s;
    auto ret = s.ConvertToTitle(27);
    EXPECT_EQ("AA", ret);
}

TEST(ExcelSheetColumnTitle, t5) {
    Solution const s;
    auto ret = s.ConvertToTitle(701);
    EXPECT_EQ("ZY", ret);
}

}  // namespace