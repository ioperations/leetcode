// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer n, return the nth digit of the infinite integer sequence
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
*/

#include <cmath>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int FindNthDigit(int n) {
        if (n < 10) return n;
        long d = 1;
        long base = 9;
        while (n - base * d > 0) {
            n = static_cast<int>(n - base * d);
            base *= 10;
            d++;
        }
        int const index = n % d == 0 ? static_cast<int>(d) : n % d;
        long const num = static_cast<long>(pow(10, d - 1)) + (index == d ? n / d - 1 : n / d);
        return to_string(num).at(static_cast<size_t>(index) - 1) - '0';
    }
};

/*
_________________________________________________________________
| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |16 |
|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 1 | 0 | 1 | 1 | 1 | 2 | 1 |
|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
*/

TEST(nthV, t1) {
    int const n = 3;

    int const output = 3;
    Solution sl;
    int const ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(nthV, t2) {
    int const n = 11;
    int const output = 0;
    // Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9,
    // 10, 11, ... is a 0, which is part of the number 10.
    Solution sl;
    int const ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(nthV, t3) {
    int const n = 99;
    int const output = 4;
    Solution sl;
    int const ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(nthV, t4) {
    int const n = 100;
    int const output = 5;
    Solution sl;
    int const ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(nthV, t5) {
    int const n = 1000;
    int const output = 3;
    Solution sl;
    int const ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
