// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array nums. We define a running sum of an array as runningSum[i] =
sum(nums[0]…nums[i]).

Return the running sum of nums.*/

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <vector>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {

class Solution {
   public:
    vector<int> RunningSum(vector<int> &nums) {
        int presum = 0;
        for (auto &ptr : nums) {
            ptr = ptr + presum;
            presum = ptr;
        }
        return nums;
    }
    vector<int> RunningSumV1(vector<int> &nums) {
        for (int i = 1; i < (int)nums.size(); i++) {
            nums[i] += nums[i - 1];
        }
        return nums;
    }
};

TEST(running_sum_of_1d_array, t1) {
    std::vector<int> p{1, 2, 3, 4};
    std::vector<int> output{1, 3, 6, 10};

    Solution sl;
    auto ret = sl.RunningSum(p);
    EXPECT_EQ(ret, output);
}

TEST(running_sum_of_1d_array, t2) {
    std::vector<int> p{1, 1, 1, 1, 1};
    std::vector<int> output{1, 2, 3, 4, 5};

    Solution sl;
    auto ret = sl.RunningSum(p);
    EXPECT_EQ(ret, output);
}

TEST(running_sum_of_1d_array, t3) {
    std::vector<int> p{3, 1, 2, 10, 1};
    std::vector<int> output{3, 4, 6, 16, 17};

    Solution sl;
    auto ret = sl.RunningSum(p);
    EXPECT_EQ(ret, output);
}

TEST(RunningSum, t1) {
    std::vector<int> output{3, 4, 6, 16, 17};

    Solution sl;
    BENCHMARK("BenchV1") {
        std::vector<int> p{3, 1, 2, 10, 1};
        auto ret = sl.RunningSum(p);
        EXPECT_EQ(ret, output);
    };
}

TEST(BenchV2, v2) {
    std::vector<int> output{3, 4, 6, 16, 17};

    Solution sl;

    BENCHMARK("BenchV2") {
        std::vector<int> p{3, 1, 2, 10, 1};
        auto ret = sl.RunningSumV1(p);
        EXPECT_EQ(ret, output);
    };
}

}  // namespace
