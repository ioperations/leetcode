/*
 * You are given a 0-indexed string blocks of length n, where blocks[i] is
 * either 'W' or 'B', representing the color of the ith block. The characters
 * 'W' and 'B' denote the colors white and black, respectively.
 *
 * You are also given an integer k, which is the desired number of consecutive
 * black blocks.
 *
 * In one operation, you can recolor a white block such that it becomes a black
 * block.
 *
 * Return the minimum number of operations needed such that there is at least
 * one occurrence of k consecutive black blocks.
 *
 */

#include <algorithm>
#include <string>
using namespace std;

class Solution {
   public:
    int MinimumRecolors(string blocks, int k) {
        /*
         * n == blocks.length
         * 1 <= n <= 100
         * blocks[i] is either 'W' or 'B'.
         * 1 <= k <= n
         */

        auto size = blocks.size();
        int white_size = 0;
        for (int i = 0; i < k; i++) {
            if (blocks[i] == 'W') {
                white_size++;
            }
        }

        int ret = white_size;
        for (int i = k; i < size; i++) {
            if (blocks[i] == 'W') {
                white_size++;
            }

            if (blocks[i - k] == 'W') {
                white_size--;
            }

            ret = min(ret, white_size);
        }

        return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string const blocks = "WBBWWBBWBW";
    int const k = 7;
    int const output = 3;
    Solution sl;
    auto ret = sl.MinimumRecolors(blocks, k);
    EXPECT_EQ(ret, output);
    // Explanation:
    // One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd,
    // and 4th blocks so that blocks = "BBBBBBBWBW". It can be shown that there
    // is no way to achieve 7 consecutive black blocks in less than 3
    // operations. Therefore, we return 3.
}

TEST(t0, t2) {
    string const blocks = "WBWBBBW";
    int const k = 2;
    int const output = 0;
    Solution sl;
    auto ret = sl.MinimumRecolors(blocks, k);
    EXPECT_EQ(ret, output);
    // Explanation:
    // No changes need to be made, since 2 consecutive black blocks already
    // exist.
    // Therefore, we return 0.
}

TEST(t0, t3) {
    string const blocks = "BWBBWW";
    int const k = 6;
    int const output = 3;
    Solution sl;
    auto ret = sl.MinimumRecolors(blocks, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
