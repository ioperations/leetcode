// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two strings word1 and word2, return the minimum number of operations
required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character

*/
// #pragma GCC optimize("O2")

#include <benchmark/benchmark.h>

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MinDistance(string word1, string word2) {
        std::map<std::pair<std::string, std::string>, int> cache;
        return EditDistance(word1, word2, cache);
    }

    int EditDistance(
        const std::string& word1, const std::string& word2,
        std::map<std::pair<std::string, std::string>, int>& cache) {
        if (!word2.size()) {
            return word1.size();
        }
        if (!word1.size()) {
            return word2.size();
        }

        if (cache.count(std::make_pair(word1, word2))) {
            return cache[std::make_pair(word1, word2)];
        }

        if (word1[0] == word2[0]) {
            return EditDistance(word1.substr(1, word1.size()),
                                word2.substr(1, word2.size()), cache);
        }

        int const remove =
            1 + EditDistance(word1.substr(1, word1.size()), word2, cache);
        int const replace =
            1 + EditDistance(word1.substr(1, word1.size()),
                             word2.substr(1, word2.size()), cache);
        int const insert =
            1 + EditDistance(word1, word2.substr(1, word2.size()), cache);

        int const ret = std::min({remove, replace, insert});
        cache[std::make_pair(word1, word2)] = ret;
        return ret;
    }

    int MinDistanceV3(std::string word1, std::string word2) {
        int m = word1.size();
        int n = word2.size();
        map<pair<int, int>, int> cache;
        function<int(int, int)> fun = [&](int i, int j) -> int {
            if (cache.count(make_pair(i, j))) {
                return cache[make_pair(i, j)];
            }
            if (i >= m && j >= n) {
                return 0;
            }
            if (i >= m) {
                return n - j;
            }
            if (j >= n) {
                return m - i;
            }
            if (word1[i] == word2[j]) {
                cache[make_pair(i, j)] = fun(i + 1, j + 1);
            } else {
              cache[make_pair(i, j)] =
                  1 + min({fun(i + 1, j + 1), fun(i + 1, j), fun(i, j + 1)});
            }
            return cache[make_pair(i, j)];
        };
        return fun(0, 0);
    }
    int MinDistanceV2(std::string word1, std::string word2) {
      int const m = word1.length();
      int const n = word2.length();
      std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));
      for (int i = 0; i <= m; i++) dp[i][0] = i;
      for (int i = 0; i <= n; i++) dp[0][i] = i;
      for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
          if (word1[i - 1] == word2[j - 1])
            dp[i][j] = 0 + dp[i - 1][j - 1];
          else {
            int mn = 1 + dp[i - 1][j];
            if (1 + dp[i][j - 1] < mn) mn = 1 + dp[i][j - 1];
            if (1 + dp[i - 1][j - 1] < mn) mn = 1 + dp[i - 1][j - 1];
            dp[i][j] = mn;
          }
        }
        }

        return dp[m][n];
    }
};

TEST(edit_distance_v2, t2) {
    std::string word1 = "intention", word2 = "execution";
    int const output = 5;
    Solution s;

    int const ret = s.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(edit_distance_v2, t3) {
    std::string word1 = "horse", word2 = "ros";

    int const output = 3;
    Solution s;

    int const ret = s.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(edit_distance_v2, t4) {
    std::string word1 = "dinitrophenylhydrazine",
                word2 = "acetylphenylhydrazine";

    int const output = 6;
    Solution s;

    int const ret = s.MinDistanceV2(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(edit_distance_v3, t2) {
    std::string word1 = "intention", word2 = "execution";
    int const output = 5;
    Solution s;

    int const ret = s.MinDistanceV3(word1, word2);
    EXPECT_EQ(ret, output);
}
TEST(edit_distance_v4, t3) {
    std::string word1 = "horse", word2 = "ros";

    int const output = 3;
    Solution s;

    int const ret = s.MinDistanceV3(word1, word2);
    EXPECT_EQ(ret, output);
}
TEST(edit_distance_v4, t4) {
    std::string word1 = "dinitrophenylhydrazine",
                word2 = "acetylphenylhydrazine";

    int const output = 6;
    Solution s;

    int const ret = s.MinDistanceV3(word1, word2);
    EXPECT_EQ(ret, output);
}

static void BenchMarkFirst(benchmark::State& state) {
    for (auto _ : state) {
        std::string word1 = "horse", word2 = "ros";

        int const output = 3;
        Solution s;

        int const ret = s.MinDistance(word1, word2);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkFirst);

static void BenchMarkSecond(benchmark::State& state) {
    for (auto _ : state) {
        std::string word1 = "horse", word2 = "ros";

        int const output = 3;
        Solution s;

        int const ret = s.MinDistanceV2(word1, word2);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkSecond);

static void BenchMarkThird(benchmark::State& state) {
    for (auto _ : state) {
        std::string word1 = "horse", word2 = "ros";

        int const output = 3;
        Solution s;

        int const ret = s.MinDistanceV3(word1, word2);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkThird);

}  // namespace
