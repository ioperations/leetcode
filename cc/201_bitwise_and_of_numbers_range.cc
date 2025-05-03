// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// Given two integers left and right that represent the
// range [left, right], return the bitwise AND of all numbers in this range,
// inclusive.

#include <benchmark/benchmark.h>

#include <cmath>

#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int RangeBitwiseAnd(int left, int right) {
        int ret = left;
        for (int i = left + 1; i <= right; i++) {
            ret &= i;
        }
        return ret;
    }

    int RangeBitwiseAndV2(int left, int right) {
        if (left == right) return left;

        const int diff = left ^ right;
        const int pow = floor(log2(diff));

        return (left >> pow) << pow;
    }
};

TEST(bitwise_and_of_numbers_range, t1) {
    Solution s;
    const int ret = s.RangeBitwiseAnd(5, 7);
    EXPECT_EQ(ret, 4);
}
TEST(bitwise_and_of_numbers_range, t2) {
    Solution s;
    const int ret = s.RangeBitwiseAnd(0, 0);
    EXPECT_EQ(ret, 0);
}

TEST(bitwise_and_of_numbers_range, t3) {
    Solution s;
    const int left = 1, right = 2147483647;
    const int ret = s.RangeBitwiseAndV2(left, right);
    EXPECT_EQ(ret, 0);
}
TEST(bitwise_and_of_numbers_range, t4) {
    Solution s;
    const int left = 1, right = 2;
    const int ret = s.RangeBitwiseAnd(left, right);
    EXPECT_EQ(ret, 0);
}

void BenchMarkSeqBitAnd(benchmark::State& state) {
    for (auto _ : state) {
        Solution s;
        const int left = 1, right = 200000;
        const int ret = s.RangeBitwiseAnd(left, right);

        EXPECT_EQ(ret, 0);
    }
}
BENCHMARK(BenchMarkSeqBitAnd);

void BenchMarkWise(benchmark::State& state) {
    for (auto _ : state) {
        Solution s;
        const int left = 1, right = 200000;
        const int ret = s.RangeBitwiseAndV2(left, right);

        EXPECT_EQ(ret, 0);
    }
}
BENCHMARK(BenchMarkWise);

}  // namespace
