// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given two integer arrays of equal length target and arr. In one step,
you can select any non-empty sub-array of arr and reverse it. You are allowed to
make any number of steps.

Return true if you can make arr equal to target or false otherwise.
*/

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
    bool CanBeEqual(vector<int> &target, vector<int> &arr) {
        // pass
        std::sort(target.begin(), target.end());
        std::sort(arr.begin(), arr.end());

        return target == arr;
    }
};

TEST(make_two_arrays_equal_by_reversing_sub_arrays, t1) {
    std::vector<int> target = {1, 2, 3, 4}, arr = {2, 4, 1, 3};
    bool output = true;

    Solution sl;
    bool ret = sl.CanBeEqual(target, arr);

    EXPECT_EQ(ret, output);
    /*
    You can follow the next steps to convert arr to target:
    1- Reverse sub-array [2,4,1], arr becomes [1,4,2,3]
    2- Reverse sub-array [4,2], arr becomes [1,2,4,3]
    3- Reverse sub-array [4,3], arr becomes [1,2,3,4]
    There are multiple ways to convert arr to target, this is not the only way
    to do so.*/
}

TEST(make_two_arrays_equal_by_reversing_sub_arrays, t2) {
    std::vector<int> target = {7}, arr = {7};
    bool output = true;

    Solution sl;
    bool ret = sl.CanBeEqual(target, arr);

    EXPECT_EQ(ret, output);
}

TEST(make_two_arrays_equal_by_reversing_sub_arrays, t3) {
    std::vector<int> target = {3, 7, 9}, arr = {3, 7, 11};
    bool output = false;

    Solution sl;
    bool ret = sl.CanBeEqual(target, arr);

    EXPECT_EQ(ret, output);

    /*arr does not have value 9 and it can never be converted to target.*/
}

}  // namespace
