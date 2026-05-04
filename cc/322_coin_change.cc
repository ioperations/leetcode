// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an integer array coins representing coins of different
denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that
amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.


*/

#include <benchmark/benchmark.h>

#include <algorithm>
#include <climits>
#include <functional>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int CoinChange(std::vector<int>& coins, int amount) {
        // pass
        sort(coins.begin(), coins.end());

        std::map<int, int> cache;

        std::function<int(int)> fun = [&](int a) -> int {
            if (a == 0) {
                return 0;
            }
            if (cache.count(a)) {
                return cache.at(a);
            }

            int ret = -1;

            for (int i = static_cast<int>(coins.size()) - 1; i >= 0; i--) {
                if (coins.at(i) <= a) {
                    int const tmp = fun(a - coins.at(i));
                    cache[a - coins.at(i)] = tmp;

                    if (tmp != -1) {
                        ret = 1 + (ret == -1 ? tmp : std::min(ret - 1, tmp));
                    }
                } else {
                    break;
                }
            }

            return ret;
        };

        return fun(amount);
    }

    int CoinChangeV1(std::vector<int>& coins, int amount) {
        std::vector<int> h((amount + 1), INT_MAX - 1);
        h.at(0) = 0;
        for (int i = 0; i < static_cast<int>(h.size()); i++) {
            for (int const coin : coins) {
                if (i >= coin) {
                    h.at(i) = std::min(h.at(i), 1 + h.at(i - coin));
                }
            }
        }
        return (h.at(h.size() - 1) < INT_MAX - 1) ? h.at(h.size() - 1) : -1;
    }

    int CoinChangeV2(std::vector<int>& arr, int sum) {
        int const n = static_cast<int>(arr.size());

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(sum + 1));

        for (int i = 0; i <= n; i++) {
            dp.at(i).at(0) = 0;
        }

        for (int i = 0; i < sum + 1; i++) {
            dp.at(0).at(i) = INT_MAX - 1;
        }

        for (int i = 1; i <= sum; i++) {
            if (i % arr.at(0) == 0) {
                dp.at(1).at(i) = i / arr.at(0);
            } else {
                dp.at(1).at(i) = INT_MAX - 1;
            }
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                if (arr.at(i - 1) <= j) {
                    dp.at(i).at(j) = std::min(dp.at(i - 1).at(j), dp.at(i).at(j - arr.at(i - 1)) + 1);
                } else {
                    dp.at(i).at(j) = dp.at(i - 1).at(j);
                }
            }
        }

        if (dp.at(n).at(sum) == INT_MAX or dp.at(n).at(sum) == INT_MAX - 1) {
            return -1;
        }

        return dp.at(n).at(sum);
    }
};

TEST(coinV, t1) {
    std::vector<int> coins = {1, 2, 5};
    int const amount = 11;
    int const output = 3;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int const ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

TEST(coinV, t2) {
    std::vector<int> coins = {2};
    int const amount = 3;
    int const output = -1;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int const ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

TEST(coinV, t3) {
    std::vector<int> coins = {1};
    int const amount = 0;
    int const output = 0;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int const ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV0(benchmark::State& state) {
    for (auto&& _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int const amount = 11;
        int const output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int const ret = sl.CoinChange(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV0);

static void BenchMarkV1(benchmark::State& state) {
    for (auto&& _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int const amount = 11;
        int const output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int const ret = sl.CoinChangeV1(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State& state) {
    for (auto&& _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int const amount = 11;
        int const output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int const ret = sl.CoinChangeV2(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

}  // namespace
