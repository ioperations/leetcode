// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*We have n jobs, where every job is scheduled to be done from startTime[i] to
endTime[i], obtaining a profit of profit[i]. You're given the startTime, endTime
and profit arrays, return the maximum profit you can take such that there are no
two jobs in the subset with overlapping time range. If you choose a job that
ends at time X you will be able to start another job that starts at time X.
*/
#include <algorithm>
#include <map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    void SortByStartTime(vector<int>& start_time, vector<int>& end_time,
                         vector<int>& profit) {
        vector<vector<int>> tmp;
        tmp.reserve(start_time.size());
        for (int i = 0; i < static_cast<int>(start_time.size()); i++) {
          tmp.push_back({start_time.at(i), end_time.at(i), profit.at(i)});
        }
        sort(tmp.begin(), tmp.end());
        for (int i = 0; i < static_cast<int>(start_time.size()); i++) {
            start_time.at(i) = tmp.at(i).at(0);
            end_time.at(i) = tmp.at(i).at(1);
            profit.at(i) = tmp.at(i).at(2);
        }
    }

   public:
    int JobScheduling(vector<int>& start_time, vector<int>& end_time,
                      vector<int>& profit) {
        SortByStartTime(start_time, end_time, profit);
        map<int, int> time_profit;  // dp, timeProfit[i]: maximum profit if we
                                    // schedule job from timepoint i
        int res = 0;
        for (int i = static_cast<int>(start_time.size()) - 1; i >= 0; i--) {
            auto iter = time_profit.lower_bound(end_time.at(i));
            int const val =
                (iter == time_profit.end() ? 0 : iter->second) + profit.at(i);
            time_profit[start_time.at(i)] = max(time_profit[start_time.at(i)], val);
            time_profit[start_time.at(i)] = max(time_profit[start_time.at(i)], res);
            res = time_profit[start_time.at(i)];
        }
        return res;
    }
};

TEST(MaximumProfitInJobScheduling, t1) {
    vector<int> start_time = {1, 2, 3, 3}, end_time = {3, 4, 5, 6},
                profit = {50, 10, 40, 70};
    int const output = 120;
    /*
    Explanation: The subset chosen is the first and fourth job.
    Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
    */
    Solution sl;
    int const ret = sl.JobScheduling(start_time, end_time, profit);
    EXPECT_EQ(ret, output);
}

TEST(MaximumProfitInJobScheduling, t2) {
    vector<int> start_time = {1, 2, 3, 4, 6}, end_time = {3, 5, 10, 6, 9},
                profit = {20, 20, 100, 70, 60};
    int const output = 150;
    // Explanation: The subset chosen is the first, fourth and fifth job.
    // Profit obtained 150 = 20 + 70 + 60.
    /*
    Explanation: The subset chosen is the first and fourth job.
    Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
    */
    Solution sl;
    int const ret = sl.JobScheduling(start_time, end_time, profit);
    EXPECT_EQ(ret, output);
}

TEST(MaximumProfitInJobScheduling, t3) {
    vector<int> start_time = {1, 1, 1}, end_time = {2, 3, 4},
                profit = {5, 6, 4};
    int const output = 6;
    // Explanation: The subset chosen is the first, fourth and fifth job.
    // Profit obtained 150 = 20 + 70 + 60.
    /*
    Explanation: The subset chosen is the first and fourth job.
    Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
    */
    Solution sl;
    int const ret = sl.JobScheduling(start_time, end_time, profit);
    EXPECT_EQ(ret, output);
}

}  // namespace
