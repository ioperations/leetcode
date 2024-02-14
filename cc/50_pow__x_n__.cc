// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// Implement pow(x, n), which calculates x raised to the
// power n(i.e., xn).

#include <string>

#include "gtest/gtest.h"

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    double MyPow(double x, int n) {
        if (n < 0) {
            return 1 / MyPow(x, -n);
        }
        if (n == 0) {
            return 1;
        }
        return MyPow(x, n - 1) * x;
    }

    double MyPowV2(double x, int n) {
        if (n == 0) return 1;
        if (n < 0) {
            return 1 / x * MyPowV2(1 / x, -(n + 1));
        }
        return (n % 2 == 0) ? MyPowV2(x, n / 2) : MyPowV2(x * x, n / 2);
    }

    double MyPowV3(double x, int n) {
        long long int n1 = n;
        double res = 1.00000;
        if (n < 0) {
            n1 *= -1;
        }
        while (n1 != 0) {
            if (n1 % 2 == 0) {
                x *= x;
                n1 /= 2;
            } else {
                res *= x;
                n1--;
            }
        }
        if (n < 0) {
            return 1 / res;
        }
        return res;
    }
};



TEST(t0, t1) {
    const double x = 2.00000;
    const int n = 10;

    const double expected = 1024.00000;

    Solution s;
    const double ret = s.MyPow(x, n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    const double x = 2.10000;
    const int n = 3;

    const double expected = 9.261;

    Solution s;
    const double ret = s.MyPow(x, n);
    EXPECT_NEAR(ret, expected, 0.001);
}

TEST(t0, t3) {
    const double x = 2.00000;
    const int n = -2;

    const double expected = 0.25000;

    Solution s;
    const double ret = s.MyPow(x, n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t4) {
    const double x = 0.00001;
    const int n = 2147483647;

    const double expected = 0;

    Solution s;
    const double ret = s.MyPowV3(x, n);
    EXPECT_EQ(ret, expected);
}

}
