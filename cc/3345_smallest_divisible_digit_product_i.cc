/*
 * You are given two integers n and t. Return the smallest number greater than
 * or equal to n such that the product of its digits is divisible by t.
 *
 * 1 <= n <= 100
 * 1 <= t <= 10
 * */

namespace {

class Solution {
   public:
    int SmallestNumber(int n, int t) {
        while (true) {
            int product = Pro(n);
            if (product % t == 0) {
                return n;
            }
            n++;
        }
    }

    int Pro(int num) {
        int s = num % 10;
        num = num / 10;
        while (num) {
            int t = num % 10;
            s = s * t;
            num = num / 10;
        }
        return s;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(smallestNumber, t0) {
    int n = 10;
    int t = 2;
    int output = 10;
    Solution sl;
    int ret = sl.SmallestNumber(n, t);
    EXPECT_EQ(output, ret);
    // The digit product of 10 is 0, which is divisible by 2, making it the
    // smallest number greater than or equal to 10 that satisfies the
    // condition.
}
TEST(smallestNumber, t1) {
    int n = 15;
    int t = 3;
    int output = 16;
    Solution sl;
    int ret = sl.SmallestNumber(n, t);
    EXPECT_EQ(output, ret);
    // The digit product of 16 is 6, which is divisible by 3, making it the
    // smallest number greater than or equal to 15 that satisfies the
    // condition.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
