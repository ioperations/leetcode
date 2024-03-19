// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    Bob is standing at cell (0, 0), and he wants to reach destination: (row,
    column). He can only travel right and down. You are going to help Bob by
    providing instructions for him to reach destination.

    The instructions are represented as a string, where each character is
   either:

    'H', meaning move horizontally (go right), or
    'V', meaning move vertically (go down).
    Multiple instructions will lead Bob to destination. For example, if
   destination is (2, 3), both "HHHVV" and "HVHVH" are valid instructions.

    However, Bob is very picky. Bob has a lucky number k, and he wants the kth
    lexicographically smallest instructions that will lead him to destination. k
   is 1-indexed.

    Given an integer array destination and an integer k, return the kth
    lexicographically smallest instructions that will take Bob to destination.
*/

#include <cstring>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

const int mxn = 15 + 2;
namespace {
class Solution {
   public:
    int n, m;

    int dp[mxn][mxn];

    int Go(int x, int y) {
        if (x == n && y == m) return 1;
        if (x < 0 || x > n || y < 0 || y > m) return 0;
        int &ans = dp[x][y];
        if (ans != -1) return ans;
        ans = Go(x + 1, y) + Go(x, y + 1);
        return ans;
    }

    string way;
    void Build(int x, int y, int k) {
        if (x == n && y == m) return;
        if (x < 0 || x > n || y < 0 || y > m) return;
        if (k <= Go(x, y + 1)) {
            way.push_back('H');
            Build(x, y + 1, k);
        } else {
            k -= Go(x, y + 1);
            way.push_back('V');
            Build(x + 1, y, k);
        }
    }

   public:
    string KthSmallestPath(vector<int> &destination, int k) {
        n = destination[0];
        m = destination[1];
        memset(dp, -1LL, sizeof(dp));
        Go(0, 0);
        Build(0, 0, k);
        return way;
    }
};

TEST(Kth_smallest_instructions, t1) {
    std::vector<int> destination = {2, 3};
    int k = 1;
    string output = "HHHVV";
    // Explanation: All the instructions that reach (2, 3) in lexicographic
    // order are as follows:
    // ["HHHVV", "HHVHV", "HHVVH", "HVHHV", "HVHVH", "HVVHH", "VHHHV", "VHHVH",
    // "VHVHH", "VVHHH"]

    Solution sl;
    auto ret = sl.KthSmallestPath(destination, k);
    EXPECT_EQ(ret, output);
}

TEST(Kth_smallest_instructions, t2) {
    std::vector<int> destination = {2, 3};
    int k = 2;
    string output = "HHVHV";

    Solution sl;
    auto ret = sl.KthSmallestPath(destination, k);
    EXPECT_EQ(ret, output);
}

TEST(Kth_smallest_instructions, t3) {
    std::vector<int> destination = {2, 3};
    int k = 3;
    string output = "HHVVH";

    Solution sl;
    auto ret = sl.KthSmallestPath(destination, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
