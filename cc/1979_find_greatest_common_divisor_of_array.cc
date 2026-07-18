/*
 * Given an integer array nums, return the greatest common divisor of the
 * smallest number and largest number in nums.
 *
 * The greatest common divisor of two numbers is the largest positive integer
 * that evenly divides both numbers.
 *
 * 2 <= nums.length <= 1000
 * 1 <= nums[i] <= 1000
 * */
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    int FindGcd(vector<int>& nums) {
        int min = std::numeric_limits<int>::max();
        int max = std::numeric_limits<int>::min();
        for (auto& v : nums) {
            min = std::min(min, v);
            max = std::max(max, v);
        }

        int ret = 1;
        for (int i = ret; i <= min; i++) {
            if (min % i == 0 && max % i == 0) {
                ret = i;
            }
        }
        return ret;
    }
};
}  // namespace
   //

#include <gtest/gtest.h>

TEST(findGCD, t0) {
    vector<int> nums{2, 5, 6, 9, 10};
    int output = 2;
    Solution sl;
    int ret = sl.FindGcd(nums);
    EXPECT_EQ(output, ret);
    /*
     * The smallest number in nums is 2.
     * The largest number in nums is 10.
     * The greatest common divisor of 2 and 10 is 2.
     * */
}
TEST(findGCD, t1) {
    vector<int> nums{7, 5, 6, 8, 3};
    int output = 1;
    Solution sl;
    int ret = sl.FindGcd(nums);
    EXPECT_EQ(output, ret);
    /*
     * The smallest number in nums is 3.
     * The largest number in nums is 8.
     * The greatest common divisor of 3 and 8 is 1.
     * */
}
TEST(findGCD, t2) {
    vector<int> nums{
        3,
        3,
    };
    int output = 3;
    Solution sl;
    int ret = sl.FindGcd(nums);
    EXPECT_EQ(output, ret);
    /*
     * The smallest number in nums is 3.
     * The largest number in nums is 3.
     * The greatest common divisor of 3 and 3 is 3.
     * */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
