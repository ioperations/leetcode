// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer num, return the number of steps to reduce it to zero.

In one step, if the current number is even, you have to divide it by 2,
otherwise, you have to subtract 1 from it.*/

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int NumberOfSteps(int num) {
        int step = 0;
        while (num) {
            if (num % 2 == 0) {
                num /= 2;
            } else {
                num -= 1;
            }
            step++;
        }
        return step;
    }
};

TEST(number_of_steps_to_reduce_a_number_to_zero, t1) {
    int const num = 14;
    int const output = 6;
    // Explanation:
    // Step 1) 14 is even; divide by 2 and obtain 7.
    // Step 2) 7 is odd; subtract 1 and obtain 6.
    // Step 3) 6 is even; divide by 2 and obtain 3.
    // Step 4) 3 is odd; subtract 1 and obtain 2.
    // Step 5) 2 is even; divide by 2 and obtain 1.
    // Step 6) 1 is odd; subtract 1 and obtain 0.

    Solution sls;
    int const ret = sls.NumberOfSteps(num);

    EXPECT_EQ(ret, output);
}

TEST(number_of_steps_to_reduce_a_number_to_zero, t2) {
    int const num = 8;
    int const output = 4;
    // Explanation:
    // Step 1) 8 is even; divide by 2 and obtain 4.
    // Step 2) 4 is even; divide by 2 and obtain 2.
    // Step 3) 2 is even; divide by 2 and obtain 1.
    // Step 4) 1 is odd; subtract 1 and obtain 0.

    Solution sls;
    int const ret = sls.NumberOfSteps(num);

    EXPECT_EQ(ret, output);
}

TEST(number_of_steps_to_reduce_a_number_to_zero, t3) {
    int const num = 123;
    int const output = 12;

    Solution sls;
    int const ret = sls.NumberOfSteps(num);

    EXPECT_EQ(ret, output);
}

}  // namespace
