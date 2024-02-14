// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A peak element is an element that is strictly greater than its neighbors.

Given an integer array nums, find a peak element, and return its index. If the
array contains multiple peaks, return the index to any of the peaks.

You may imagine that nums[-1] = nums[n] = -∞.

You must write an algorithm that runs in O(log n) time.


*/

#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    /**
     * @brief 在数组当中找到最大的局部值
     * @param @nums 数组
     * @return 最大的局部值所在的偏移量
     */
    int FindPeakElement(vector<int> &nums)
        __attribute__((deprecated("use v2 instead"))) {
        // O(n)
        if (nums.size() == 0) return 0;
        if (nums.size() == 2) {
            if (nums[0] > nums[1]) {
                return 0;
            }
            if (nums[nums.size() - 1] > nums[nums.size() - 2]) {
                return nums.size() - 1;
            }
        }
        for (int i = 1; i < (int)nums.size() - 1; i++) {
            if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) {
                return i;
            }
        }
        // pass
        return -1;
    }

    /**
     * @brief 在数组当中找到最大的局部值
     * @param @nums 数组
     * @return 最大的局部值所在的偏移量
     */
    int FindPeakElementV2(vector<int> &nums) {
        // O(log(n))
        int low = 0;
        int high = nums.size() - 1;

        // handling corner case of array having only one element
        if (nums.size() == 1) return 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // if we are at the begning we can compare with the next element
            // only
            if (mid == 0) {
                if (nums[mid] > nums[mid + 1]) return mid;
                low = mid + 1;
                // if we are at the end we can compare with last second element
                // only
            } else if (mid == (int)nums.size() - 1) {
                if (nums[mid] > nums[mid - 1]) return mid;
                high = mid - 1;
            } else {
                // if the current element is peak return the index
                if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
                    return mid;
                // if the next element is bigger so we will go left as we need
                // only one more element to be in right of bigger element
                if (nums[mid + 1] > nums[mid]) {
                    low = mid + 1;
                    // same case as above to element before
                } else if (nums[mid - 1] > nums[mid]) {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};

#include <set>

TEST(t0, t1) {
    std::set<int> expectd{2};
    std::vector<int> nums{1, 2, 3, 1};
    Solution s;

    int ret = s.FindPeakElementV2(nums);
    EXPECT_EQ(expectd.count(ret), true);
}

TEST(t0, t2) {
    std::set<int> expectd{1, 5};
    std::vector<int> nums{1, 2, 1, 3, 5, 6, 4};
    Solution s;

    int ret = s.FindPeakElementV2(nums);
    EXPECT_EQ(expectd.count(ret), true);
}

}
