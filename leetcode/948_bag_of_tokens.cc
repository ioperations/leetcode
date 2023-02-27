/*You have an initial power of power, an initial score of 0, and a bag of tokens
where tokens[i] is the value of the ith token (0-indexed).

Your goal is to maximize your total score by potentially playing each token in
one of two ways:

If your current power is at least tokens[i], you may play the ith token face up,
losing tokens[i] power and gaining 1 score. If your current score is at least 1,
you may play the ith token face down, gaining tokens[i] power and losing 1
score. Each token may be played at most once and in any order. You do not have
to play all the tokens.

Return the largest possible score you can achieve after playing any number of
tokens.*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;
class Solution {
   public:
    int Recursion(vector<int> &tokens, int power, int start, int end,
                  vector<vector<int>> &dp) {
        if (start > end || power < tokens[start]) return 0;
        int take = 0, nottake = 0;
        if (dp[start][end] != -1) return dp[start][end];
        if (power >= tokens[start])
            take = 1 +
                   Recursion(tokens, power - tokens[start], start + 1, end, dp);
        if (power >= tokens[start])
            nottake = Recursion(tokens, power - tokens[start] + tokens[end],
                                start + 1, end - 1, dp);
        return dp[start][end] = max(take, nottake);
    }

    int BagOfTokensScore(vector<int> &tokens, int power) {
        int n = tokens.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        sort(tokens.begin(), tokens.end());
        return Recursion(tokens, power, 0, tokens.size() - 1, dp);
    }

    int BagOfTokensScoreV1(vector<int> &tokens, int power) {
        int size = tokens.size();

        /// @param visited 当前已经访问过的节点
        /// @param current_power 当前拥有的power值
        /// @param current_score 当前拥有的分数
        std::function<int(set<int> &, int, int)> fun =
            [&fun, &size, &tokens](set<int> &visited, int current_power,
                                   int current_score) -> int {
            int max = current_score;
            for (int i = 0; i < size; i++) {
                if (visited.count(i)) {
                    continue;
                }
                if (current_score >= 1) {
                    /// 可以对i节点采用token face down 的操作
                    visited.emplace(i);
                    int v1 = fun(visited, current_power + tokens[i],
                                 current_score - 1);
                    max = std::max(max, v1);
                    visited.erase(i);
                }
                if (current_power >= tokens[i]) {
                    /// 可以对i节点采用token face up的操作
                    visited.emplace(i);
                    int v2 = fun(visited, current_power - tokens[i],
                                 current_score + 1);
                    max = std::max(max, v2);
                    visited.erase(i);
                }
            }
            return max;
        };

        set<int> visited;
        return fun(visited, power, 0);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> tokens = {100};
    int power = 50;
    Solution sl;
    int output = 0;
    // Explanation: Playing the only token in the bag is impossible because you
    // either have too little power or too little score.*/
    int ret = sl.BagOfTokensScore(tokens, power);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> tokens = {100, 200};
    int power = 150;
    Solution sl;
    int output = 1;
    int ret = sl.BagOfTokensScore(tokens, power);
    // Play the 0th token (100) face up, your power becomes 50 and score
    // becomes 1.
    // There is no need to play the 1st token since you cannot play it face up
    // to add to your score.int ret = sl.bagOfTokensScore(tokens, power);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> tokens = {100, 200, 300, 400};
    int power = 200;
    Solution sl;
    int output = 2;
    int ret = sl.BagOfTokensScoreV1(tokens, power);

    /*Play the tokens in this order to get a score of 2:
    1. Play the 0th token (100) face up, your power becomes 100 and score
    becomes 1.
    2. Play the 3rd token (400) face down, your power becomes 500 and score
    becomes 0.
    3. Play the 1st token (200) face up, your power becomes 300 and score
    becomes 1.
    4. Play the 2nd token (300) face up, your power becomes 0 and score
    becomes 2.
    */
    EXPECT_EQ(ret, output);
}

TEST(t1, t3) {
    vector<int> tokens = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int power = 200;
    Solution sl;
    int output = 4;
    int ret = sl.BagOfTokensScore(tokens, power);
    int ret1 = sl.BagOfTokensScoreV1(tokens, power);

    /*Play the tokens in this order to get a score of 2:
    1. Play the 0th token (100) face up, your power becomes 100 and score
    becomes 1.
    2. Play the 3rd token (400) face down, your power becomes 500 and score
    becomes 0.
    3. Play the 1st token (200) face up, your power becomes 300 and score
    becomes 1.
    4. Play the 2nd token (300) face up, your power becomes 0 and score
    becomes 2.
    */
    EXPECT_EQ(ret, output);
    EXPECT_EQ(ret1, output);
}
#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void BenchmarkTwoArrayDpv1(benchmark::State &state) {
    vector<int> tokens = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int power = 200;
    Solution sl;
    int output = 4;

    for (auto _ : state) {
        int ret = sl.BagOfTokensScore(tokens, power);
        EXPECT_EQ(output, ret);
    }
}
BENCHMARK(BenchmarkTwoArrayDpv1);

static void BenchmarkMyImplementation(benchmark::State &state) {
    vector<int> tokens = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};
    int power = 200;
    Solution sl;
    int output = 4;

    for (auto _ : state) {
        int ret = sl.BagOfTokensScoreV1(tokens, power);
        EXPECT_EQ(output, ret);
    }
}
BENCHMARK(BenchmarkMyImplementation);

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
