// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
     You are given an array of positive integers nums and want to erase a
   subarray containing unique elements. The score you get by erasing the
   subarray is equal to the sum of its elements.

     Return the maximum score you can get by erasing exactly one subarray.

     An array b is called to be a subarray of a if it forms a contiguous
   subsequence of a, that is, if it is equal to a[l],a[l+1],...,a[r] for some
   (l,r).
*/
#include <algorithm>
#include <unordered_map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int MaximumUniqueSubarray(vector<int> &nums) {
        //	Initially we will keep our i and j pointer at index 0
        //	keep moving j and add the current no to sum and
        //	also add the curr no to map
        //	at each step update the ans
        //  whenever any element comes which is already in map
        //  then start increasing i pointer and erase nums[i]
        //  from map and also subtract it from sum
        unordered_map<int, int> m;
        int sum = 0, ans = 0;
        int i = 0, j = 0, n = nums.size();
        while (j < n) {
            sum += nums[j];
            while (m.find(nums[j]) != m.end()) {
                sum -= nums[i];
                m.erase(nums[i]);
                i++;
            }
            m[nums[j]]++;
            ans = max(ans, sum);
            j++;
        }
        return ans;
    }
};

TEST(maximium_erasure_value, t1) {
    vector<int> nums = {4, 2, 4, 5, 6};

    int out = 17;
    Solution sl;
    int ret = sl.MaximumUniqueSubarray(nums);
    // The optimal subarray here is [2,4,5,6].
    EXPECT_EQ(ret, out);
}

TEST(maximium_erasure_value, t2) {
    vector<int> nums = {5, 2, 1, 2, 5, 2, 1, 2, 5};

    int out = 8;
    Solution sl;
    int ret = sl.MaximumUniqueSubarray(nums);
    // The optimal subarray here is [5,2,1] or [1,2,5].
    EXPECT_EQ(ret, out);
}

}  // namespace
