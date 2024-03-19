// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an integer array matchsticks where matchsticks[i] is the length
of the ith matchstick. You want to use all the matchsticks to make one square.
You should not break any stick, but you can link them up, and each matchstick
must be used exactly one time.

Return true if you can make this square and false otherwise.*/

#include <algorithm>
#include <numeric>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    bool Makesquare(vector<int> &matchsticks) {
        std::sort(matchsticks.begin(), matchsticks.end());
        int sum = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
        int n = matchsticks.size();

        if (n == 0) return false;
        if (sum % 4 != 0) return false;

        // 在matchsticks当中找到能够组合成4个target的情况

        int maxlen = sum / 4;
        vector<int> sums(4);
        return Check(matchsticks, n, sums, maxlen);
    }

    bool Check(vector<int> &matchsticks, int pos, vector<int> &sums, int side) {
        if (pos == 0) return true;

        for (int i = 0; i < 4; i++) {
            if (sums[i] + matchsticks[pos - 1] <= side) {
                sums[i] += matchsticks[pos - 1];
                if (Check(matchsticks, pos - 1, sums, side)) return true;
                sums[i] -= matchsticks[pos - 1];
            }
        }

        return false;
    }

    bool MakesquareV2(vector<int> &matchsticks) {
        sort(matchsticks.begin(), matchsticks.end());
        int n = matchsticks.size();
        int sum = 0;
        for (int i = 0; i < n; i++) sum += matchsticks[i];

        if (sum % 4 != 0) return false;

        int maxlen = sum / 4;
        vector<int> sums(4);
        return Check(matchsticks, n, sums, maxlen);
    }
};

TEST(matchsticks_to_square, t1) {
    vector<int> matchsticks = {1, 1, 2, 2, 2};
    bool output = true;
    // Explanation: You can form a square with length 2, one side of the square
    // came two sticks with length 1.
    Solution sl;
    bool ret = sl.Makesquare(matchsticks);
    EXPECT_EQ(ret, output);
}

TEST(matchsticks_to_square, t2) {
    vector<int> matchsticks = {3, 3, 3, 3, 4};
    bool output = false;
    // You cannot find a way to form a square with all the matchsticks.
    Solution sl;
    bool ret = sl.Makesquare(matchsticks);
    EXPECT_EQ(ret, output);
}

}  // namespace
