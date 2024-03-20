// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More
formally, if you are on index i on the current row, you may move to either index
i or index i + 1 on the next row.

 */

#include <algorithm>
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

using namespace std;

namespace {
class Solution {
   public:
    int FindMin(std::size_t i, std::size_t j, int n, vector<vector<int>> &triangle,
                vector<vector<int>> &mem) {
        if (i == n - 1) return triangle[i][j];
        if (mem[i][j] != -1) return mem[i][j];
        int left = triangle[i][j] + FindMin(i + 1, j, n, triangle, mem);
        int right = triangle[i][j] + FindMin(i + 1, j + 1, n, triangle, mem);
        return mem[i][j] = min(left, right);
    }

    int MinimumTotal(vector<vector<int>> &triangle) {
        vector<vector<int>> mem(triangle.size(),
                                vector<int>(triangle.size(), -1));
        return FindMin(0, 0, triangle.size(), triangle, mem);
    }
};

TEST(triangle, t1) {
    std::vector<vector<int>> v{{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    int out = 11;
    Solution sl;
    int ret = sl.MinimumTotal(v);
    /*
    The triangle looks like:
       2
      3 4
     6 5 7
    4 1 8 3
    The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined
    above).
    */

    EXPECT_EQ(ret, out);
}

TEST(triangle, t2) {
    std::vector<vector<int>> v{{-10}};
    int out = -10;
    Solution sl;
    int ret = sl.MinimumTotal(v);
    EXPECT_EQ(ret, out);
}
}  // namespace
