/*
 * You are given an integer array nums and an integer k.
 *
 * The frequency of an element x is the number of times it occurs in an array.
 *
 * An array is called good if the frequency of each element in this array is
 * less than or equal to k.
 *
 * Return the length of the longest good subarray of nums.
 *
 * A subarray is a contiguous non-empty sequence of elements within an array.
 *
 * 1 <= nums.length <= 105
 * 1 <= nums[i] <= 109
 * 1 <= k <= nums.length
 * */

#include <unordered_map>
#include <vector>
using namespace std;

namespace {
class Solution {
   public:
    int MaxSubarrayLength(vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());
        int cnt = 0;
        unordered_map<int, int> freq;  // 1 <= nums[i] <= 10^9
        freq.reserve(n);
        for (int l = 0, r = 0; r < n; r++) {
            int x = nums[r];
            auto it = freq.find(x);
            int& f = (it == freq.end()) ? freq[x] = 1 : ++(it->second);
            while (f > k) freq[nums[l++]]--;

            cnt = max(cnt, r - l + 1);  // max len
        }
        return cnt;
    }
};
}  // namespace
#include <gtest/gtest.h>

TEST(maxSubarrayLength, t0) {
    vector<int> nums{1, 2, 3, 1, 2, 3, 1, 2};
    int k = 2;
    int output = 6;
    Solution sl;
    int ret = sl.MaxSubarrayLength(nums, k);
    /*
     * The longest possible good subarray is [1,2,3,1,2,3] since the values 1,
     * 2, and 3 occur at most twice in this subarray. Note that the subarrays
     * [2,3,1,2,3,1] and [3,1,2,3,1,2] are also good. It can be shown that there
     * are no good subarrays with length more than 6.
     *
     */
    EXPECT_EQ(output, ret);
}

TEST(maxSubarrayLength, t1) {
    vector<int> nums{1, 2, 1, 2, 1, 2, 1, 2};
    int k = 1;
    int output = 2;
    Solution sl;
    int ret = sl.MaxSubarrayLength(nums, k);
    /*
     * The longest possible good subarray is [1,2] since the values 1 and 2
     * occur at most once in this subarray. Note that the subarray [2,1] is also
     * good. It can be shown that there are no good subarrays with length more
     * than 2.
     *
     */
    EXPECT_EQ(output, ret);
}

TEST(maxSubarrayLength, t2) {
    vector<int> nums{5, 5, 5, 5, 5, 5, 5};
    int k = 4;
    int output = 4;
    Solution sl;
    int ret = sl.MaxSubarrayLength(nums, k);
    /*
     * The longest possible good subarray is [5,5,5,5] since the value 5
     * occurs 4 times in this subarray. It can be shown that there are no good
     * subarrays with length more than 4.
     */
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
