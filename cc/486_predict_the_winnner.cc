// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an integer array nums. Two players are playing a game with this
array: player 1 and player 2.

Player 1 and player 2 take turns, with player 1 starting first. Both players
start the game with a score of 0. At each turn, the player takes one of the
numbers from either end of the array (i.e., nums[0] or nums[nums.length - 1])
which reduces the size of the array by 1. The player adds the chosen number to
their score. The game ends when there are no more elements in the array.

Return true if Player 1 can win the game. If the scores of both players are
equal, then player 1 is still the winner, and you should also return true. You
may assume that both players are playing optimally.
*/

#include <algorithm>
#include <array>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool Ok(vector<int>& nums, int i, int j, int score, bool chance) {
        if (i > j) {
            return score >= 0;
        }
        bool ans = false;
        if (chance) {
            ans |= Ok(nums, i + 1, j, score + nums.at(i), false);
            ans |= Ok(nums, i, j - 1, score + nums.at(j), false);
        } else {
            ans = true;
            ans &= Ok(nums, i + 1, j, score - nums.at(i), true);
            ans &= Ok(nums, i, j - 1, score - nums.at(j), true);
        }

        return ans;
    }

    bool PredictTheWinner(vector<int>& nums) {
        return Ok(nums, 0, static_cast<int>(nums.size()) - 1, 0, true);
    }

std::array<std::array<std::array<int, 2>, 21>, 21> m_dp;

     int Ok(vector<int>& nums, int i, int j, int chance) {
         // Base case
         if (i > j) {
             return 0;
         }

         if (m_dp.at(i).at(j).at(chance) != -1) {
             return m_dp.at(i).at(j).at(chance);
         }

         int ans = 0;
         if (chance != 0) {
             ans = max(Ok(nums, i + 1, j, static_cast<int>(1 - chance)) + nums.at(i),
                       Ok(nums, i, j - 1, static_cast<int>(1 - chance)) + nums.at(j));
         } else {
             ans = min(Ok(nums, i + 1, j, static_cast<int>(1 - chance)) - nums.at(i),
                       Ok(nums, i, j - 1, static_cast<int>(1 - chance)) - nums.at(j));
         }

         return m_dp.at(i).at(j).at(chance) = ans;
     }

     bool PredictTheWinnerV2(vector<int>& nums) {
         for (auto& row : m_dp) {
             for (auto& col : row) {
                 col.fill(-1);
             }
         }
         int const res = Ok(nums, 0, static_cast<int>(nums.size()) - 1, 1);

         return res >= 0;
     }
};

TEST(PredictTheWinnner, t1) {
    std::vector<int> nums = {1, 5, 2};
    bool const expected = false;
    /* Explanation: Initially, player 1 can choose between 1 and 2.
        If he chooses 2 (or 1), then player 2 can choose from 1 (or 2) and 5.
        If player 2 chooses 5, then player 1 will be left with 1 (or 2).
        So, final score of player 1 is 1 + 2 = 3,
        and player 2 is 5. Hence, player 1 will
        never be the winner and you need to return false.
    */

    Solution sl{};
    bool ret = sl.PredictTheWinner(nums);
    EXPECT_EQ(ret, expected);

    ret = sl.PredictTheWinnerV2(nums);
    EXPECT_EQ(ret, expected);
}

TEST(PredictTheWinnner, t2) {
    std::vector<int> nums = {1, 5, 233, 7};
    bool const expected = true;
    /*  Player 1 first chooses 1.
        Then player 2 has to choose between 5 and 7.
        No matter which number player 2 choose,
        player 1 can choose 233. Finally,
        player 1 has more score (234) than
        player 2 (12), so you need to return True
        representing player1 can win.
    */

    Solution sl{};
    bool ret = sl.PredictTheWinner(nums);
    EXPECT_EQ(ret, expected);

    ret = sl.PredictTheWinnerV2(nums);
    EXPECT_EQ(ret, expected);
}

}  // namespace
