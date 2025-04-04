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
    int minimumRecolors(string blocks, int k) {
        /*
         * n == blocks.length
         * 1 <= n <= 100
         * blocks[i] is either 'W' or 'B'.
         * 1 <= k <= n
         */

        auto size = blocks.size();
        int whiteSize = 0;
        for (int i = 0; i < k; i++) {
            if (blocks[i] == 'W') {
                whiteSize++;
            }
        }

        int ret = whiteSize;
        for (int i = k; i < size; i++) {
            if (blocks[i] == 'W') {
                whiteSize++;
            }

            if (blocks[i - k] == 'W') {
                whiteSize--;
            }

            ret = min(ret, whiteSize);
        }

        return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string blocks = "WBBWWBBWBW";
    int k = 7;
    int Output = 3;
    Solution sl;
    auto ret = sl.minimumRecolors(blocks, k);
    EXPECT_EQ(ret, Output);
    // Explanation:
    // One way to achieve 7 consecutive black blocks is to recolor the 0th, 3rd,
    // and 4th blocks so that blocks = "BBBBBBBWBW". It can be shown that there
    // is no way to achieve 7 consecutive black blocks in less than 3
    // operations. Therefore, we return 3.
}

TEST(t0, t2) {
    string blocks = "WBWBBBW";
    int k = 2;
    int Output = 0;
    Solution sl;
    auto ret = sl.minimumRecolors(blocks, k);
    EXPECT_EQ(ret, Output);
    // Explanation:
    // No changes need to be made, since 2 consecutive black blocks already
    // exist.
    // Therefore, we return 0.
}

TEST(t0, t3) {
    string blocks = "BWBBWW";
    int k = 6;
    int Output = 3;
    Solution sl;
    auto ret = sl.minimumRecolors(blocks, k);
    EXPECT_EQ(ret, Output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
