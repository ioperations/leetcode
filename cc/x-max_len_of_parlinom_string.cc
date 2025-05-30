// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// given a string
/// find the 最长回文子序列
/// abcba => abcda
/// abcbs => bcb

#include <algorithm>
#include <cstring>
#include <limits>

#include "gtest/gtest.h"

namespace {

int MaxRet(const char* str, int str_len) {
    /*
    for
        对于在 0- strlen 之间的节点i ，
            分别向左右扩展 奇数
            在i , i+1 比较 再分别扩展
    */

    auto maxbetween = [&str, str_len](int i, int j) -> int {
        if (j >= str_len) {
            return 0;
        }
        if (i < 0) {
            return 0;
        }
        while (*(str + i) == *(str + j)) {
            i--;
            j++;
            if (j >= str_len) {
                break;
            }
            if (i < 0) {
                break;
            }
        }
        return --j - ++i + 1;
    };

    int last = std::numeric_limits<int>::min();

    for (int i = 0; i < str_len; i++) {
        int const s1 = maxbetween(i, i);
        int const s2 = maxbetween(i, i + 1);
        int const tmp = std::max(s1, s2);
        last = std::max(tmp, last);
    }

    return last;
}

TEST(x_max_len_of_parlinom_string_v2, t2) {
    const char* s1 = "abcba";
    EXPECT_EQ(MaxRet(s1, strlen(s1)), 5);
}

TEST(x_max_len_of_parlinom_string_v2, t3) {
    const char* s1 = "bcba";
    EXPECT_EQ(MaxRet(s1, strlen(s1)), 3);
}

TEST(x_max_len_of_parlinom_string_v2, t4) {
    const char* s1 = "zabcba";
    EXPECT_EQ(MaxRet(s1, strlen(s1)), 5);
}

TEST(x_max_len_of_parlinom_string_v2, t1) {
    const char* s1 = "00000";
    EXPECT_EQ(MaxRet(s1, strlen(s1)), 5);
}

TEST(x_max_len_of_parlinom_string_v2, t0) {
    const char* s1 = "5432345";
    EXPECT_EQ(MaxRet(s1, strlen(s1)), 7);
}

}  // namespace
