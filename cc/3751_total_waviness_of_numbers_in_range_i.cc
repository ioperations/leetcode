/*
 * You are given two integers num1 and num2 representing an inclusive range
 * [num1, num2].
 *
 * The waviness of a number is defined as the total count of its peaks and
 * valleys:
 *
 * A digit is a peak if it is strictly greater than both of its immediate
 * neighbors. A digit is a valley if it is strictly less than both of its
 * immediate neighbors. The first and last digits of a number cannot be peaks or
 * valleys. Any number with fewer than 3 digits has a waviness of 0. Return the
 * total sum of waviness for all numbers in the range [num1, num2].
 * 1 <= num1 <= num2 <= 105
 */

#include <string>
namespace {
class Solution {
   public:
    int TotalWaviness(int num1, int num2) {
        int ret = 0;
        for (int i = num1; i <= num2; i++) {
            ret += Count(i);
        }
        return ret;
    }

   private:
    int Count(int v) {
        if (v < 100) {
            return 0;
        }

        int ret = 0;
        std::string p = std::to_string(v);
        bool up = p[1] > p[0];
        bool down = p[1] < p[0];
        for (int i = 2; i < p.size(); i++) {
            if (p[i] > p[i - 1] && down) {
                ret += 1;
            } else if (p[i] < p[i - 1] && up) {
                ret += 1;
            }
            up = p[i] > p[i - 1];
            down = p[i] < p[i - 1];
        }

        return ret;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(totalWaviness, t1) {
    int num1 = 120, num2 = 130;
    int output = 3;
    /*Input:
     * Explanation:
     *
     * In the range [120, 130]:
     * 120: middle digit 2 is a peak, waviness = 1.
     * 121: middle digit 2 is a peak, waviness = 1.
     * 130: middle digit 3 is a peak, waviness = 1.
     * All other numbers in the range have a waviness of 0.
     * Thus, total waviness is 1 + 1 + 1 = 3.
     */

    Solution sl;
    int ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

TEST(totalWaviness, t2) {
    int num1 = 198, num2 = 202;
    int output = 3;
    /*
     * Explanation:
     *
     * In the range [198, 202]:
     * 198: middle digit 9 is a peak, waviness = 1.
     * 201: middle digit 0 is a valley, waviness = 1.
     * 202: middle digit 0 is a valley, waviness = 1.
     * All other numbers in the range have a waviness of 0.
     * Thus, total waviness is 1 + 1 + 1 = 3.

     */

    Solution sl;
    int ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

TEST(totalWaviness, t3) {
    int num1 = 4848, num2 = 4848;
    int output = 2;
    /*
     * Explanation:
     * Number 4848: the second digit 8 is a peak, and the third digit 4 is a
     * valley, giving a waviness of 2.
     */

    Solution sl;
    int ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

TEST(totalWaviness, t4) {
    int num1 = 449, num2 = 451;
    int output = 2;

    Solution sl;
    int ret = sl.TotalWaviness(num1, num2);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
