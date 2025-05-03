/*
 * You are given a 0-indexed array nums of size n consisting of non-negative
 * integers.
 *
 * You need to apply n - 1 operations to this array where, in the ith operation
 * (0-indexed), you will apply the following on the ith element of nums:
 *
 * If nums[i] == nums[i + 1], then multiply nums[i] by 2 and set nums[i + 1] to
 * 0. Otherwise, you skip this operation. After performing all the operations,
 * shift all the 0's to the end of the array.
 *
 * For example, the array [1,0,2,0,0,1] after shifting all its 0's to the end,
 * is [1,2,1,0,0,0]. Return the resulting array.
 *
 * Note that the operations are applied sequentially, not all at once.
 *
 */

#include <algorithm>
#include <vector>

using namespace std;
class Solution {
   public:
    vector<int> ApplyOperations(vector<int>& nums) {
        auto n = nums.size();

        for (int i = 0; i < n - 1; i++) {
            if (nums[i] == nums[i + 1]) {
                nums[i] = nums[i] * 2;
                nums[i + 1] = 0;
            }
        }

        int j = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) nums[j++] = nums[i];
        }
        fill(nums.begin() + j, nums.end(), 0);

        return nums;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums{1, 2, 2, 1, 1, 0};
    vector<int> const output{1, 4, 2, 0, 0, 0};

    Solution sl;
    auto ret = sl.ApplyOperations(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums{0, 1};
    vector<int> const output{1, 0};

    Solution sl;
    auto ret = sl.ApplyOperations(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> nums{328, 0, 0, 0, 93,  43, 802, 802, 0,
                     580, 0, 0, 0, 973, 0,  0,   774};
    vector<int> const output{328, 93, 43, 1604, 580, 973, 774, 0, 0,
                             0,   0,  0,  0,    0,   0,   0,   0};

    Solution sl;
    auto ret = sl.ApplyOperations(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
