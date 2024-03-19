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
#include <limits.h>

#include <algorithm>
#include <functional>
#include <map>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int CoinChange(vector<int> &coins, int amount) {
        // pass
        sort(coins.begin(), coins.end());

        std::map<int, int> cache;

        function<int(int)> fun = [&](int a) -> int {
            if (a == 0) {
                return 0;
            }
            if (cache.count(a)) {
                return cache[a];
            }

            int ret = -1;

            for (int i = (int)coins.size() - 1; i >= 0; i--) {
                if (coins[i] <= a) {
                    int tmp = fun(a - coins[i]);
                    cache[a - coins[i]] = tmp;

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

    int CoinChangeV1(vector<int> &coins, int amount) {
        vector<int> h((amount + 1), INT_MAX - 1);
        h[0] = 0;
        for (int i = 0; i < (int)h.size(); i++) {
            for (int j = 0; j < (int)coins.size(); j++) {
                if (i >= coins[j]) h[i] = min(h[i], 1 + h[i - coins[j]]);
            }
        }
        return (h[h.size() - 1] < INT_MAX - 1) ? h[h.size() - 1] : -1;
    }

    int CoinChangeV2(vector<int> &arr, int sum) {
        int n = arr.size();

        vector<vector<int>> dp(n + 1, vector<int>(sum + 1));

        for (int i = 0; i <= n; i++) dp[i][0] = 0;

        for (int i = 0; i < sum + 1; i++) dp[0][i] = INT_MAX - 1;

        for (int i = 1; i <= sum; i++) {
            if (i % arr[0] == 0)
                dp[1][i] = i / arr[0];
            else
                dp[1][i] = INT_MAX - 1;
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= sum; j++) {
                if (arr[i - 1] <= j)
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - arr[i - 1]] + 1);
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }

        if (dp[n][sum] == INT_MAX or dp[n][sum] == INT_MAX - 1) {
            return -1;
        }

        return dp[n][sum];
    }
};

TEST(coin_change, t1) {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    int output = 3;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

TEST(coin_change, t2) {
    std::vector<int> coins = {2};
    int amount = 3;
    int output = -1;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

TEST(coin_change, t3) {
    std::vector<int> coins = {1};
    int amount = 0;
    int output = 0;
    // Explanation: 11 = 5 + 5 + 1
    Solution sl;
    int ret = sl.CoinChange(coins, amount);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV0(benchmark::State &state) {
    for (auto _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int amount = 11;
        int output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int ret = sl.CoinChange(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV0);

static void BenchMarkV1(benchmark::State &state) {
    for (auto _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int amount = 11;
        int output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int ret = sl.CoinChangeV1(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State &state) {
    for (auto _ : state) {
        std::vector<int> coins = {1, 2, 5};
        int amount = 11;
        int output = 3;
        // Explanation: 11 = 5 + 5 + 1
        Solution sl;
        int ret = sl.CoinChangeV2(coins, amount);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

}  // namespace
