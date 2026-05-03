// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an integer array prices where prices[i] is the price of a given
stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k
transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must
sell the stock before you buy again).*/

#include <algorithm>
#include <climits>
#include <functional>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int MaxProfit(int k, vector<int>& prices) {
        // no transaction, no profit
        if (k == 0) return 0;
        // dp[k][0] = min cost you need to spend at most k transactions
        // dp[k][1] = max profit you can achieve at most k transactions
        vector<vector<int>> dp(k + 1, vector<int>(2));
        for (int i = 0; i <= k; i++) dp.at(i).at(0) = INT_MAX;
        for (auto& price : prices) {
            for (int i = 1; i <= k; i++) {
                dp.at(i).at(0) = std::min(dp.at(i).at(0), price - dp.at(i - 1).at(1));
                dp.at(i).at(1) = std::max(dp.at(i).at(1), price - dp.at(i).at(0));
            }
        }
        return dp.at(k).at(1);
    }

    int MaxProfitV1(int k, vector<int>& prices) {
        int const size = static_cast<int>(prices.size());

        /// @param action bool Buy
        ///        action false sell
        function<int(int, bool, int, int)> fun =
            [&](int day, bool next_action, int value, int k_times) -> int {
            if ((next_action && k_times <= 0) || (day >= size)) {
                return value;
            }
            // 选择不采取这个动作 买/卖, 在下一天决定
            int const v1 = fun(day + 1, next_action, value, k_times);
            // 选择采取这个动作 买/卖 今天就买/卖
            int const v2 = fun(
                day + 1, !next_action,
                next_action ? (value - (prices.at(day))) : (value + (prices.at(day))),
                next_action ? (k_times) : --k_times);

            return max(v1, v2);
        };
        return fun(0, true, 0, k);
    }
};

TEST(BestTimeToBuyAndSellStockIv, t1) {
    int const k = 2;
    vector<int> prices = {2, 4, 1};
    int const output = 2;
    // Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4),
    // profit = 4-2 = 2.
    Solution sl;
    int const ret = sl.MaxProfit(k, prices);
    EXPECT_EQ(ret, output);
}

TEST(BestTimeToBuyAndSellStockIv, t2) {
    int const k = 2;
    vector<int> prices = {3, 2, 6, 5, 0, 3};
    int const output = 7;
    // Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4.
    // Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0
    // = 3.
    Solution sl;
    int const ret = sl.MaxProfit(k, prices);
    EXPECT_EQ(ret, output);
}

TEST(BestTimeToBuyAndSellStockIv, t3) {
    int const k = 2;
    vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};
    int const output = 6;
    Solution sl;
    int const ret = sl.MaxProfit(k, prices);
    EXPECT_EQ(ret, output);
}

TEST(BestTimeToBuyAndSellStockIv, t4) {
    int const k = 7;
    vector<int> prices = {48, 12, 60, 93, 97, 42, 25, 64, 17, 56,
                          85, 93, 9,  48, 52, 42, 58, 85, 81, 84,
                          69, 36, 1,  54, 23, 15, 72, 15, 11, 94};
    int const output = 469;
    Solution sl;
    int const ret = sl.MaxProfit(k, prices);
    EXPECT_EQ(ret, output);
}

}  // namespace
