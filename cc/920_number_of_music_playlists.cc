/*
 * Your music player contains n different songs. You want to listen to goal
 * songs (not necessarily different) during your trip. To avoid boredom, you
 * will create a playlist so that:
 *     * Every song is played at least once.
 *     * A song can only be played again only if k other songs have been played.
 *
 * Given n, goal, and k, return the number of possible playlists that you can
 * create. Since the answer can be very large, return it modulo 109 + 7.
 */

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

#define ll long long

using namespace std;

namespace {
class Solution {
   public:
    ll Solve(int n, int goal, int k, vector<vector<int>> &dp) {
        if (n == 0 && goal == 0) return 1;
        if (n == 0 || goal == 0) return 0;
        if (dp[n][goal] != -1) return dp[n][goal];
        ll pick = Solve(n - 1, goal - 1, k, dp) * n;
        ll notpick = Solve(n, goal - 1, k, dp) * max(n - k, 0);
        return dp[n][goal] = (pick + notpick) % mod;
    }

    int NumMusicPlaylists(int n, int goal, int k) {
        /*
         * The goal is to find the number of distinct playlists of length goal
        that can be created using n different songs, with the constraint that
        the same song cannot appear in consecutive positions in the playlist,
        and there should be at least k songs between any two occurrences of the
        same song. The function numMusicPlaylists takes three parameters: n
        (number of songs), goal (length of the playlist), and k (minimum number
        of songs between repeated songs). It uses dynamic programming to find
        the answer efficiently. The solve function is a recursive helper
        function that calculates the number of valid playlists of length goal
        using n songs and satisfying the constraint of k. It uses memoization
        (dynamic programming) to avoid redundant calculations and improve
        efficiency. Approach:

        The base cases of the recursive function solve are:

        If there are no songs left (n == 0) and the playlist length is also zero
        (goal
        == 0), we have found a valid playlist, so return 1. If there are no
        songs left (n == 0) but the playlist length is still greater than zero
        (goal > 0), or vice versa, it is not possible to create a valid
        playlist, so return 0. If the value of dp[n][goal] is already calculated
        (not equal to -1), return it. This is the memoization step to avoid
        redundant calculations. The main recursive steps: pick: We choose a song
        for the current position in the playlist. There are n choices for the
        first position, n - 1 for the second, and so on. So, we multiply solve(n
        - 1, goal - 1, k, dp) by n to count all valid playlists when we pick a
        song for the current position. notpick: We do not choose a song for the
        current position. In this case, we can select any song from the
        remaining max(n - k, 0) songs (to ensure there are at least k songs
        between repeated songs). So, we multiply solve(n, goal - 1, k, dp) by
        max(n - k, 0). Finally, we return the result of the recursive
        calculation and store it in dp[n][goal] for future use.
        */
        vector<vector<int>> dp(n + 1, vector<int>(goal + 1, -1));
        return Solve(n, goal, k, dp);
    }
    const int mod = 1000000007;
};

TEST(number_of_music_playlists, t1) {
    Solution s;
    // There are 6 possible playlists: [1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3,
    // 1], [3, 1, 2], and [3, 2, 1].
    EXPECT_EQ(s.NumMusicPlaylists(3, 3, 1), 6);
}

TEST(number_of_music_playlists, t2) {
    Solution s;
    // There are 6 possible playlists: [1, 1, 2], [1, 2, 1], [2, 1, 1], [2, 2,
    // 1], [2, 1, 2], and [1, 2, 2].
    EXPECT_EQ(s.NumMusicPlaylists(2, 3, 0), 6);
}

TEST(number_of_music_playlists, t3) {
    Solution s;
    // There are 2 possible playlists: [1, 2, 1] and [2, 1, 2].
    EXPECT_EQ(s.NumMusicPlaylists(2, 3, 1), 2);
}

}  // namespace
