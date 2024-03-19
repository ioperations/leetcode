// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums and an integer k, return true if there are two
distinct indices i and j in the array such that nums[i] == nums[j] and abs(i -
j) <= k.
*/

#include <stdlib.h>

#include <unordered_map>
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
    bool ContainsNearbyDuplicate(const vector<int> &nums, int k) {
        int const size = nums.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; (j < size) && ((j - i) <= k); j++) {
                if (nums[i] == nums[j]) return true;
            }
        }
        return false;
    }
    bool ContainsNearbyDuplicateV2(const vector<int> &nums, int k) {
        unordered_map<int, int> map;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            if (map.count(nums[i])) {
                if (abs(i - map[nums[i]]) <= k) return true;
            }
            map[nums[i]] = i;
        }
        return false;
    }
};

TEST(contains_duplicate_ii, t1) {
    std::vector<int> nums = {1, 2, 3, 1};
    int k = 3;
    bool output = true;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicate(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(contains_duplicate_ii, t2) {
    std::vector<int> nums = {1, 0, 1, 1};
    int k = 1;
    bool output = true;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicate(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(contains_duplicate_ii, t3) {
    std::vector<int> nums = {1, 2, 3, 1, 2, 3};
    int k = 2;
    bool output = false;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicate(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(contains_duplicate_ii_v2, t1) {
    std::vector<int> nums = {1, 2, 3, 1};
    int k = 3;
    bool output = true;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicateV2(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(contains_duplicate_ii_v2, t2) {
    std::vector<int> nums = {1, 0, 1, 1};
    int k = 1;
    bool output = true;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicateV2(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(contains_duplicate_ii_v2, t3) {
    std::vector<int> nums = {1, 2, 3, 1, 2, 3};
    int k = 2;
    bool output = false;

    Solution sl;
    bool ret = sl.ContainsNearbyDuplicateV2(nums, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
