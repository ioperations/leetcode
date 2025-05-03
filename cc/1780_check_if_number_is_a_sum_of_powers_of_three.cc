/*
 * Given an integer n, return true if it is possible to represent n as the sum
 * of distinct powers of three. Otherwise, return false.
 *
 * An integer y is a power of three if there exists an integer x such that y ==
 * 3x.
 */

constexpr static int GenThree(int n) {
    int v = 1;
    for (int i = 0; i < n; i++) {
        v = 3 * v;
    }

    return v;
}

class Solution {
   public:
    bool CheckPowersOfThree(int n) {
        // 3进制表示
        // 1 <= n <= 107
        //
        // Let's note that the maximum power of 3 you'll use in your soln is
        // 3^16
        //
        // The number can not be represented as a sum of powers
        // of 3 if it's ternary presentation has a 2 in it

        for (int const i : arr) {
            int const v = n / i;
            n = n % i;

            if (v == 2) {
                return false;
            }
        }
        return true;
    }

    static constexpr int arr[17] = {
        GenThree(16), GenThree(15), GenThree(14), GenThree(13), GenThree(12),
        GenThree(11), GenThree(10), GenThree(9),  GenThree(8),  GenThree(7),
        GenThree(6),  GenThree(5),  GenThree(4),  GenThree(3),  GenThree(2),
        GenThree(1),  GenThree(0),
    };
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    int const n = 12;
    Solution sl;
    auto ret = sl.CheckPowersOfThree(n);
    EXPECT_EQ(true, ret);
}

TEST(t0, t2) {
    int const n = 91;
    Solution sl;
    auto ret = sl.CheckPowersOfThree(n);
    EXPECT_EQ(true, ret);
}

TEST(t0, t3) {
    int const n = 21;
    Solution sl;
    auto ret = sl.CheckPowersOfThree(n);
    EXPECT_EQ(false, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
