// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You want to schedule a list of jobs in d days. Jobs are dependent (i.e To work
on the ith job, you have to finish all the jobs j where 0 <= j < i).

You have to finish at least one task every day. The difficulty of a job schedule
is the sum of difficulties of each day of the d days. The difficulty of a day is
the maximum difficulty of a job done on that day.

You are given an integer array jobDifficulty and an integer d. The difficulty of
the ith job is jobDifficulty[i].

Return the minimum difficulty of a job schedule. If you cannot find a schedule
for the jobs return -1.*/

#include <algorithm>
#include <climits>
#include <iterator>
#include <limits>
#include <string>
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
    int MinDifficulty(vector<int> &job_difficulty, int d) {
        int const n = job_difficulty.size();
        job_difficulty.insert(job_difficulty.begin(), 0);
        vector<vector<int>> dp(n + 1, vector<int>(d + 1, INT_MAX / 2));

        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= min(i, d); k++) {
                int mx = job_difficulty[i];

                for (int j = i; j >= k; j--) {
                    mx = max(mx, job_difficulty[j]);
                    // dp[i][k] = min(dp[i][k], dp[j-1][k-1] +
                    // *max_element(jobDifficulty.begin() + j,
                    // jobDifficulty.begin() + i + 1));
                    dp[i][k] = min(dp[i][k], dp[j - 1][k - 1] + mx);
                }
            }
        }

        if (dp[n][d] >= INT_MAX / 2) return -1;
        return dp[n][d];
    }

    int Dfs(const vector<int> &jobs, int start_idx, int days_left,
            vector<vector<int>> &memo) {
        if (start_idx >= (int)jobs.size()) {
            return std::numeric_limits<int>::max();
        }

        if (days_left == 1) {
            return *max_element(begin(jobs) + start_idx, end(jobs));
        }

        if (memo[start_idx][days_left] != -1) {
            return memo[start_idx][days_left];
        }

        int state_value = std::numeric_limits<int>::max();
        int current_max = jobs[start_idx];
        for (int i = start_idx; i < (int)jobs.size(); ++i) {
            current_max = max(current_max, jobs[i]);
            int const next_state_value = Dfs(jobs, i + 1, days_left - 1, memo);
            if (next_state_value == std::numeric_limits<int>::max()) {
                continue;
            }

            state_value = min(state_value, next_state_value + current_max);
        }

        memo[start_idx][days_left] = state_value;

        return state_value;
    }

    int MinDifficultyV2(vector<int> &job_difficulty, int d) {
        vector<vector<int>> memo(job_difficulty.size(), vector<int>(d + 1, -1));

        int const result = Dfs(job_difficulty, 0, d, memo);

        return result == std::numeric_limits<int>::max() ? -1 : result;
    }
};

TEST(minimum_difficulty_of_a_job_schedule, t1) {
    vector<int> job_difficulty = {6, 5, 4, 3, 2, 1};
    int const d = 2;
    int const output = 7;
    /*
    Explanation: First day you can finish the first 5 jobs, total difficulty
    = 6. Second day you can finish the last job, total difficulty = 1. The
    difficulty of the schedule = 6 + 1 = 7
    */

    Solution sl;
    int const ret = sl.MinDifficulty(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

TEST(minimum_difficulty_of_a_job_schedule, t2) {
    vector<int> job_difficulty = {9, 9, 9};
    int const d = 4;
    int const output = -1;
    /*
     If you finish a job per day you will still have a free day. you cannot find
     a schedule for the given jobs.
    */

    Solution sl;
    int const ret = sl.MinDifficulty(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

TEST(minimum_difficulty_of_a_job_schedule, t3) {
    vector<int> job_difficulty = {1, 1, 1};
    int const d = 3;
    int const output = 3;
    /*
    The schedule is one job per day. total difficulty will be 3.
    */

    Solution sl;
    int const ret = sl.MinDifficulty(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

TEST(minimum_difficulty_of_a_job_schedule_v2, t1) {
    vector<int> job_difficulty = {6, 5, 4, 3, 2, 1};
    int const d = 2;
    int const output = 7;
    /*
    Explanation: First day you can finish the first 5 jobs, total difficulty
    = 6. Second day you can finish the last job, total difficulty = 1. The
    difficulty of the schedule = 6 + 1 = 7
    */

    Solution sl;
    int const ret = sl.MinDifficultyV2(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

TEST(minimum_difficulty_of_a_job_schedule_v2, t2) {
    vector<int> job_difficulty = {9, 9, 9};
    int const d = 4;
    int const output = -1;
    /*
     If you finish a job per day you will still have a free day. you cannot find
     a schedule for the given jobs.
    */

    Solution sl;
    int const ret = sl.MinDifficultyV2(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

TEST(minimum_difficulty_of_a_job_schedule_v2, t3) {
    vector<int> job_difficulty = {1, 1, 1};
    int const d = 3;
    int const output = 3;
    /*
    The schedule is one job per day. total difficulty will be 3.
    */

    Solution sl;
    int const ret = sl.MinDifficultyV2(job_difficulty, d);
    EXPECT_EQ(output, ret);
}

}  // namespace
