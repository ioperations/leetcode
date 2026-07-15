/**
 * You are given an integer n. Your task is to compute the GCD (greatest common
 * divisor) of two values:
 *
 * sumOdd: the sum of the smallest n positive odd numbers.
 *
 * sumEven: the sum of the smallest n positive even numbers.
 *
 * Return the GCD of sumOdd and sumEven.
 *
 */
namespace {

class Solution {
   public:
    int GcdOfOddEvenSums(int n) {
        return n;
        /**
         * Hint 1
         * The first n odd numbers sum to n * n
         * Hint 2
         * First n even numbers sum to n * (n + 1)
         * Hint 3
         * gcd(n, n + 1) = 1, so the answer is n
         *
         **/
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(gcdOfOddEvenSums, t0) {
    int n = 4;

    int output = 4;
    Solution sl;
    int ret = sl.GcdOfOddEvenSums(n);
    EXPECT_EQ(output, ret);

    // Explanation:
    // Sum of the first 4 odd numbers sumOdd = 1 + 3 + 5 + 7 = 16
    // Sum of the first 4 even numbers sumEven = 2 + 4 + 6 + 8 = 20
    // Hence, GCD(sumOdd, sumEven) = GCD(16, 20) = 4.
}
TEST(gcdOfOddEvenSums, t1) {
    int n = 5;

    int output = 5;
    Solution sl;
    int ret = sl.GcdOfOddEvenSums(n);
    EXPECT_EQ(output, ret);

    // Explanation:
    // Sum of the first 5 odd numbers sumOdd = 1 + 3 + 5 + 7 + 9 = 25
    // Sum of the first 5 even numbers sumEven = 2 + 4 + 6 + 8 + 10 = 30
    // Hence, GCD(sumOdd, sumEven) = GCD(25, 30) = 5.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
