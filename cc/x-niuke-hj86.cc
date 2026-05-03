// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <array>

#include "gtest/gtest.h"

namespace {

constexpr int byte_len = 8;

int Func(int number) {
    int max = 0;

    constexpr std::array<int, byte_len> z = {
        1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    };

    int already_lian_xu_one_length = 0;
    for (const int i : z) {
        const bool this_bit_is_one = (number & i) != 0;
        if (this_bit_is_one) {
            ++already_lian_xu_one_length;
            max = std::max(max, already_lian_xu_one_length);
        } else {
            already_lian_xu_one_length = 0;
        }
    }

    return max;
}

TEST(XNiukeHjv2, t1) { EXPECT_EQ(Func(5), 1); }
TEST(XNiukeHjv2, t2) { EXPECT_EQ(Func(3), 2); }
TEST(XNiukeHjv2, t4) { EXPECT_EQ(Func(110), 3); }
TEST(XNiukeHjv2, t5) { EXPECT_EQ(Func(126), 6); }
}  // namespace
