/*
 * There are several consecutive houses along a street, each of which has some
 * money inside. There is also a robber, who wants to steal money from the
 * homes, but he refuses to steal from adjacent homes.
 *
 * The capability of the robber is the maximum amount of money he steals from
 * one house of all the houses he robbed.
 *
 * You are given an integer array nums representing how much money is stashed in
 * each house. More formally, the ith house from the left has nums[i] dollars.
 *
 * You are also given an integer k, representing the minimum number of houses
 * the robber will steal from. It is always possible to steal at least k houses.
 *
 * Return the minimum capability of the robber out of all the possible ways to
 * steal at least k houses.
 */

#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

class Solution {
   public:
    Solution() {}
    ~Solution() {}

   public:
    int minCapability(vector<int>& nums, int k) {
        /*
         * 1 <= nums.length <= 105
         * 1 <= nums[i] <= 109
         * 1 <= k <= (nums.length + 1)/2
         */
        this->k = k;
        this->nums = nums;
        this->size = nums.size();

        int min = INT_MAX;
        int max = INT_MIN;
        for (int i = 0; i < size; i++) {
            Q(min, max, 0, i);
        }
        return min;
    }

   private:
    bool Q(int& min, int& Max, int got = 0, int i = 0) {
        if (got == k) {
            return true;
        }

        if (i >= size) {
            return false;
        }

        bool ok = false;
        int m = max(Max, nums[i]);
        int q = INT_MAX;
        if (Q(min, m, got + 1, i + 2)) {
            min = std::min(min, m);
            q = std::max(Max, m);
            ok = true;
        }

        int n = INT_MAX;
        if (Q(min, Max, got, i + 1)) {
            min = std::min(min, m);
            n = Max;
            ok = true;
        }

        Max = std::max(Max, std::min(q, n));
        return ok;
    }

   private:
    int k = 0;
    vector<int> nums;
    size_t size = 0;
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums{2, 3, 5, 9};
    int k = 2;
    int output = 5;
    Solution sl;
    int ret = sl.minCapability(nums, k);
    EXPECT_EQ(ret, output);
    /*
     * There are three ways to rob at least 2 houses:
     * - Rob the houses at indices 0 and 2. Capability is max(nums[0], nums[2])
     * = 5.
     * - Rob the houses at indices 0 and 3. Capability is max(nums[0], nums[3])
     * = 9.
     * - Rob the houses at indices 1 and 3. Capability is max(nums[1], nums[3])
     * = 9. Therefore, we return min(5, 9, 9) = 5.
     */
}

TEST(t0, t2) {
    vector<int> nums{2, 7, 9, 3, 1};
    int k = 2;
    int output = 2;
    Solution sl;
    int ret = sl.minCapability(nums, k);
    EXPECT_EQ(ret, output);
    /*
     * There are 7 ways to rob the houses. The way which leads to minimum
     * capability is to rob the house at index 0 and 4. Return max(nums[0],
     * nums[4]) = 2.
     */
}

// TEST(t0, t3) {
//     vector<int> nums{5038, 3053, 2825, 3638, 4648, 3259, 4948, 4248, 4940,
//     2834,
//                      109,  5224, 5097, 4708, 2162, 3438, 4152, 4134, 551,
//                      3961, 2294, 3961, 1327, 2395, 1002, 763,  4296, 3147,
//                      5069, 2156, 572,  1261, 4272, 4158, 5186, 2543, 5055,
//                      4735, 2325, 1206, 1019, 1257, 5048, 1563, 3507, 4269,
//                      5328, 173,  5007, 2392, 967,  2768, 86,   3401, 3667,
//                      4406, 4487, 876,  1530, 819, 1320, 883,  1101, 5317,
//                      2305, 89,   788,  1603, 3456, 5221, 1910, 3343, 4597};
//     int k = 28;
//     int output = 2;
//     Solution sl;
//     int ret = sl.minCapability(nums, k);
//     EXPECT_EQ(ret, output);
//     /*
//      * There are 7 ways to rob the houses. The way which leads to minimum
//      * capability is to rob the house at index 0 and 4. Return max(nums[0],
//      * nums[4]) = 2.
//      */
// }

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
