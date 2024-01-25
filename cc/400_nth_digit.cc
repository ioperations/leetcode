// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer n, return the nth digit of the infinite integer sequence
    [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...].
*/

#include <cmath>
#include <string>
using namespace std;
class Solution {
   public:
    int FindNthDigit(int n) {
        if (n < 10) return n;
        long d = 1, base = 9;
        while (n - base * d > 0) {
            n = n - base * d;
            base *= 10;
            d++;
        }
        int index = n % d == 0 ? d : n % d;
        long num = pow(10, d - 1) + (index == d ? n / d - 1 : n / d);
        return to_string(num)[index - 1] - '0';
    }
};

#include <gtest/gtest.h>

#include <iostream>

/*
_________________________________________________________________
| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |10 |11 |12 |13 |14 |15 |16 |
|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 1 | 0 | 1 | 1 | 1 | 2 | 1 |
|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|___|
*/

TEST(t0, t1) {
    int n = 3;

    int output = 3;
    Solution sl;
    int ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 11;
    int output = 0;
    // Explanation: The 11th digit of the sequence 1, 2, 3, 4, 5, 6, 7, 8, 9,
    // 10, 11, ... is a 0, which is part of the number 10.
    Solution sl;
    int ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int n = 99;
    int output = 4;
    Solution sl;
    int ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t4) {
    int n = 100;
    int output = 5;
    Solution sl;
    int ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t5) {
    int n = 1000;
    int output = 3;
    Solution sl;
    int ret = sl.FindNthDigit(n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
