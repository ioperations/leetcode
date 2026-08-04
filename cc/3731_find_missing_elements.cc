/*
 *  You are given an integer array nums consisting of unique integers.
 *
 * Originally, nums contained every integer within a certain range. However,
 * some integers might have gone missing from the array.
 *
 * The smallest and largest integers of the original range are still present in
 * nums.
 *
 * Return a sorted list of all the missing integers in this range. If no
 * integers are missing, return an empty list.
 * 2 <= nums.length <= 100
 * 1 <= nums[i] <= 100
 *  *
 * */
#include <algorithm>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    vector<int> FindMissingElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<int> ret;

        int start = nums[0];
        auto size = nums.size();

        int expect = start;
        for (int i = 0; i < size;) {
            if (nums[i] != expect) {
                ret.emplace_back(expect);
                expect++;
                continue;
            }

            expect++;
            i++;
        }
        return ret;
    }
};
}  // namespace
#include <gtest/gtest.h>

TEST(findMissingElements, t0) {
    vector<int> nums = {1, 4, 2, 5};

    vector<int> output = {3};

    /*
     * Explanation:
     * The smallest integer is 1 and the largest is 5, so the full
     * range should be [1,2,3,4,5]. Among these, only 3 is missing.
     */
    Solution sl;
    auto ret = sl.FindMissingElements(nums);
    EXPECT_EQ(output, ret);
}

TEST(findMissingElements, t1) {
    vector<int> nums = {7, 8, 6, 9};

    vector<int> output = {};

    /*
     * Explanation:
     * The smallest integer is 6 and the largest is 9, so the full
     * range is [6,7,8,9]. All integers are already present,
     * so no integer is missing.
     */
    Solution sl;
    auto ret = sl.FindMissingElements(nums);
    EXPECT_EQ(output, ret);
}

TEST(findMissingElements, t2) {
    vector<int> nums = {5, 1};

    vector<int> output = {2, 3, 4};

    /*
     * The smallest integer is 1 and the largest is 5, so the full
     * range should be [1,2,3,4,5]. The missing integers are 2, 3, and 4
     */
    Solution sl;
    auto ret = sl.FindMissingElements(nums);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
