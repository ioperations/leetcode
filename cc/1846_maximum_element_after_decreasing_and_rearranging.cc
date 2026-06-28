/**
 * You are given an array of positive integers arr. Perform some operations
 * (possibly none) on arr so that it satisfies these conditions:
 *
 * The value of the first element in arr must be 1.
 * The absolute difference between any 2 adjacent elements must be less than or
 * equal to 1. In other words, abs(arr[i] - arr[i - 1]) <= 1 for each i where 1
 * <= i < arr.length (0-indexed). abs(x) is the absolute value of x. There are 2
 * types of operations that you can perform any number of times:
 *
 * Decrease the value of any element of arr to a smaller positive integer.
 * Rearrange the elements of arr to be in any order.
 * Return the maximum possible value of an element in arr after performing the
 * operations to satisfy the conditions.
 *
 * 1 <= arr.length <= 105
 * 1 <= arr[i] <= 109
 *
 */
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;
namespace {

class Solution {
   public:
    int MaximumElementAfterDecrementingAndRearranging(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int ans = 1;

        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] >= ans + 1) {
                ans++;
            }
        }

        return ans;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(maximumElementAfterDecrementingAndRearranging, t0) {
    vector<int> arr = {2, 2, 1, 2, 1};
    int output = 2;
    Solution sl;
    int ret = sl.MaximumElementAfterDecrementingAndRearranging(arr);
    EXPECT_EQ(output, ret);
    // Explanation:
    // We can satisfy the conditions by rearranging arr so it becomes
    // [1,2,2,2,1]. The largest element in arr is 2.
}

TEST(maximumElementAfterDecrementingAndRearranging, t1) {
    vector<int> arr = {100, 1, 100};
    int output = 3;
    Solution sl;
    int ret = sl.MaximumElementAfterDecrementingAndRearranging(arr);
    EXPECT_EQ(output, ret);
    // Explanation:
    // ne possible way to satisfy the conditions is by doing the following:
    // 1. Rearrange arr so it becomes [1,100,1000].
    // 2. Decrease the value of the second element to 2.
    // 3. Decrease the value of the third element to 3.
    // Now arr = [1,2,3], which satisfies the conditions.
    // The largest element in arr is 3.
}

TEST(maximumElementAfterDecrementingAndRearranging, t2) {
    vector<int> arr = {1, 2, 3, 4, 5};
    int output = 5;
    Solution sl;
    int ret = sl.MaximumElementAfterDecrementingAndRearranging(arr);
    EXPECT_EQ(output, ret);
    // The array already satisfies the conditions, and the largest element is 5.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
