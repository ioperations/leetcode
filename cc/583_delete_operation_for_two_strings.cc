// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two strings word1 and word2, return the minimum number of steps required
to make word1 and word2 the same.

In one step, you can delete exactly one character in either string.

*/

#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int Lcs(std::string s, std::string t) {
        int const n = static_cast<int>(s.length());
        int const m = static_cast<int>(t.length());

        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= m; j++) {
                if (i == 0 || j == 0) {
                    dp.at(i).at(j) = 0;
                } else {
                    if (s.at(i - 1) == t.at(j - 1)) {
                        dp.at(i).at(j) = 1 + dp.at(i - 1).at(j - 1);
                    } else {
                        dp.at(i).at(j) = max(dp.at(i - 1).at(j), dp.at(i).at(j - 1));
                    }
                }
            }
        }
        return dp.at(n).at(m);
    }

    int MinDistance(const std::string& word1, const std::string& word2) {
        int const n = static_cast<int>(word1.size());
        int const m = static_cast<int>(word2.size());
        return n + m - 2 * Lcs(word1, word2);
    }
};

TEST(DeleteOperationForTwoStrings, t1) {
    std::string const word1 = "sea", word2 = "eat";
    int const output = 2;
    // Explanation: You need one step to make "sea" to "ea" and another step to
    // make "eat" to "ea".

    Solution sl;
    int const ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

TEST(DeleteOperationForTwoStrings, t2) {
    std::string const word1 = "leetcode", word2 = "etco";
    int const output = 4;

    Solution sl;
    int const ret = sl.MinDistance(word1, word2);
    EXPECT_EQ(ret, output);
}

}  // namespace
