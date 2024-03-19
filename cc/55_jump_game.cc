// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <benchmark/benchmark.h>
#include <stddef.h>

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

/*
You are given an integer array nums. You are initially positioned at the array's
first index, and each element in the array represents your maximum jump length
at that position.
    */

namespace {
class Solution {
   public:
    bool CanJump(vector<int> &nums) {
        return CanJump(nums, 0, nums.size() - 1);
    }

    bool CanJump(vector<int> &nums, int start_position, int last_position) {
        if (last_position < start_position) {
            return false;
        }
        if (last_position == start_position) {
            return true;
        }
        if (nums[start_position] <= 0) {
            return false;
        }

        for (int i = 0; i < nums[start_position]; i++) {
            if (CanJump(nums, start_position + i + 1, last_position)) {
                return true;
            }
        }

        return false;
    }

    bool CanJumpV2(vector<int> &nums) {
        vector<int> dp(nums.size(), 0);
        dp[0] = 0;
        for (size_t i = 1; i < nums.size(); ++i) {
            dp[i] = max(dp[i - 1], nums[i - 1]) - 1;
            if (dp[i] < 0) {
                return false;
            }
        }
        return true;
    }
};

TEST(testName, testNum) {
    std::vector<int> nums = {2, 3, 1, 1, 4};
    bool output = true;

    Solution sl;
    bool ret = sl.CanJumpV2(nums);

    EXPECT_EQ(ret, output);
}

TEST(testName, t1) {
    std::vector<int> nums = {3, 2, 1, 0, 4};
    bool output = false;

    Solution sl;
    bool ret = sl.CanJumpV2(nums);

    EXPECT_EQ(ret, output);
}

static void BenchMarkMyImpl(benchmark::State &state) {
    for (auto _ : state) {
        std::vector<int> nums = {2, 3, 1, 1, 4};
        bool output = true;

        Solution sl;
        bool ret = sl.CanJump(nums);

        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkMyImpl);

static void BenchMarkDp(benchmark::State &state) {
    for (auto _ : state) {
        std::vector<int> nums = {2, 3, 1, 1, 4};
        bool output = true;

        Solution sl;
        bool ret = sl.CanJumpV2(nums);

        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkDp);

}  // namespace
