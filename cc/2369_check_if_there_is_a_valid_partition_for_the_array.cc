
/*
 * You are given a 0-indexed integer array nums. You have to partition the array
into one or more contiguous subarrays.

We call a partition of the array valid if each of the obtained subarrays
satisfies one of the following conditions:

    The subarray consists of exactly 2 equal elements. For example, the subarray
[2,2] is good. The subarray consists of exactly 3 equal elements. For example,
the subarray [4,4,4] is good. The subarray consists of exactly 3 consecutive
increasing elements, that is, the difference between adjacent elements is 1. For
example, the subarray [3,4,5] is good, but the subarray [1,3,5] is not.

Return true if the array has at least one valid partition. Otherwise, return
false.

 */

#include <map>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool ValidPartition(vector<int> &nums) {
        // pass
        return CheckIfOk(nums, 0);
    }
    bool CheckIfOk(vector<int> &nums, int start_from) {
        // pass
        if (start_from == nums.size()) {
            return true;
        }
        if (start_from > nums.size()) {
            return false;
        }
        if (start_from + 1 == nums.size()) {
            return false;
        }
        if (cache.find(start_from) != cache.end()) {
            return cache[start_from];
        }

        if (nums[start_from] == nums[start_from + 1]) {
            if (CheckIfOk(nums, start_from + 2)) {
                cache[start_from] = true;
                return true;
            }

            if (start_from + 2 < nums.size()) {
                if (nums[start_from] == nums[start_from + 2]) {
                    return CheckIfOk(nums, start_from + 3);
                }
                cache[start_from] = false;
                return false;
            }
            cache[start_from] = false;
            return false;
        }

        if (start_from + 2 >= nums.size()) {
            return false;
        }

        if (nums[start_from + 2] - nums[start_from + 1] == 1) {
            if (nums[start_from + 1] - nums[start_from] == 1) {
                return CheckIfOk(nums, start_from + 3);
            }
        }
        cache[start_from] = false;
        return false;
    }
    std::map<int, bool> cache;
};



TEST(t0, t1) {
    vector<int> nums = {4, 4, 4, 5, 6};
    bool output = true;
    // Explanation: The array can be partitioned into the subarrays [4,4] and
    // [4,5,6]. This partition is valid, so we return true.
    Solution sl;
    bool ret = sl.ValidPartition(nums);
    EXPECT_EQ(output, ret);
}

TEST(t0, t2) {
    vector<int> nums = {1, 1, 1, 2};
    bool output = false;
    // There is no valid partition for this array.
    Solution sl;
    bool ret = sl.ValidPartition(nums);
    EXPECT_EQ(output, ret);
}
}
