/*
 *
 * Given an array intervals where intervals[i] = [li, ri] represent the
 * interval
 * [li, ri), remove all intervals that are covered by another interval in the
 * list.
 *
 * The interval [a, b) is covered by the interval [c, d) if and only if c <= a
 * and b <= d.
 *
 * Return the number of remaining intervals.
 * 1 <= intervals.length <= 1000
 * intervals[i].length == 2
 * 0 <= li < ri <= 105
 * All the given intervals are unique.
 */

#include <algorithm>
#include <vector>

using namespace std;
namespace {
class Solution {
   public:
    int RemoveCoveredIntervals(vector<vector<int>>& intervals) {
        int size = intervals.size();
        int remain = size;

        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& left, const vector<int>& right) {
                 if (left[0] < right[0]) {
                     return true;
                 } else if (left[0] == right[0]) {
                     return left[1] > right[1];
                 }
                 return false;
             });

        int left = 0;
        int right = 0;

        while (right < size) {
            right++;
            if (right >= size) {
                break;
            }

            if (intervals[right][1] > intervals[left][1]) {
                left = right;
            } else {
                remain--;
            }
        }
        return remain;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(removeCoveredIntervals, t1) {
    vector<vector<int>> intervals = {{1, 4}, {3, 6}, {2, 8}};
    int output = 2;
    // Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
    Solution sl;
    int ret = sl.RemoveCoveredIntervals(intervals);
    EXPECT_EQ(output, ret);
}

TEST(removeCoveredIntervals, t2) {
    vector<vector<int>> intervals = {{1, 4}, {3, 6}, {2, 8}};
    int output = 2;
    // Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
    Solution sl;
    int ret = sl.RemoveCoveredIntervals(intervals);
    EXPECT_EQ(output, ret);
}
TEST(removeCoveredIntervals, t3) {
    vector<vector<int>> intervals = {{1, 2}, {1, 4}, {3, 4}};
    int output = 1;
    // Explanation: Interval [3,6] is covered by [2,8], therefore it is removed.
    Solution sl;
    int ret = sl.RemoveCoveredIntervals(intervals);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
