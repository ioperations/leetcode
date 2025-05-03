
/*
 * You are given a 0-indexed integer array nums. A pair of indices (i, j) is a
 * bad pair if i < j and j - i != nums[j] - nums[i].
 *
 * Return the total number of bad pairs in nums.
 */

#include <cstddef>
#include <vector>
using namespace std;

class Solution {
   public:
    long long CountBadPairs(vector<int>& nums) {
      // FIXME: timeout
      long long ret = 0;
      auto size = nums.size();
      for (size_t i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
          if (nums[j] - nums[i] != (j - i)) {
            ret++;
          }
        }
      }

      return ret;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {4, 1, 3, 3};
    int const output = 5;
    Solution sl;
    int const ret = sl.CountBadPairs(nums);
    EXPECT_EQ(ret, output);
    /*
     * Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
     * The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
     * The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
     * The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
     * The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
     * There are a total of 5 bad pairs, so we return 5.
     */
}

TEST(t0, t2) {
    vector<int> nums = {1, 2, 3, 4, 5};
    int const output = 0;
    Solution sl;
    int const ret = sl.CountBadPairs(nums);
    EXPECT_EQ(ret, output);
    // Explanation : There are no bad pairs.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
