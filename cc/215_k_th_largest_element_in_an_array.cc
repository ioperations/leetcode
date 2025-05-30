// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums and an integer k, return the kth largest element
in the array.

Note that it is the kth largest element in the sorted order, not the kth
distinct element.

*/

#include <functional>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int FindKthLargest(vector<int>& nums, int k) {
        // pass
        priority_queue<int, vector<int>, greater<>> q;

        for (auto& ptr : nums) {
            if (k > (int)q.size()) {
                q.push(ptr);
            } else if (ptr > q.top()) {
                q.push(ptr);
                q.pop();
            }
        }
        return q.top();
    }
    int FindKthLargestV2(vector<int>& nums, int k) {
        // pass
        priority_queue<int, vector<int>, greater<>> q;
        for (int i = 0; i < k; i++) {
            q.push(nums[i]);
        }

        int const size = nums.size();
        for (int i = k; i < size; i++) {
            if (q.top() < nums[i]) {
                q.pop();
                q.push(nums[i]);
            }
        }

        return q.top();
    }
};

TEST(k_th_largest_element_in_an_array, t1) {
    vector<int> nums = {3, 2, 1, 5, 6, 4};
    int const k = 2;
    int const out = 5;
    Solution sl;
    int ret = sl.FindKthLargest(nums, k);
    EXPECT_EQ(ret, out);

    ret = sl.FindKthLargestV2(nums, k);
    EXPECT_EQ(ret, out);
}

TEST(k_th_largest_element_in_an_array, t2) {
    vector<int> nums = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    int const k = 4;
    int const out = 4;
    Solution sl;
    int ret = sl.FindKthLargest(nums, k);
    EXPECT_EQ(ret, out);

    ret = sl.FindKthLargestV2(nums, k);
    EXPECT_EQ(ret, out);
}

}  // namespace
