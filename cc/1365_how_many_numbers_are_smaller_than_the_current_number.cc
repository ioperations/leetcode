// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given the array nums, for each nums[i] find out how many numbers in the array
are smaller than it. That is, for each nums[i] you have to count the number of
valid j's such that j != i and nums[j] < nums[i].

Return the answer in an array.*/

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    vector<int> SmallerNumbersThanCurrent(vector<int> &nums) {
        vector<int> s(101, -1);
        vector<int> f = nums;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < (int)nums.size(); i++) {
            if (s[nums[i]] == -1) {
                s[nums[i]] = i;
            }
        }
        for (int i = 0; i < (int)f.size(); i++) {
            f[i] = s[f[i]];
        }
        return f;
    }
};

TEST(how_many_numbers_are_smaller_than_the_current_number, t1) {
    std::vector<int> nums{8, 1, 2, 2, 3};
    std::vector<int> output{4, 0, 1, 1, 3};
    Solution sl;
    auto ret = sl.SmallerNumbersThanCurrent(nums);
    EXPECT_EQ(ret, output);
}

TEST(how_many_numbers_are_smaller_than_the_current_number, t2) {
    std::vector<int> nums{6, 5, 4, 8};
    std::vector<int> output{2, 1, 0, 3};
    Solution sl;
    auto ret = sl.SmallerNumbersThanCurrent(nums);
    EXPECT_EQ(ret, output);
}

TEST(how_many_numbers_are_smaller_than_the_current_number, t3) {
    std::vector<int> nums{7, 7, 7, 7};
    std::vector<int> output{0, 0, 0, 0};
    Solution sl;
    auto ret = sl.SmallerNumbersThanCurrent(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
