// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i,
find the number of ways we can draw exactly k non-overlapping line segments such
that each segment covers two or more points. The endpoints of each segment must
have integral coordinates. The k line segments do not have to cover all n
points, and they are allowed to share endpoints.

Return the number of ways we can draw k non-overlapping line segments. Since
this number can be huge, return it modulo 109 + 7.
*/

/*
The problem looked like a typical 2-D DP problem to me.
Suppose we want to solve the problem for n points and k line segments. Then, we
can break it into following subproblems:

Don't choose the current point as the end point (i.e Don't make a line segment).
Then we are left with n-1 points and k segments. Choose the current point as the
left-end of the line segment (i.e We are going to construct a line segment).
Now, we have multiple choices for the length of the current line segment
(because left-end point is fixed, we can change right-end point to get different
length segments). So, now we have to solve the following subproblems: n-1 points
and k-1 segments n-2 points and k-1 segments n-3 points and k-1 segments
....
2 points and k-1 segments
The initial soultion I implemented did the part (2) using a for loop. This
solution would pass only 62/68 test cases. Now, we can optimize it further by
observing that there is lot of repetitive work being done in the for-loop for
(2). Take this example:
[(n,k) means solution of n points and k segments]
(6,3) reduces to (5,2) + (4,2) + (3,2) + (2,2). [This is only step 2]
(5,3) reduces to (4,2) + (3,2) + (2,2). [Again, this is only step 2]

So, now optimizing the for-loop is just another DP problem (a rather simple
one)!

Here's the implementation which runs in 188ms and passes all test cases.
*/

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
    int mod = 1e9 + 7;
    int SumDyp(int n, int k, vector<vector<int>> &dp,
               vector<vector<int>> &sum_dp) {
        if (n < 2) return 0;

        if (sum_dp[n][k] != -1) return sum_dp[n][k];

        sum_dp[n][k] = ((SumDyp(n - 1, k, dp, sum_dp) % mod) +
                        (Dyp(n, k, dp, sum_dp) % mod)) %
                       mod;
        return sum_dp[n][k];
    }

    int Dyp(int n, int k, vector<vector<int>> &dp,
            vector<vector<int>> &sum_dp) {
        if (n < 2) return 0;

        if (dp[n][k] != -1) return dp[n][k];

        if (k == 1) {
            dp[n][k] = ((((n - 1) % mod) * (n % mod)) % mod) / 2;
            return dp[n][k];
        }

        int ans1 = Dyp(n - 1, k, dp, sum_dp);
        int ans2 = SumDyp(n - 1, k - 1, dp, sum_dp);

        int ans = ((ans1 % mod) + (ans2 % mod)) % mod;
        dp[n][k] = ans;
        return ans;
    }

    int NumberOfSets(int n, int k) {
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, -1));
        vector<vector<int>> sum_dp(n + 1, vector<int>(k + 1, -1));
        return Dyp(n, k, dp, sum_dp);
    }
};

TEST(number_of_sets_of_k_non_overlapping_line_segments, t1) {
    int n = 4, k = 2;
    int output = 5;
    // Explanation: The two line segments are shown in red and blue.
    // The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)},
    // {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.

    Solution sl;
    int ret = sl.NumberOfSets(n, k);
    EXPECT_EQ(ret, output);
}

TEST(number_of_sets_of_k_non_overlapping_line_segments, t2) {
    int n = 3, k = 1;
    int output = 3;
    // Explanation: The 3 ways are {(0,1)}, {(0,2)}, {(1,2)}.
    // int output = 5;

    Solution sl;
    int ret = sl.NumberOfSets(n, k);
    EXPECT_EQ(ret, output);
}

TEST(number_of_sets_of_k_non_overlapping_line_segments, t3) {
    int n = 30, k = 7;
    int output = 796297179;
    // Explanation: The total number of possible ways to draw 7 line segments is
    // 3796297200. Taking this number modulo 109 + 7 gives us 796297179.

    Solution sl;
    int ret = sl.NumberOfSets(n, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
