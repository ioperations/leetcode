// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer n, return the least number of perfect square numbers that sum
to n.

A perfect square is an integer that is the square of an integer; in other words,
it is the product of some integer with itself. For example, 1, 4, 9, and 16 are
perfect squares while 3 and 11 are not.*/

#include <algorithm>
#include <climits>
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

namespace {
class Solution {
   public:
    int NumSquares(int n) {
        // vector for updating the dp array/values
        std::vector<int> dp(n + 1, INT_MAX);
        // base case
        dp[0] = 0;
        int count = 1;
        while (count * count <= n) {
            int sq = count * count;
            for (int i = sq; i < n + 1; i++) {
                dp[i] = std::min(dp[i - sq] + 1, dp[i]);
            }
            count++;
        }
        return dp[n];
    }
};

TEST(perfect_squares, t1) {
    int n = 12;
    int const output = 3;
    // Explanation: 12 = 4 + 4 + 4.
    Solution sl;
    int const ret = sl.NumSquares(n);
    EXPECT_EQ(ret, output);
}

TEST(perfect_squares, t2) {
    int n = 13;
    int const output = 2;
    // Explanation: 12 = 4 + 9
    Solution sl;
    int const ret = sl.NumSquares(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
