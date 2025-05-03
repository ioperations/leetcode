/*
 * You are given a 0-indexed integer array nums, and an integer k.
 *
 * In one operation, you will:
 *
 * Take the two smallest integers x and y in nums.
 * Remove x and y from nums.
 * Add min(x, y) * 2 + max(x, y) anywhere in the array.
 * Note that you can only apply the described operation if nums contains at
 * least two elements.
 *
 * Return the minimum number of operations needed so that all elements of the
 * array are greater than or equal to k.
 *
 */
#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    int MinOperations(vector<int>& nums, int k) {
        // pass
        priority_queue<long long, vector<long long>, std::greater<>> q;
        for (auto& n : nums) {
            q.emplace(n);
        }

        int i = 0;
        for (; q.top() < k; i++) {
            auto n = q.top();
            q.pop();
            auto m = q.top();
            q.pop();

            q.emplace(min(n, m) * 2 + max(n, m));
        }
        return i;
    }
};
#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {2, 11, 10, 1, 3};
    int const k = 10;
    int const output = 2;
    Solution sl;
    int const ret = sl.MinOperations(nums, k);
    EXPECT_EQ(ret, output);
    // Explanation: In the first operation, we remove elements 1 and 2, then add
    // 1 * 2 + 2 to nums. nums becomes equal to [4, 11, 10, 3]. In the second
    // operation, we remove elements 3 and 4, then add 3 * 2 + 4 to nums. nums
    // becomes equal to [10, 11, 10]. At this stage, all the elements of nums
    // are greater than or equal to 10 so we can stop. It can be shown that 2 is
    // the minimum number of operations needed so that all elements of the array
    // are greater than or equal to 10.
}

TEST(t0, t2) {
    vector<int> nums = {1, 1, 2, 4, 9};
    int const k = 20;
    int const output = 4;
    Solution sl;
    int const ret = sl.MinOperations(nums, k);
    EXPECT_EQ(ret, output);
    /*
     * After one operation, nums becomes equal to [2, 4, 9, 3].
      After two operations, nums becomes equal to [7, 4, 9].
      After three operations, nums becomes equal to [15, 9].
      After four operations, nums becomes equal to [33].
      At this stage, all the elements of nums are greater than 20 so we can
      stop. It can be shown that 4 is the minimum number of operations needed so
      that all elements of the array are greater than or equal to 20.
      */
}

TEST(t0, t3) {
    vector<int> nums = {999999999, 999999999, 999999999};
    int const k = 1000000000;
    int const output = 2;
    Solution sl;
    int const ret = sl.MinOperations(nums, k);
    EXPECT_EQ(ret, output);
    /*
     * NOTE: long long
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
