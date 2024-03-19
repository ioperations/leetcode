// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
        Given an array nums with n objects colored red, white, or blue, sort
   them in-place so that objects of the same color are adjacent, with the colors
   in the order red, white, and blue.

    We will use the integers 0, 1, and 2 to represent the color red, white, and
    blue, respectively.

    You must solve this problem without using the library's sort function.
*/
#include <benchmark/benchmark.h>

#include <cstddef>
#include <utility>
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

namespace {
class Solution {
   public:
    void SortColors(std::vector<int> &nums) {
        for (std::size_t i = 0; i < nums.size(); i++) {
            for (std::size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] > nums[j]) {
                    std::swap(nums[i], nums[j]);
                }
            }
        }
    }
    void Merge(std::vector<int> &nums, int low, int mid, int high) {
        std::vector<int> temp;
        temp.resize(nums.size());

        int i = low, j = mid + 1, k = 0;
        while (i <= mid && j <= high) {
            if (nums[i] <= nums[j]) {
                temp[k++] = nums[i++];
            } else
                temp[k++] = nums[j++];
        }
        while (i <= mid) {
            temp[k++] = nums[i++];
        }
        while (j <= high) {
            temp[k++] = nums[j++];
        }

        for (int i = low, k = 0; i <= high; i++, k++) {
            nums[i] = temp[k];
        }
    }
    void SortColorsV2(std::vector<int> &nums) {
        MergeSort(nums, 0, nums.size() - 1);
    }
    void MergeSort(std::vector<int> &nums, int low, int high) {
        if (low >= high) {
            return;
        }
        int mid = low + (high - low) / 2;
        MergeSort(nums, low, mid);
        MergeSort(nums, mid + 1, high);
        Merge(nums, low, mid, high);
    }
};

static void BenchBubbleSort(benchmark::State &state) {
    for (auto _ : state) {
        Solution s;
        std::vector<int> nums{2, 0, 2, 1, 1, 0};
        s.SortColors(nums);
    }
}
BENCHMARK(BenchBubbleSort);

static void BenchMergeSort(benchmark::State &state) {
    for (auto _ : state) {
        Solution s;
        std::vector<int> nums{2, 0, 2, 1, 1, 0};
        s.SortColorsV2(nums);
    }
}
BENCHMARK(BenchMergeSort);

TEST(sort_colors, t1) {
    // nums = [2,0,2,1,1,0]
    // Output: [0,0,1,1,2,2]

    Solution s;
    std::vector<int> nums{2, 0, 2, 1, 1, 0};
    s.SortColors(nums);

    EXPECT_EQ(nums, (std::vector<int>{0, 0, 1, 1, 2, 2}));
    std::vector<int> nums2{2, 0, 2, 1, 1, 0};

    s.SortColorsV2(nums2);
    EXPECT_EQ(nums2, (std::vector<int>{0, 0, 1, 1, 2, 2}));
}
TEST(sort_colors, t2) {
    // nums = [2,0,1]
    // Output: [0,1,2]

    Solution s;
    std::vector<int> nums{2, 0, 1};
    s.SortColors(nums);

    EXPECT_EQ(nums, (std::vector<int>{0, 1, 2}));
    std::vector<int> nums2{2, 0, 1};
    s.SortColors(nums2);

    EXPECT_EQ(nums2, (std::vector<int>{0, 1, 2}));
}

}  // namespace
