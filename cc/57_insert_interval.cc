// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given an array of non-overlapping intervals intervals where
    intervals[i] = [starti, endi] represent the start and the end of the ith
    interval and intervals is sorted in ascending order by starti. You are also
    given an interval newInterval = [start, end] that represents the start and
    end of another interval.

    Insert newInterval into intervals such that intervals is still sorted in
    ascending order by starti and intervals still does not have any overlapping
    intervals (merge overlapping intervals if necessary).

    Return intervals after the insertion.
*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> Insert(vector<vector<int>>& intervals,
                               vector<int>& new_interval) {
        vector<vector<int>> ans;

        int start = new_interval.at(0), end = new_interval.at(1);

        int index = 0;

        // push element before overlap
        while (index < static_cast<int>(intervals.size()) && start > intervals.at(index).at(1)) {
            ans.push_back(intervals.at(index));
            index++;
        }

        // merge overlap
        while (index < static_cast<int>(intervals.size()) && end >= intervals.at(index).at(0)) {
            start = min(start, intervals.at(index).at(0));
            end = max(end, intervals.at(index).at(1));
            index++;
        }
        ans.push_back({start, end});

        // push element after overlap
        while (index < static_cast<int>(intervals.size())) {
            ans.push_back(intervals.at(index));
            index++;
        }

        return ans;
    }

    vector<vector<int>> InsertV1(vector<vector<int>>& intervals,
                                 vector<int>& new_interval) {
        vector<vector<int>> ans;

        int start = new_interval.at(0), end = new_interval.at(1);

        for (auto& interval : intervals) {
            if (interval.at(1) < start || end < interval.at(0)) {
                if (interval.at(1) < start) {  // push element before overlap
                    ans.push_back(interval);
                } else {  // push element after overlap
                    ans.push_back({start, end});
                    start = interval.at(0);
                    end = interval.at(1);
                }
            } else {  // merge overlap
                start = min(start, interval.at(0));
                end = max(end, interval.at(1));
            }
        }

        ans.push_back({start, end});

        return ans;
    }
};

TEST(insertV, t1) {
    vector<vector<int>> intervals = {{1, 3}, {6, 9}};
    vector<int> new_interval = {2, 5};
    vector<vector<int>> const output = {{1, 5}, {6, 9}};

    Solution sl;
    auto ret = sl.Insert(intervals, new_interval);
    EXPECT_EQ(ret, output);
}

TEST(insertV, t2) {
    vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> new_interval = {4, 8};
    vector<vector<int>> const output = {{1, 2}, {3, 10}, {12, 16}};

    // Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
    Solution sl;
    auto ret = sl.Insert(intervals, new_interval);
    EXPECT_EQ(ret, output);
}

}  // namespace
