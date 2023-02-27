/*
Given an integer array nums, you need to find one continuous subarray that if
you only sort this subarray in ascending order, then the whole array will be
sorted in ascending order.

Return the shortest such subarray and output its length
**/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

class Solution {
   public:
    int FindUnsortedSubarray(vector<int> &nums) {
        priority_queue<int, vector<int>, std::less<int>> q1;
        priority_queue<int, vector<int>, std::greater<int>> q2;
        int i, n = nums.size(), j;
        for (i = 0; i < n; i++) {
            q1.push(nums[i]);
            q2.push(nums[i]);
        }
        for (i = 0; i < n; i++) {
            if (nums[i] != q2.top()) break;
            q2.pop();
        }
        if (i == n) return 0;
        for (j = n - 1; j >= 0; j--) {
            if (nums[j] != q1.top()) break;
            q1.pop();
        }
        return j - i + 1;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> v{2, 6, 4, 8, 10, 9, 15};
    int expected = 5;
    // You need to sort [6, 4, 8, 10, 9] in ascending
    // order to make the whole
    // array sorted in ascending order.
    Solution sl;
    int ret = sl.FindUnsortedSubarray(v);

    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    std::vector<int> v{1, 2, 3, 4};
    int expected = 0;
    Solution sl;
    int ret = sl.FindUnsortedSubarray(v);
    EXPECT_EQ(ret, expected);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
