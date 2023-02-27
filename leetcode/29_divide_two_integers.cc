/*
    Given two integers dividend and divisor, divide two integers without using
    multiplication, division, and mod operator.

    The integer division should truncate toward zero, which means losing its
    fractional part. For example, 8.345 would be truncated to 8, and -2.7335
    would be truncated to -2.

    Return the quotient after dividing dividend by divisor.

   Note: Assume we are dealing with an environment that could only store
   integers within the 32-bit signed integer range: [−231, 231 − 1]. For this
   problem, if the quotient is strictly greater than 231 - 1, then return 231 -
   1, and if the quotient is strictly less than -231, then return -231.

*/
#include <limits.h>

#include <iostream>
using namespace std;

class Solution {
   public:
    int Divide(int d1, int b1) {
        // -2^31 <= dividend, divisor <= 2^31 - 1
        // divisor != 0
        long long ans = 0, h, d, b;
        d = d1;
        b = b1;
        int f = 0;
        if (d < 0 && b < 0) {
            d = abs(d);
            b = abs(b);
        } else if (d < 0) {
            d = abs(d);
            f = 1;
        } else if (b < 0) {
            f = 1;
            b = abs(b);
        }

        if (d > 1000) {
            int c = 0;
            long long b2 = 0;
            while (b2 < 1000) {
                b2 += b;
                c++;
            }
            while (d >= b2) {
                d -= b2;
                ans++;
            }
            h = ans;
            c--;
            while (c--) ans += h;

            while (d >= b) {
                d -= b;
                ans++;
            }

        } else {
            while (d >= b) {
                d -= b;
                ans++;
            }
        }

        if (f == 1) {
            h = ans;
            ans -= h;
            ans -= h;
        }

        if (ans > INT_MAX) return INT_MAX;
        if (ans < INT_MIN) return INT_MIN;
        return (int)ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int dividend = 10, divisor = 3;
    int output = 3;
    // Explanation: 10/3 = 3.33333.. which is truncated to 3.
    Solution sls;
    int ret = sls.Divide(dividend, divisor);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int dividend = 7, divisor = -3;
    int output = -2;
    // Explanation: 7/-3 = -2.33333.. which is truncated to -2.
    Solution sls;
    int ret = sls.Divide(dividend, divisor);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
