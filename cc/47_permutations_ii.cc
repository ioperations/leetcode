// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a collection of numbers, nums, that might contain duplicates, return all
 * possible unique permutations in any order.*/

#include <benchmark/benchmark.h>

#include <algorithm>
#include <climits>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<vector<int>> PermuteUnique(vector<int>& nums) {
        vector<vector<int>> ret;
        sort(nums.begin(), nums.end());

        do {
            ret.push_back(nums);
        } while (next_permutation(nums.begin(), nums.end()));
        return ret;
    }
    vector<vector<int>> m_res;

    vector<vector<int>> PermuteUniqueV1(vector<int>& nums) {
        m_res = vector<vector<int>>();
        sort(nums.begin(), nums.end());
        vector<int> cur;
        Helper(nums, cur, 0);
        return m_res;
    }

    void Helper(const vector<int>& nums, vector<int>& perm, int v) {
        if (perm.size() == nums.size()) return m_res.push_back(perm);

        int popped = INT_MIN;

        for (int i = 0; i < (int)nums.size(); i++) {
            auto a = nums[i];
            if ((v >> i & 1) || a == popped) continue;
            perm.push_back(a);
            Helper(nums, perm, v | (1 << i));
            popped = a;
            perm.pop_back();
        }
    }
};

#include <set>

TEST(permutations_ii, t1) {
    std::vector<int> nums = {1, 1, 2};
    vector<vector<int>> output = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};

    std::set<vector<int>> const output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PermuteUnique(nums);
    std::set<vector<int>> const ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

TEST(permutations_ii_v2, t1) {
    std::vector<int> nums = {1, 1, 2};
    vector<vector<int>> output = {{1, 1, 2}, {1, 2, 1}, {2, 1, 1}};

    std::set<vector<int>> const output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PermuteUniqueV1(nums);
    std::set<vector<int>> const ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

TEST(permutations_ii, t2) {
    std::vector<int> nums = {1, 2, 3};
    vector<vector<int>> output = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                  {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    std::set<vector<int>> const output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PermuteUnique(nums);
    std::set<vector<int>> const ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

TEST(permutations_ii_v2, t2) {
    std::vector<int> nums = {1, 2, 3};
    vector<vector<int>> output = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                  {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

    std::set<vector<int>> const output_set(output.begin(), output.end());
    Solution sl;
    auto ret = sl.PermuteUniqueV1(nums);
    std::set<vector<int>> const ret_set(ret.begin(), ret.end());

    EXPECT_EQ(ret_set, output_set);
}

static void BenchMarkStlFunction(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> nums = {1, 2, 3};
        vector<vector<int>> output = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                      {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

        std::set<vector<int>> const output_set(output.begin(), output.end());
        Solution sl;
        auto ret = sl.PermuteUnique(nums);
        std::set<vector<int>> const ret_set(ret.begin(), ret.end());

        EXPECT_EQ(ret_set, output_set);
    }
}
BENCHMARK(BenchMarkStlFunction);

static void BenchMarkLocalImpl(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> nums = {1, 2, 3};
        vector<vector<int>> output = {{1, 2, 3}, {1, 3, 2}, {2, 1, 3},
                                      {2, 3, 1}, {3, 1, 2}, {3, 2, 1}};

        std::set<vector<int>> const output_set(output.begin(), output.end());
        Solution sl;
        auto ret = sl.PermuteUniqueV1(nums);
        std::set<vector<int>> const ret_set(ret.begin(), ret.end());

        EXPECT_EQ(ret_set, output_set);
    }
}
BENCHMARK(BenchMarkLocalImpl);

}  // namespace
