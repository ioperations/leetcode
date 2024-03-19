// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <algorithm>
#include <benchmark/benchmark.h>
#include <limits>
#include <stdlib.h>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

/// 给一个数字的数组，返回距离target最近的算数和,由任意三个数字组成
/// 3 <= nums.length <= 1000
namespace {
class Solution {
   public:
    Solution(){};
    virtual ~Solution(){};
    ///* 将输入的数据得到他的全排列，
    ///* 在每一次排列当中，得到前3个数字，
    ///* 将这三个数字加和，更最后的要求做比较
    int ThreeSum(std::vector<int> &nums, int target) {
        auto t = nums;
        std::sort(t.begin(), t.end());
        int ret = std::numeric_limits<int>::max();
        int ret_ret = 0;
        do {
            const int tmp = t[0] + t[1] + t[2];
            const int distance = abs(tmp - target);
            if (distance < ret) {
                ret = distance;
                ret_ret = tmp;
            }
        } while (std::next_permutation(t.begin(), t.end()));
        return ret_ret;
    }

    // 第二种解法，效率更高，我的第一种解法直接在数据量大的时候超时，两个指针
    int ThreeSum2(std::vector<int> &nums, int target) {
        int i, j, k;
        sort(nums.begin(), nums.end());
        const int n = nums.size();
        int diff = std::numeric_limits<int>::max();
        int sum;
        for (i = 0; i < n; i++) {
            j = i + 1;
            k = n - 1;
            while (j < k) {
                const int d = abs(target - (nums[i] + nums[j] + nums[k]));
                if (diff >= d) {
                    diff = d;
                    sum = nums[i] + nums[j] + nums[k];
                }
                if ((nums[i] + nums[j] + nums[k]) <= target) {
                    j = j + 1;
                } else {
                    k = k - 1;
                }
            }
        }
        return sum;
    }
};

TEST(sum_closest_v2, t1) {
    Solution s;
    std::vector<int> nums{-1, 2, 1, 4};
    const int ret = s.ThreeSum(nums, 1);

    EXPECT_EQ(ret, 2);
}

TEST(sum_closest_v2, t2) {
    Solution s;
    std::vector<int> nums{0, 0, 0};
    const int ret = s.ThreeSum(nums, 1);

    EXPECT_EQ(ret, 0);
}

TEST(sum_closest_v2, t3) {
    Solution s;
    std::vector<int> nums{-55, -24, -18, -11, -7, -3, 4, 5, 6, 9, 11, 23, 33};
    const int ret = s.ThreeSum2(nums, 0);

    EXPECT_EQ(ret, 0);
}
static void BenchV2(benchmark::State &state) {
    Solution s;
    for (auto _ : state) {
        std::vector<int> nums{0, 0, 0, 0, 0, 0};
        s.ThreeSum2(nums, 1);
    }
}
BENCHMARK(BenchV2);

static void BenchV1(benchmark::State &state) {
    Solution s;

    for (auto _ : state) {
        std::vector<int> nums{0, 0, 0, 0, 0, 0};
        s.ThreeSum(nums, 1);
    }
}
BENCHMARK(BenchV1);
}  // namespace
