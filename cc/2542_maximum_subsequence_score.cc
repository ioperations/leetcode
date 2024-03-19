/*
 * You are given two 0-indexed integer arrays nums1 and nums2 of equal length n
and a positive integer k. You must choose a subsequence of indices from nums1 of
length k.

For chosen indices i0, i1, ..., ik - 1, your score is defined as:

    The sum of the selected elements from nums1 multiplied with the minimum of
the selected elements from nums2. It can defined simply as: (nums1[i0] +
nums1[i1] +...+ nums1[ik - 1]) * min(nums2[i0] , nums2[i1], ... ,nums2[ik - 1]).

Return the maximum possible score.

A subsequence of indices of an array is a set that can be derived from the set
{0, 1, ..., n-1} by deleting some or no elements.

*/

#include <algorithm>
#include <functional>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    long long MaxScore(vector<int> &nums1, vector<int> &nums2, int k) {
        /*
    n == nums1.length == nums2.length
    1 <= n <= 105
    0 <= nums1[i], nums2[j] <= 105
    1 <= k <= n
*/
        const int len = nums1.size();
        function<long long(int sum, int min, int current_size,
                           int current_index)>
            dfs = [&](int sum, int min, int current_size, int current_index) {
                if (current_index >= len) {
                    return 0;
                }

                sum += nums1[current_index];
                int z = 0;
                if ((current_size + 1) == k) {
                    z = sum * std::min(min, nums2[current_index]);
                }
                int choose_this_index =
                    dfs(sum, std::min(min, nums2[current_index]),
                        current_size + 1, current_index + 1);
                sum -= nums1[current_index];
                int do_not_choose_this_index =
                    dfs(sum, min, current_size, current_index + 1);

                return std::max(
                    z, max(choose_this_index, do_not_choose_this_index));
            };

        return dfs(0, 100000, 0, 0);
    }
};

TEST(maximum_subsequence_score, t1) {
    vector<int> nums1 = {1, 3, 3, 2};
    vector<int> nums2 = {2, 1, 3, 4};
    int k = 3;
    int output = 12;
    Solution sl;
    int ret = sl.MaxScore(nums1, nums2, k);
    EXPECT_EQ(ret, output);
    // Explanation:
    // The four possible subsequence scores are:
    // - We choose the indices 0, 1, and 2 with score = (1+3+3) * min(2,1,3)
    // = 7.
    // - We choose the indices 0, 1, and 3 with score = (1+3+2) * min(2,1,4)
    // = 6.
    // - We choose the indices 0, 2, and 3 with score = (1+3+2) * min(2,3,4)
    // = 12.
    // - We choose the indices 1, 2, and 3 with score = (3+3+2) * min(1,3,4)
    // = 8. Therefore, we return the max score, which is 12.
}

TEST(maximum_subsequence_score, t2) {
    vector<int> nums1 = {4, 2, 3, 1, 1};
    vector<int> nums2 = {7, 5, 10, 9, 6};
    int k = 1;
    int output = 30;
    Solution sl;
    int ret = sl.MaxScore(nums1, nums2, k);
    EXPECT_EQ(ret, output);
    // Explanation:
    // Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the
    // maximum possible score.
}

/*
// timeout
TEST(maximum_subsequence_score, t3) {
    vector<int> nums1 = {93,   463,  179,  2488, 619,  2006, 1561, 137,  53,
                         1765, 2304, 1459, 1768, 450,  1938, 2054, 466,  331,
                         670,  1830, 1550, 1534, 2164, 1280, 2277, 2312, 1509,
                         867,  2223, 1482, 2379, 1032, 359,  1746, 966,  232,
                         67,   1203, 2474, 944,  1740, 1775, 1799, 1156, 1982,
                         1416, 511,  1167, 1334, 2344};
    ;
    vector<int> nums2 = {345,  229,  976,  2086, 567,  726,  1640, 2451, 1829,
                         77,   1631, 306,  2032, 2497, 551,  2005, 2009, 1855,
                         1685, 729,  2498, 2204, 588,  474,  693,  30,   2051,
                         1126, 1293, 1378, 1693, 1995, 2188, 1284, 1414, 1618,
                         2005, 1005, 1890, 30,   895,  155,  526,  682,  2454,
                         278,  999,  1417, 1682, 995};
    int k = 42;
    int output = 30;
    Solution sl;
    int ret = sl.MaxScore(nums1, nums2, k);
    EXPECT_EQ(ret, output);
    // Explanation:
    // Choosing index 2 is optimal: nums1[2] * nums2[2] = 3 * 10 = 30 is the
    // maximum possible score.
}
*/

}  // namespace
