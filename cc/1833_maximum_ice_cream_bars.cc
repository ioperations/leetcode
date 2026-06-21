/**
 * It is a sweltering summer day, and a boy wants to buy some ice cream bars.
 *
 * At the store, there are n ice cream bars. You are given an array costs of
 * length n, where costs[i] is the price of the ith ice cream bar in coins. The
 * boy initially has `coins` coins to spend, and he wants to buy as many ice
 * cream bars as possible.
 *
 * Note: The boy can buy the ice cream bars in any order.
 *
 * Return the maximum number of ice cream bars the boy can buy with coins coins.
 *
 * You must solve the problem by counting sort.
 *
 * costs.length == n
 * 1 <= n <= 105
 * 1 <= costs[i] <= 105
 * 1 <= coins <= 108
 *
 */
#include <algorithm>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    int MaxIceCream(vector<int>& costs, int coins) {
        sort(costs.begin(), costs.end(), std::less<>());
        int count = 0;
        for (auto& p : costs) {
            if (p <= coins) {
                coins -= p;
                count++;
            } else {
                break;
            }
        }
        return count;
    }
};
}  // namespace
#include <gtest/gtest.h>

TEST(maxIceCream, t0) {
    vector<int> costs = {1, 3, 2, 4, 1};
    int coins = 7;
    int output = 4;
    Solution sl;
    auto ret = sl.MaxIceCream(costs, coins);
    EXPECT_EQ(output, ret);
    // Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a
    // total price of 1 + 3 + 2 + 1 = 7.
}

TEST(maxIceCream, t1) {
    vector<int> costs = {10, 6, 8, 7, 7, 8};
    int coins = 5;
    int output = 0;
    Solution sl;
    auto ret = sl.MaxIceCream(costs, coins);
    EXPECT_EQ(output, ret);
    // The boy cannot afford any of the ice cream bars.
}

TEST(maxIceCream, t2) {
    vector<int> costs = {1, 6, 3, 1, 2, 5};
    int coins = 20;
    int output = 6;
    Solution sl;
    auto ret = sl.MaxIceCream(costs, coins);
    EXPECT_EQ(output, ret);
    // The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1
    // + 2 + 5 = 18.
}
