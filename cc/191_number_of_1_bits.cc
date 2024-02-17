// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Write a function that takes an unsigned integer and returns the number of '1'
bits it has (also known as the Hamming weight).

Note:

Note that in some languages, such as Java, there is no unsigned integer type. In
this case, the input will be given as a signed integer type. It should not
affect your implementation, as the integer's internal binary representation is
the same, whether it is signed or unsigned. In Java, the compiler represents the
signed integers using 2's complement notation. Therefore, in Example 3, the
input represents the signed integer. -3.
*/

#include <cstdint>
#include <string>

#include "gtest/gtest.h"

namespace { 
class Solution {
   public:
    int HammingWeight(uint32_t n) {
        // pass
        int num = 0;

        while (n) {
            if (n & 1) num++;
            n = n >> 1;
        }
        return num;
    }
};



TEST(t0, t1) {
    uint32_t n = 11;  // 00000000000000000000000000001011;
    int expected = 3;
    Solution s;
    int ret = s.HammingWeight(n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    uint32_t n = 128;  //  00000000000000000000000010000000;
    int expected = 1;
    Solution s;
    int ret = s.HammingWeight(n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t3) {
    uint32_t n = 4294967293;  // 11111111111111111111111111111101;
    int expected = 31;
    Solution s;
    int ret = s.HammingWeight(n);
    EXPECT_EQ(ret, expected);
}

}
