// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Reverse bits of a given 32 bits unsigned integer.

Note:

Note that in some languages, such as Java, there is no unsigned integer type. In
this case, both input and output will be given as a signed integer type. They
should not affect your implementation, as the integer's internal binary
representation is the same, whether it is signed or unsigned. In Java, the
compiler represents the signed integers using 2's complement notation.
Therefore, in Example 2 above, the input represents the signed integer -3 and
the output represents the signed integer -1073741825.
*/

#include <stddef.h>

#include <algorithm>
#include <cstdint>
#include <string>

#include "gtest/gtest.h"

using namespace std;

uint32_t ConstructUint32T(const std::string &s) {
    uint32_t num = 0;
    // pass
    for (size_t i = 0; i < s.size(); i++) {
        num += (s[s.size() - i - 1] == '1') ? (i == 0 ? 1 : 2 << (i - 1)) : 0;
    }
    return num;
}

std::string ConstructString(uint32_t n) {
    std::string ret = "00000000000000000000000000000000";

    int i = 0;

    while (n) {
        if (n & 1) {
            ret[i] = '1';
        } else {
            ret[i] = '0';
        }
        n = n >> 1;
        i++;
    }
    std::reverse(ret.begin(), ret.end());

    return ret;
}

namespace {
class Solution {
   public:
    uint32_t ReverseBits(uint32_t n) {
        // pass

        std::string str = ConstructString(n);
        std::reverse(str.begin(), str.end());

        n = ConstructUint32T(str);

        uint32_t ret = 0;
        int i = 0;
        while (n) {
            if (n & 1) {
                ret += i == 0 ? 1 : 2 << (i - 1);
            }
            n = n >> 1;

            i++;
        }
        return ret;
    }

    uint32_t ReverseBitsV2(uint32_t n) {
        // pass

        uint32_t ret = 0;
        int i = 0;
        while (n) {
            if (n & 1) {
                ret += i == 31 ? 1 : 2 << (30 - i);
            }
            n = n >> 1;

            i++;
        }
        return ret;
    }
};

TEST(base, tp) {
    EXPECT_EQ(2 << 1, 4);
    EXPECT_EQ(2 << 0, 2);
}

TEST(base, t0) {
    std::string z = "00000000000000000000000000000001";
    uint32_t n = ConstructUint32T(z);           //
    std::string expected = ConstructString(n);  //(
    EXPECT_EQ(expected, z);
}

TEST(base, t1) {
    std::string z = "00000010100101000001111010011100";
    uint32_t n = ConstructUint32T(z);  //

    std::string expected = ConstructString(n);  //(
    EXPECT_EQ(expected, z);
}

TEST(reverse_bits, t1) {
    std::string input = "00000010100101000001111010011100";
    uint32_t n = ConstructUint32T(input);  //
    uint32_t expected = 964176192;         //( 00111001011110000010100101000000)

    std::string output_expected = ConstructString(expected);

    Solution s;
    uint32_t ret = s.ReverseBits(n);
    std::string ret_str = ConstructString(ret);
    EXPECT_EQ(ret_str, output_expected);
}

TEST(reverse_bits, t2) {
    uint32_t n = ConstructUint32T("11111111111111111111111111111101");  //
    uint32_t expected = 3221225471;  // (10111111111111111111111111111111)

    std::string output_expected = ConstructString(expected);
    Solution s;
    uint32_t ret = s.ReverseBits(n);

    std::string ret_str = ConstructString(ret);
    EXPECT_EQ(ret_str, output_expected);
}

}  // namespace
