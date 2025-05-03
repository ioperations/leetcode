/*
 * You are given an array nums consisting of positive integers.
 * We call a subarray of an array complete if the following condition is
 * satisfied: The number of distinct elements in the subarray is equal to the
 * number of distinct elements in the whole array. Return the number of complete
 * subarrays. A subarray is a contiguous non-empty part of an array.
 */
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    int CountCompleteSubarrays(vector<int>& nums) {
      /*
       * 1 <= nums.length <= 1000
       * 1 <= nums[i] <= 2000
       */
      int k = unordered_set<int>(nums.begin(), nums.end()).size(), res = 0;
      for (int i = 0; i < nums.size(); i++) {
        unordered_set<int> st;
        for (int j = i; j < nums.size(); j++) {
          st.insert(nums[j]);
          if (st.size() == k) res++;
        }
      }
      return res;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums{1, 3, 1, 2, 2};
    int const output = 4;
    Solution sl;
    int const ret = sl.CountCompleteSubarrays(nums);
    EXPECT_EQ(ret, output);
    /*
     * The complete subarrays are the following: [1,3,1,2], [1,3,1,2,2], [3,1,2]
     * and [3,1,2,2].
     */
}

TEST(t0, t2) {
    vector<int> nums{5, 5, 5, 5};
    int const output = 10;
    Solution sl;
    int const ret = sl.CountCompleteSubarrays(nums);
    EXPECT_EQ(ret, output);
    /*
     * The array consists only of the integer 5, so any subarray is complete.
     * The number of subarrays that we can choose is 10.
     */
}
TEST(t0, t3) {
    vector<int> nums{1898, 370, 822, 1659, 1360, 128, 370, 360, 261, 1898};
    int const output = 4;
    Solution sl;
    int const ret = sl.CountCompleteSubarrays(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
