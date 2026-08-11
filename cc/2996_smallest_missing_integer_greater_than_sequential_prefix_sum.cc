/*You are given a 0-indexed array of integers nums.
 *
 * A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j -
 * 1] + 1. In particular, the prefix consisting only of nums[0] is sequential.
 *
 * Return the smallest integer x missing from nums such that x is greater than
 * or equal to the sum of the longest sequential prefix.
 *
 *
 * */
#include <unordered_set>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    int MissingInteger(vector<int>& nums) {
        int start = nums[0];
        int i = 1;
        int size = nums.size();
        int expect = start + 1;
        while (i < size) {
            if (nums[i] != expect) {
                break;
            }
            i++;
            expect++;
        }

        int count = (start + expect - 1) * (expect - start) / 2;
        unordered_set<int> q(nums.begin(), nums.end());

        while (true) {
            if (q.find(count) == q.end()) {
                break;
            }
            count++;
        }

        return count;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(missingInteger, t0) {
    vector<int> nums{1, 2, 3, 2, 5};
    Solution sl;
    int output = 6;
    int ret = sl.MissingInteger(nums);
    /*
     * The longest sequential prefix of nums is [1,2,3] with a sum of 6. 6 is
     not in the array, therefore 6 is the smallest missing integer greater than
     or equal to the sum of the longest sequential prefix.

     * */
    EXPECT_EQ(output, ret);
}

TEST(missingInteger, t1) {
    vector<int> nums{3, 4, 5, 1, 12, 14, 13};
    Solution sl;
    int output = 15;
    int ret = sl.MissingInteger(nums);
    /*
     * The longest sequential prefix of nums is [3,4,5] with a sum of 12. 12,
     * 13, and 14 belong to the array while 15 does not. Therefore 15 is the
     * smallest missing integer greater than or equal to the sum of the longest
     * sequential prefix.

     * * */
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
