// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int MinDistance(const std::string& word1, const std::string& word2) {
        int n1 = word1.size(), n2 = word2.size();

        std::vector<std::vector<int>> dp(n1 + 1, std::vector<int>(n2 + 1, 0));
        // int dp[n1 + 1][n2 + 1];

        for (int i = 0; i <= n1; ++i) dp[i][0] = i;
        for (int i = 0; i <= n2; ++i) dp[0][i] = i;
        for (int i = 1; i <= n1; ++i) {
            for (int j = 1; j <= n2; ++j) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = std::min({dp[i - 1][j - 1], dp[i - 1][j],
                                         dp[i][j - 1]}) +
                               1;
                }
            }
        }
        return dp[n1][n2];
    }

    int MinDistanceV2(const std::string& word1, const std::string& word2) {
        int const n1 = word1.size();
        int const n2 = word2.size();
        std::vector<std::vector<int>> cache;
        cache.resize(n1);
        for (auto& prt : cache) {
            prt.resize(n2);
        }

        if (n1 == 0 || n2 == 0) {
            return n1 + n2;
        }
        if (word1[0] == word2[0]) {
            return MinDistanceV2(word1.substr(1, n1), word2.substr(1, n2));
        }
        int const inserted = 1 + MinDistance(word1, word2.substr(1, n2));
        int const deleted = 1 + MinDistanceV2(word1.substr(1, n1), word2);
        int const replaced =
            1 + MinDistanceV2(word1.substr(1, n1), word2.substr(1, n2));
        return std::min({inserted, deleted, replaced});
    }
};

TEST(editdistance, t0) {
    std::string const a("abc");
    std::string const b("Abc");

    Solution s;
    int const ret = s.MinDistance(a, b);

    EXPECT_EQ(ret, 1);
}
TEST(editdistance, t1) {
    std::string const a("ab");
    std::string const b("Abc");

    Solution s;
    int const ret = s.MinDistance(a, b);

    EXPECT_EQ(ret, 2);
}

TEST(editdistanceV2, t0) {
    std::string const a("abc");
    std::string const b("Abc");

    Solution s;
    int const ret = s.MinDistanceV2(a, b);

    EXPECT_EQ(ret, 1);
}

TEST(editdistanceV2, t1) {
    std::string const a("ab");
    std::string const b("Abc");

    Solution s;
    int const ret = s.MinDistanceV2(a, b);

    EXPECT_EQ(ret, 2);
}

}  // namespace
