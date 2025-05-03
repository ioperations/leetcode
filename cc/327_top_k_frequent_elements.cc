// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.*/

#include <benchmark/benchmark.h>

#include <algorithm>
#include <map>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    vector<int> TopKFrequent(vector<int>& nums, int k) {
        vector<int> ret;

        sort(nums.begin(), nums.end());
        map<int, int> map;
        for (auto ptr : nums) {
            map[ptr]++;
        }

        struct Cmp {
            bool operator()(pair<int, int>& a, pair<int, int>& b) {
                return a.second < b.second;
            }
        };

        std::priority_queue<pair<int, int>, vector<pair<int, int>>, Cmp> q;
        for (auto& ptr : map) {
            q.emplace(ptr);
        }

        for (int i = 0; i < k; i++) {
            ret.push_back(q.top().first);
            q.pop();
        }
        return ret;
    }
    vector<int> TopKFrequentV1(vector<int>& nums, int k) {
        unordered_map<int, int> mp;
        priority_queue<pair<int, int>> pq;
        vector<int> ans;
        for (int const i : nums) {
            ++mp[i];
        }
        for (auto it : mp) {
            pq.emplace(it.second, it.first);
        }

        while (k--) {
            ans.push_back(pq.top().second);
            pq.pop();
            if (!pq.empty()) {
                continue;
            }
        }
        return ans;
    }
};

TEST(top_k_frequent_elements, t1) {
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int const k = 2;
    std::vector<int> const output = {1, 2};

    Solution sl;
    auto ret = sl.TopKFrequent(nums, k);

    EXPECT_EQ(ret, output);
}

TEST(top_k_frequent_elements_v2, t1) {
    std::vector<int> nums = {1, 1, 1, 2, 2, 3};
    int const k = 2;
    std::vector<int> const output = {1, 2};

    Solution sl;
    auto ret = sl.TopKFrequentV1(nums, k);

    EXPECT_EQ(ret, output);
}

TEST(top_k_frequent_elements, t2) {
    std::vector<int> nums = {1};
    int const k = 1;
    std::vector<int> const output = {1};

    Solution sl;
    auto ret = sl.TopKFrequent(nums, k);

    EXPECT_EQ(ret, output);
}

TEST(top_k_frequent_elements_v2, t2) {
    std::vector<int> nums = {1};
    int const k = 1;
    std::vector<int> const output = {1};

    Solution sl;
    auto ret = sl.TopKFrequentV1(nums, k);

    EXPECT_EQ(ret, output);
}

static void BenchMarkV0(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> nums = {
            1,   1,   1,   2,   2,   3,   4,   5,   6,   7,   8,   9,   10,
            11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,
            24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
            37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
            50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
            63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,
            76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,
            89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101,
            102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 123};
        int const k = 2;
        std::vector<int> const output = {1, 2};

        Solution sl;
        auto ret = sl.TopKFrequent(nums, k);

        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV0);

static void BenchMarkV1(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> nums = {
            1,   1,   1,   2,   2,   3,   4,   5,   6,   7,   8,   9,   10,
            11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,
            24,  25,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,
            37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
            50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,
            63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,
            76,  77,  78,  79,  80,  81,  82,  83,  84,  85,  86,  87,  88,
            89,  90,  91,  92,  93,  94,  95,  96,  97,  98,  99,  100, 101,
            102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
            115, 116, 117, 118, 119, 120, 121, 122, 123};
        int const k = 2;
        std::vector<int> const output = {1, 2};

        Solution sl;
        auto ret = sl.TopKFrequentV1(nums, k);

        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

}  // namespace
