/**
 * @file 1732_find_highest_altitude.c
 * There is a biker going on a road trip. The road trip consists of n + 1 points
 * at different altitudes. The biker starts his trip on point 0 with altitude
 * equal 0.
 *
 * You are given an integer array gain of length n where gain[i] is the net gain
 * in altitude between points i​​​​​​ and i + 1 for all (0 <= i <
 * n). Return the highest altitude of a point.
 *
 */
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    int LargestAltitude(vector<int>& gain) {
        int i = 0;
        int max = 0;
        for (auto& alt : gain) {
            i = i + alt;
            max = std::max(max, i);
        }
        return max;
    }
};
}  // namespace

#include "gtest/gtest.h"

TEST(largestAltitude, t0) {
    vector<int> gain = {-5, 1, 5, 0, -7};
    int output = 1;
    Solution sl;
    int ret = sl.LargestAltitude(gain);
    // The altitudes are [0,-5,-4,1,1,-6]. The highest is 1.
    EXPECT_EQ(output, ret);
}

TEST(largestAltitude, t2) {
    vector<int> gain = {-4, -3, -2, -1, 4, 3, 2};
    int output = 0;
    Solution sl;
    int ret = sl.LargestAltitude(gain);
    // The altitudes are [0,-4,-7,-9,-10,-6,-3,-1]. The highest is 0.
    EXPECT_EQ(output, ret);
}