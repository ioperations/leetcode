/**
 * Given an integer array nums, find three numbers whose product is maximum and
 * return the maximum product.
 *
 * 3 <= nums.length <= 104
 * -1000 <= nums[i] <= 1000
 * */

#include <algorithm>
#include <vector>
using namespace std;

namespace {
using std::less;

class Solution {
   public:
    int MaximumProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end(), less<>());

        auto size = nums.size();
        auto left = nums[0] * nums[1] * nums[2];
        auto left1 = nums[0] * nums[1] * nums[size - 1];
        auto right = nums[size - 3] * nums[size - 2] * nums[size - 1];
        auto right1 = nums[0] * nums[size - 2] * nums[size - 1];

        auto max = std::max(left, right);
        max = std::max(max, right1);
        max = std::max(max, left1);

        return max;
    }
};

}  // namespace
   //
#include <gtest/gtest.h>

TEST(maximumProduct, t1) {
    vector<int> nums{1, 2, 3};
    int output = 6;
    Solution sl;
    int ret = sl.MaximumProduct(nums);
    EXPECT_EQ(output, ret);
}
TEST(maximumProduct, t2) {
    vector<int> nums{1, 2, 3, 4};
    int output = 24;
    Solution sl;
    int ret = sl.MaximumProduct(nums);
    EXPECT_EQ(output, ret);
}
TEST(maximumProduct, t3) {
    vector<int> nums{-1, -2, -3};
    int output = -6;
    Solution sl;
    int ret = sl.MaximumProduct(nums);
    EXPECT_EQ(output, ret);
}

TEST(maximumProduct, t4) {
    vector<int> nums{-100, -98, -1, 2, 3, 4};
    int output = 39200;
    Solution sl;
    int ret = sl.MaximumProduct(nums);
    EXPECT_EQ(output, ret);
}

TEST(maximumProduct, t5) {
    vector<int> nums{-1, -2, -3, -4};
    int output = -6;
    Solution sl;
    int ret = sl.MaximumProduct(nums);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
