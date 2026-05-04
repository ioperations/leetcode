// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/// given two string
/// find the max length of the substring containing same characters

#include <algorithm>
#include <array>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {

int MaxSubStringLengthOfTwoString(const char* s1, int s1_len, const char* s2,
                                  int s2_len) {
    std::array<std::array<int, 100>, 100> dp{};
    for (auto& row : dp) {
        row.fill(-1);
    }
    std::function<int(int, int)> dp_fun = [&dp_fun, &dp, s1, s2](int i,
                                                                 int j) -> int {
        if (i == -1) {
            return 0;
        }
        if (j == -1) {
            return 0;
        }

        if (dp.at(static_cast<size_t>(i)).at(static_cast<size_t>(j)) != -1) {
            return dp.at(static_cast<size_t>(i)).at(static_cast<size_t>(j));
        }

        if (*(s1 + i) == *(s2 + j)) {
            dp.at(static_cast<size_t>(i)).at(static_cast<size_t>(j)) = dp_fun(i - 1, j - 1) + 1;
        } else {
            dp.at(static_cast<size_t>(i)).at(static_cast<size_t>(j)) = std::max({dp_fun(i - 1, j), dp_fun(i, j - 1)});
        }
        return dp.at(static_cast<size_t>(i)).at(static_cast<size_t>(j));
    };
    return dp_fun(s1_len - 1, s2_len - 1);
}

TEST(T1j, t2) {
    const char* s1 = "hello";
    const char* s2 = "hell";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, static_cast<int>(strlen(s1)), s2, static_cast<int>(strlen(s2)));
    EXPECT_EQ(ret, 4);
}

TEST(T1j, t3) {
    const char* s1 = "hllo";
    const char* s2 = "hell";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, static_cast<int>(strlen(s1)), s2, static_cast<int>(strlen(s2)));
    EXPECT_EQ(ret, 3);
}

TEST(T1j, t4) {
    const char* s1 = "abcd";
    const char* s2 = "defg";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, static_cast<int>(strlen(s1)), s2, static_cast<int>(strlen(s2)));
    EXPECT_EQ(ret, 1);
}

TEST(T1j, t5) {
    const char* s1 = "abch";
    const char* s2 = "defg";
    int const ret =
        MaxSubStringLengthOfTwoString(s1, static_cast<int>(strlen(s1)), s2, static_cast<int>(strlen(s2)));
    EXPECT_EQ(ret, 0);
}

}  // namespace
