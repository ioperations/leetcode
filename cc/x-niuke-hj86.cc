// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>

#include "gtest/gtest.h"

namespace {
#ifndef BYTE_LEN
#define BYTE_LEN 8
#endif

int Func(int number) {
    int max = 0;

    const int z[] = {
        1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7,
    };

    // bool last_bit_is_one = false;
    int already_lian_xu_one_length = 0;
    for (int const i : z) {
        bool const this_bit_is_one = (number & i) != 0;
        // last_bit_is_one = this_bit_is_one;
        if (this_bit_is_one) {
            already_lian_xu_one_length++;
            max = std::max(max, already_lian_xu_one_length);
        } else {
            already_lian_xu_one_length = 0;
        }
    }

    return max;
}

TEST(x_niuke_hjv2, t1) { EXPECT_EQ(Func(5), 1); }
TEST(x_niuke_hjv2, t2) { EXPECT_EQ(Func(3), 2); }
TEST(x_niuke_hjv2, t4) { EXPECT_EQ(Func(110), 3); }
TEST(x_niuke_hjv2, t5) { EXPECT_EQ(Func(126), 6); }
}  // namespace
