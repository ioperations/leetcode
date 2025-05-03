// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of integers nums containing n + 1 integers where each integer
is in the range [1, n] inclusive.

There is only one repeated number in nums, return this repeated number.

You must solve the problem without modifying the array nums and uses only
constant extra space.*/

#include <vector>

#include "benchmark/benchmark.h"
#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int FindDuplicate(vector<int>& nums) {
        // pass
        // 1 <= n <= 105
        // nums.length == n + 1
        int n = nums.size();
        int min = 1, max = n - 1;
        while (min != max) {
            int mid = (min + max) / 2;
            int count = 0;

            for (auto k : nums) {
                if (k <= mid) count++;
            }

            if (count <= mid)
                min = mid + 1;
            else
                max = mid;
        }
        return min;
    }
    int FindDuplicateV1(vector<int>& nums) {
        int slow = nums[0], fast = nums[nums[0]];
        while (slow != fast) {  // detecting cycle
            slow = nums[slow];
            fast = nums[nums[fast]];
        }
        slow = 0;
        while (slow != fast) {  // getting the duplicate number
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

TEST(find_the_duplicate_number, t1) {
    std::vector<int> v{1, 3, 4, 2, 2};

    int i = 2;
    Solution sll;
    int ret = sll.FindDuplicate(v);
    EXPECT_EQ(ret, i);
}

TEST(find_the_duplicate_number, t2) {
    std::vector<int> v{3, 1, 3, 4, 2};

    int i = 3;
    Solution sll;
    int ret = sll.FindDuplicate(v);
    EXPECT_EQ(ret, i);
}

TEST(find_the_duplicate_number_v2, t1) {
    std::vector<int> v{1, 3, 4, 2, 2};

    int i = 2;
    Solution sll;
    int ret = sll.FindDuplicateV1(v);
    EXPECT_EQ(ret, i);
}

TEST(find_the_duplicate_number_v2, t2) {
    std::vector<int> v{3, 1, 3, 4, 2};

    int i = 3;
    Solution sll;
    int ret = sll.FindDuplicateV1(v);
    EXPECT_EQ(ret, i);
}
static void BenchMarkV0(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v{3, 1, 3, 4, 2};

        int i = 3;
        Solution sll;
        int ret = sll.FindDuplicate(v);
        EXPECT_EQ(ret, i);
    }
}
BENCHMARK(BenchMarkV0);

static void BenchMarkV1(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v{3, 1, 3, 4, 2};

        int i = 3;
        Solution sll;
        int ret = sll.FindDuplicateV1(v);
        EXPECT_EQ(ret, i);
    }
}
BENCHMARK(BenchMarkV1);

}  // namespace
