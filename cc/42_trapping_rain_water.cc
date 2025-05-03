// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given n non-negative integers representing an elevation map where the width of
each bar is 1, compute how much water it can trap after raining.
*/

/*
                                          _____
                                         |     |
                                         |     |
                  _____ _________________|_____|_____ _____ _____
                 |     |=====|=====|=====|     |     |=====|     |
                 |     |=====|=====|=====|     |     |=====|     |
      _____ _____|_____|_____|_____|_____|_____|_____|_____|_____|_____
     |     |=====|     |     |=====|     |     |     |     |     |     |
     |     |=====|     |     |=====|     |     |     |     |     |     |
     |_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|_____|
_________________________________________________

0       1     0     2     1     0     1    3     2     1     2     1

*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int Trap(vector<int>& height) {
        int const n = height.size();
        int left = 0;
        int right = n - 1;
        int res = 0;
        int leftmax = 0, rightmax = 0;

        while (left <= right) {
            // handling left ptr
            if (height[left] <= height[right]) {
                if (height[left] >= leftmax)
                    leftmax = height[left];

                else
                    res += leftmax - height[left];

                left++;

            }

            // handling right ptr
            else {
                if (height[right] >= rightmax)
                    rightmax = height[right];

                else
                    res += rightmax - height[right];

                right--;
            }
        }

        return res;
    }
};

TEST(trapping_rain_water, t1) {
    std::vector<int> height = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    int const expected = 6;

    Solution s;
    int const ret = s.Trap(height);

    EXPECT_EQ(ret, expected);
}
TEST(trapping_rain_water, t2) {
    std::vector<int> height = {4, 2, 0, 3, 2, 5};
    int const expected = 9;

    Solution s;
    int const ret = s.Trap(height);

    EXPECT_EQ(ret, expected);
}

}  // namespace
