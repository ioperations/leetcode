// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an array prices where prices[i] is the price of a given stock on
the ith day.

You want to maximize your profit by choosing a single day to buy one stock and
choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot
achieve any profit, return 0.
*/

#include <stddef.h>

#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    int MaxProfit(vector<int> &prices) {
        // pass

        int max = 0;
        for (size_t i = 1; i < prices.size(); i++) {
            for (size_t j = 0; j < i; j++) {
                max = (prices[i] - prices[j]) > max ? (prices[i] - prices[j])
                                                    : max;
            }
        }
        return max;
    }

    int MaxProfitV2(vector<int> &prices) {
        int max_price = -1;
        int max_profit = 0;
        for (int i = prices.size() - 1; i >= 0; i--) {
            if (prices[i] > max_price) max_price = prices[i];
            int profit = max_price - prices[i];
            if (profit > max_profit) max_profit = profit;
        }
        return max_profit;
    }
};

TEST(best_time_to_buy_and_sell_stock, t1) {
    std::vector<int> prices = {7, 1, 5, 3, 6, 4};
    int expected = 5;
    // Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6),
    // profit = 6-1 = 5. Note that buying on day 2 and selling on day 1 is not
    // allowed because you must buy before you sell.

    Solution s;
    int ret = s.MaxProfit(prices);

    EXPECT_EQ(ret, expected);
}

TEST(best_time_to_buy_and_sell_stock, t2) {
    std::vector<int> prices = {7, 6, 4, 3, 1};
    int expected = 0;
    // In this case, no transactions are done and the max profit = 0.
    Solution s;
    int ret = s.MaxProfit(prices);

    EXPECT_EQ(ret, expected);
}

}  // namespace
