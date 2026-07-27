/*
 *
 * Given the array of integers nums, you will choose two different indices i and
 * j of that array. Return the maximum value of (nums[i]-1)*(nums[j]-1).
 * 2 <= nums.length <= 500
 * 1 <= nums[i] <= 10^3
 * */
#include <algorithm>
#include <vector>

using namespace std;

namespace {

class Solution {
   public:
    int MaxProduct(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        auto size = nums.size();
        auto n1 = (nums[0] - 1) * (nums[1] - 1);
        auto n2 = (nums[size - 2] - 1) * (nums[size - 1] - 1);
        auto max = std::max(n1, n2);
        max = std::max(max, (nums[0] - 1) * (nums[size - 1] - 1));

        return max;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(maxProduct, t0) {
    vector<int> nums{3, 4, 5, 2};
    Solution sl;
    int output = 12;
    int ret = sl.MaxProduct(nums);
    EXPECT_EQ(output, ret);
    /* If you choose the indices i=1 and j=2 (indexed from 0), you will get the
     * maximum value, that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.
     */
}

TEST(maxProduct, t1) {
    vector<int> nums{1, 5, 4, 5};
    Solution sl;
    int output = 16;
    int ret = sl.MaxProduct(nums);
    EXPECT_EQ(output, ret);
    /* Choosing the indices i=1 and j=3 (indexed from 0), you will get the
     * maximum value of (5-1)*(5-1) = 16.
     */
}

TEST(maxProduct, t2) {
    vector<int> nums{3, 7};
    Solution sl;
    int output = 12;
    int ret = sl.MaxProduct(nums);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
