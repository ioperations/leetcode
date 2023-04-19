// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// Implement pow(x, n), which calculates x raised to the
// power n(i.e., xn).

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    double x = 2.00000;
    int n = 10;

    double expected = 1024.00000;

    Solution s;
    double ret = s.MyPow(x, n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    double x = 2.10000;
    int n = 3;

    double expected = 9.261;

    Solution s;
    double ret = s.MyPow(x, n);
    EXPECT_NEAR(ret, expected, 0.001);
}

TEST(t0, t3) {
    double x = 2.00000;
    int n = -2;

    double expected = 0.25000;

    Solution s;
    double ret = s.MyPow(x, n);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t4) {
    double x = 0.00001;
    int n = 2147483647;

    double expected = 0;

    Solution s;
    double ret = s.MyPowV3(x, n);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
