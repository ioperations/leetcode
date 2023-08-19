// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
In the "100 game" two players take turns adding, to a running total, any integer
from 1 to 10. The player who first causes the running total to reach or exceed
100 wins.

What if we change the game so that players cannot re-use integers?

For example, two players might take turns drawing from a common pool of numbers
from 1 to 15 without replacement until they reach a total >= 100.

Given two integers maxChoosableInteger and desiredTotal, return true if the
first player to move can force a win, otherwise, return false. Assume both
players play optimally.
*/

#include <vector>
using namespace std;
namespace { 
class Solution {
   private:
    vector<vector<int>> dp;
    bool Backtrack(int curr, int &max_int, int &desire, int mask, int player) {
        if (dp[player][mask] != -1) {
            return dp[player][mask];
        }
        for (int i = 1; i <= max_int; i++) {
            int nmask = (1 << (i - 1));
            if ((mask & nmask) == 0) {
                if (curr + i >= desire or
                    !Backtrack(curr + i, max_int, desire, mask + nmask,
                               (player + 1) % 2)) {
                    return (dp[player][mask] = true);
                }
            }
        }
        return (dp[player][mask] = false);
    }

   public:
    bool CanIWin(int max_choosable_integer, int desired_total) {
        dp =
            vector<vector<int>>(2, vector<int>(1 << max_choosable_integer, -1));
        if (max_choosable_integer * (max_choosable_integer + 1) / 2 <
            desired_total) {
            return false;
        }
        int curr = 0, mask = 0;
        return Backtrack(curr, max_choosable_integer, desired_total, mask, 0);
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    int max_choosable_integerer = 10, desired_total = 11;
    bool expected = false;
    // Explanation:
    // No matter which integer the first player choose, the first player will
    // lose. The first player can choose an integer from 1 up to 10. If the
    // first player choose 1, the second player can only choose integers from 2
    // up to 10. The second player will win by choosing 10 and get a total = 11,
    // which is >= desiredTotal. Same with other integers chosen by the first
    // player, the second player will always win.

    Solution s;
    bool ret = s.CanIWin(max_choosable_integerer, desired_total);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t2) {
    int max_choosable_integer = 10, desired_total = 0;
    bool expected = true;

    Solution s;
    bool ret = s.CanIWin(max_choosable_integer, desired_total);
    EXPECT_EQ(ret, expected);
}

TEST(t0, t3) {
    int max_choosable_integer = 10, desired_total = 1;
    bool expected = true;

    Solution s;
    bool ret = s.CanIWin(max_choosable_integer, desired_total);
    EXPECT_EQ(ret, expected);
}

}
