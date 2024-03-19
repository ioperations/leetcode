// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums, return the largest perimeter of a triangle with a
   non-zero area, formed from three of these lengths. If it is impossible to
   form any triangle of a non-zero area, return 0.

*/

#include <algorithm>
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
    int LargestPerimeter(vector<int> &a) {
        sort(a.begin(), a.end());
        for (int i = a.size() - 1; i > 1; --i)
            if (a[i] < a[i - 1] + a[i - 2]) return a[i] + a[i - 1] + a[i - 2];
        return 0;
    }
};

TEST(largest_perimeter_triangle, t1) {
    vector<int> nums = {2, 1, 2};
    int const output = 5;
    Solution sl;
    int const ret = sl.LargestPerimeter(nums);
    EXPECT_EQ(ret, output);
}

TEST(largest_perimeter_triangle, t2) {
    vector<int> nums = {1, 2, 1};
    int const output = 0;
    Solution sl;
    int const ret = sl.LargestPerimeter(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
