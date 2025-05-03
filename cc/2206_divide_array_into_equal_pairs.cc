/*
 * You are given an integer array nums consisting of 2 * n integers.
 *
 * You need to divide nums into n pairs such that:
 * * Each element belongs to exactly one pair.
 * * The elements present in a pair are equal.
 * Return true if nums can be divided into n pairs, otherwise return false.
 */
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    bool divideArray(vector<int>& nums) {
        /* nums.length == 2 * n
         * 1 <= n <= 500
         * 1 <= nums[i] <= 500
         */
        unordered_map<int, int> v;
        for (auto& p : nums) {
            v[p]++;
        }

        return !any_of(v.begin(), v.end(),
                       [](auto& v) { return v.second % 2 == 1; });
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {3, 2, 3, 2, 2, 2};
    bool Output = true;
    Solution sl;
    int ret = sl.divideArray(nums);
    EXPECT_EQ(ret, Output);
    // Explanation:
    // There are 6 elements in nums, so they should be divided into 6 / 2 = 3
    // pairs. If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it
    // will satisfy all the conditions.
}

TEST(t0, t2) {
    vector<int> nums = {1, 2, 3, 4};
    bool Output = false;
    Solution sl;
    int ret = sl.divideArray(nums);
    EXPECT_EQ(ret, Output);
    // Explanation:
    // There is no way to divide nums into 4 / 2 = 2 pairs such that the pairs
    // satisfy every condition.
    // will satisfy all the conditions.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
