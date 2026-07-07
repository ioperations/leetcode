/*
 * You are given an integer n.
 *
 * Form a new integer x by concatenating all the non-zero digits of n in their
 * original order. If there are no non-zero digits, x = 0.
 *
 * Let sum be the sum of digits in x.
 *
 * Return an integer representing the value of x * sum.
 * 0 <= n <= 109
 */
namespace {

class Solution {
   public:
    long long SumAndMultiply(int n) {
        long long sum = 0;
        int x = 0;
        int rate = 1;
        while (n > 0) {
            int tmp = n % 10;
            n = n / 10;
            if (tmp > 0) {
                x = x + tmp * rate;
                rate = rate * 10;
                sum = sum + tmp;
            }
        }

        return sum * x;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(sumAndMultiply, t0) {
    int n = 10203004;
    int output = 12340;
    Solution sl;
    int ret = sl.SumAndMultiply(n);
    EXPECT_EQ(output, ret);
    /*
     * The non-zero digits are 1, 2, 3, and 4. Thus, x = 1234.
     * The sum of digits is sum = 1 + 2 + 3 + 4 = 10.
     * Therefore, the answer is x * sum = 1234 * 10 = 12340.
     */
}

TEST(sumAndMultiply, t1) {
    int n = 10203004;
    int output = 12340;
    Solution sl;
    int ret = sl.SumAndMultiply(n);
    EXPECT_EQ(output, ret);
    /*
     * The non-zero digit is 1, so x = 1 and sum = 1.
     * Therefore, the answer is x * sum = 1 * 1 = 1.
     */
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
