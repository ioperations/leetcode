// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
393. UTF-8 Validation
Medium

373

1529

Add to List

Share
Given an integer array data representing the data, return whether it is a valid
UTF-8 encoding (i.e. it translates to a sequence of valid UTF-8 encoded
characters).

A character in UTF8 can be from 1 to 4 bytes long, subjected to the following
rules:

For a 1-byte character, the first bit is a 0, followed by its Unicode code.
For an n-bytes character, the first n bits are all one's, the n + 1 bit is 0,
followed by n - 1 bytes with the most significant 2 bits being 10. This is how
the UTF-8 encoding would work:

     Number of Bytes   |        UTF-8 Octet Sequence
                       |              (binary)
   --------------------+-----------------------------------------
            1          |   0xxxxxxx
            2          |   110xxxxx 10xxxxxx
            3          |   1110xxxx 10xxxxxx 10xxxxxx
            4          |   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
x denotes a bit in the binary form of a byte that may be either 0 or 1.

Note: The input is an array of integers. Only the least significant 8 bits of
each integer is used to store the data. This means each integer represents only
1 byte of data.
*/

#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    bool ValidUtf8(vector<int> &data) {
        const int mask_10 = 0x80;     // 128
        const int mask_110 = 0xC0;    // 192
        const int mask_1110 = 0xE0;   // 224
        const int mask_11110 = 0xF0;  // 240
        const int mask_11111 = 0xF8;  // 248
        for (int i = 0, size = data.size(); i < size; ++i) {
            if ((data[i] & mask_10) == 0) continue;
            if ((data[i] >= mask_10 && data[i] < mask_110) ||
                data[i] >= mask_11111)
                return false;
            if ((data[i] & mask_11110) == mask_11110) {
                for (int j = 0; i < size && j < 3; ++j) {
                    if (++i == size ||
                        (data[i] < mask_10 || data[i] > mask_110))
                        return false;
                }
            } else if ((data[i] & mask_1110) == mask_1110) {
                for (int j = 0; i < size && j < 2; ++j) {
                    if (++i == size ||
                        (data[i] < mask_10 || data[i] > mask_110))
                        return false;
                }
            } else if ((data[i] & mask_110) == mask_110) {
                for (int j = 0; i < size && j < 1; ++j) {
                    if (++i == size ||
                        (data[i] < mask_10 || data[i] > mask_110))
                        return false;
                }
            }
        }
        return true;
    }
};



TEST(t0, t1) {
    vector<int> data = {197, 130, 1};
    bool output = true;
    // Explanation: data represents the octet sequence: 11000101 10000010
    // 00000001. It is a valid utf-8 encoding for a 2-bytes character followed
    // by a 1-byte character.

    Solution sl;
    bool ret = sl.ValidUtf8(data);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> data = {235, 140, 4};
    bool output = false;
    // data represented the octet sequence: 11101011 10001100 00000100.
    // The first 3 bits are all one's and the 4th bit is 0 means it is a 3-bytes
    // character. The next byte is a continuation byte which starts with 10 and
    // that's correct.
    // But the second continuation byte does not start with 10, so it is
    // invalid.
    Solution sl;
    bool ret = sl.ValidUtf8(data);
    EXPECT_EQ(ret, output);
}

}
