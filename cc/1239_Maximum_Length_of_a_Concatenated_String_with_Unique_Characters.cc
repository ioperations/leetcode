// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an array of strings arr. A string s is formed by the concatenation
of a subsequence of arr that has unique characters.

Return the maximum possible length of s.

A subsequence is an array that can be derived from another array by deleting
some or no elements without changing the order of the remaining elements.

*/

#include <algorithm>
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "benchmark/benchmark.h"
#include "gtest/gtest.h"

namespace {
class Solution {
   public:
    int MaxLength(std::vector<std::string>& arr) {
        // 这个性能肯定又不过关,但是好理解
        auto existed = [&](std::map<char, int>& map, std::string& str) -> bool {
            for (const auto& ptr : str) {
                if (map.count(ptr)) {
                    if (map.at(ptr) != 0) {
                        return true;
                    }
                }
            }
            return false;
        };

        std::map<char, int> visisted;
        int const size = static_cast<int>(arr.size());
        std::function<int(std::string&, int, int)> fun = [&](std::string& pre, int i,
                                                        int result) -> int {
            if (i >= size) {
                return result;
            }
            if (existed(visisted, arr.at(i))) {
                return std::max(fun(pre, i + 1, result), result);
            }
            int next = 0;

            {
                pre += arr.at(i);
                for (auto& ptr : arr.at(i)) {
                    visisted[ptr]++;
                }
                next = fun(pre, i + 1, result + static_cast<int>(arr.at(i).size()));
                for (auto& ptr : arr.at(i)) {
                    visisted[ptr]--;
                }
                for (int j = 0; j < static_cast<int>(arr.at(i).size()); j++) {
                  pre.pop_back();
                }
            }
            int const next_2 = fun(pre, i + 1, result);
            return std::max(next, next_2);
        };

        std::string cur;
        return fun(cur, 0, 0);
    }

    int MaxLengthV2(std::vector<std::string>& arr) {
        std::vector<unsigned> a;

        for (const std::string& x : arr) {
            unsigned mask = 0U;
            for (char const c : x) {
                mask |= 1U << static_cast<unsigned>(c - 'a');
            }
            if (__builtin_popcount(mask) != static_cast<int>(x.length())) {
                continue;
            }
            a.push_back(mask);
        }

        int ans = 0;

        std::vector<unsigned> dp{0U};
        for (unsigned const i : a) {
            int const size = static_cast<int>(dp.size());
            for (int j = 0; j < size; ++j) {
                if (dp.at(j) & i) {
                    continue;
                }
                unsigned const t = dp.at(j) | i;
                dp.push_back(t);
                ans = std::max(ans, __builtin_popcount(t));
            }
        }

        return ans;
    }
};

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharacters, t1) {
    std::vector<std::string> arr = {"un", "iq", "ue"};
    int const output = 4;
    /*Explanation: All the valid concatenations are:
    - ""
    - "un"
    - "iq"
    - "ue"
    - "uniq" ("un" + "iq")
    - "ique" ("iq" + "ue")
    Maximum length is 4.
    */
    Solution sl;
    int const ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharacters, t2) {
    std::vector<std::string> arr = {"cha", "r", "act", "ers"};
    int const output = 6;
    /*
     Possible longest valid concatenations are "chaers" ("cha" + "ers") and
     "acters" ("act" + "ers").
    */
    Solution sl;
    int const ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharacters, t3) {
    std::vector<std::string> arr = {"abcdefghijklmnopqrstuvwxyz"};
    int const output = 26;
    // Explanation: The only string in arr has all 26 characters.};
    Solution sl;
    int const ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharactersV2, t1) {
    std::vector<std::string> arr = {"un", "iq", "ue"};
    int const output = 4;
    /*Explanation: All the valid concatenations are:
    - ""
    - "un"
    - "iq"
    - "ue"
    - "uniq" ("un" + "iq")
    - "ique" ("iq" + "ue")
    Maximum length is 4.
    */
    Solution sl;
    int const ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharactersV2, t2) {
    std::vector<std::string> arr = {"cha", "r", "act", "ers"};
    int const output = 6;
    /*
     Possible longest valid concatenations are "chaers" ("cha" + "ers") and
     "acters" ("act" + "ers").
    */
    Solution sl;
    int const ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

TEST(MaximumLengthOfAConcatenatedStringWithUniqueCharactersV2, t3) {
    std::vector<std::string> arr = {"abcdefghijklmnopqrstuvwxyz"};
    int const output = 26;
    // Explanation: The only string in arr has all 26 characters.};
    Solution sl;
    int const ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV1(benchmark::State& state) {
    std::vector<std::string> arr = {"un", "iq", "ue"};
    for (auto&& _ : state) {
        int const output = 4;

        Solution sl;
        int const ret = sl.MaxLength(arr);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State& state) {
    std::vector<std::string> arr = {"un", "iq", "ue"};
    for (auto&& _ : state) {
        int const output = 4;

        Solution sl;
        int const ret = sl.MaxLengthV2(arr);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

}  // namespace
