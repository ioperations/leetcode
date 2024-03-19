// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/* Given an array of intervals where intervals[i] = [starti, endi], merge all
 * overlapping intervals, and return an array of the non-overlapping intervals
 * that cover all the intervals in the input.
 */

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>

#define TEST(a, b) TEST_CASE(#a, #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> Merge(vector<vector<int>> &intervals) {
        std::vector<std::vector<int>> ret = intervals;
        sort(ret.begin(), ret.end(),
             [](const std::vector<int> &a, const std::vector<int> &b) {
                 return a[0] < b[0];
             });
        for (int i = 0; i < (int)ret.size() - 1; i++) {
            if (ret[i][1] >= ret[i + 1][0]) {
                ret[i + 1][0] =
                    (ret[i + 1][0] > ret[i][0]) ? ret[i][0] : ret[i + 1][0];
                ret[i + 1][1] =
                    (ret[i + 1][1] > ret[i][1]) ? ret[i + 1][1] : ret[i][1];
                ret[i] = std::vector<int>{};
            }
        }
        ret.erase(
            std::remove_if(ret.begin(), ret.end(),
                           [](const std::vector<int> &v) { return v.empty(); }),
            ret.end());
        ret.shrink_to_fit();

        return ret;
    }
};

TEST(merge_intervals, t1) {
    std::vector<std::vector<int>> intervals = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}};
    std::vector<std::vector<int>> output = {{1, 6}, {8, 10}, {15, 18}};

    Solution sl;
    auto ret = sl.Merge(intervals);

    for (auto &ptr : ret) {
        for (auto &ptr2 : ptr) {
            std::cout << ptr2 << " ";
        }

        std::cout << std::endl;
    }

    std::cout << "###################" << std::endl;

    // Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into
    // [1,6].
}

TEST(merge_intervals, t2) {
    std::vector<std::vector<int>> intervals = {{1, 4}, {4, 5}};

    // Explanation: Intervals [1,4] and [4,5] are considered overlapping.
    std::vector<std::vector<int>> output = {{1, 5}};

    Solution sl;
    auto ret = sl.Merge(intervals);

    for (auto &ptr : ret) {
        for (auto &ptr2 : ptr) {
            std::cout << ptr2 << std::endl;
        }
    }

    // Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into
    // [1,6].
}

TEST(merge_intervals, t3) {
    std::vector<std::vector<int>> intervals = {{1, 4}, {2, 3}};

    // Explanation: Intervals [1,4] and [4,5] are considered overlapping.
    std::vector<std::vector<int>> output = {{1, 4}};

    Solution sl;
    auto ret = sl.Merge(intervals);

    for (auto &ptr : ret) {
        for (auto &ptr2 : ptr) {
            std::cout << ptr2 << std::endl;
        }
    }

    // Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into
    // [1,6].
}

}  // namespace
