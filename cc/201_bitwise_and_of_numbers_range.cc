// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

// Given two integers left and right that represent the
// range [left, right], return the bitwise AND of all numbers in this range,
// inclusive.

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <cmath>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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

TEST(BenchMarkSeqBitAnd, t1) {
    Solution s;
    const int left = 1, right = 200000;

    BENCHMARK("BenchMarkSeqBitAnd") {
        const int ret = s.RangeBitwiseAnd(left, right);

        EXPECT_EQ(ret, 0);
    };
}

TEST(RangeBitwiseAndV2, t2) {
    Solution s;
    const int left = 1, right = 200000;
    BENCHMARK("BenchMarkWise") {
        const int ret = s.RangeBitwiseAndV2(left, right);

        EXPECT_EQ(ret, 0);
    };
}

}  // namespace
