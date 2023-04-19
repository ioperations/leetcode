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
#include <climits>
#include <functional>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int MaxLength(vector<string> &arr) {
        // 这个性能肯定又不过关,但是好理解
        auto existed = [&](std::map<char, int> &map, std::string &str) -> bool {
            for (const auto &ptr : str) {
                if (map.count(ptr)) {
                    if (map[ptr] != 0) {
                        return true;
                    }
                }
            }
            return false;
        };

        std::map<char, int> visisted;
        int const size = arr.size();
        function<int(std::string &, int, int)> fun =
            [&](std::string &pre, int i, int result) -> int {
            if (i >= size) return result;
            if (existed(visisted, arr[i])) {
                return std::max(fun(pre, i + 1, result), result);
            }
            int next;

            {
                /// take current element as the last pre output
                pre += arr[i];
                for (auto &ptr : arr[i]) {
                    visisted[ptr]++;
                }
                next = fun(pre, i + 1, result + arr[i].size());
                for (auto &ptr : arr[i]) {
                    visisted[ptr]--;
                }
                for (int j = 0; j < (int)arr[i].size(); j++) {
                    pre.pop_back();
                }
            }
            /// do not take current element as the last pre output
            int next_2 = fun(pre, i + 1, result);
            return std::max(next, next_2);
        };

        std::string cur;
        return fun(cur, 0, 0);
    }

    int MaxLengthV2(vector<string> &arr) {
        vector<int> a;

        for (const string &x : arr) {
            int mask = 0;
            for (char c : x) mask |= 1 << (c - 'a');
            if (__builtin_popcount(mask) != x.length()) continue;
            a.push_back(mask);
        }

        int ans = 0;

        vector<int> dp{0};
        for (int i = 0; i < (int)a.size(); ++i) {
            int size = dp.size();
            for (int j = 0; j < size; ++j) {
                if (dp[j] & a[i]) continue;
                int t = dp[j] | a[i];
                dp.push_back(t);
                ans = max(ans, __builtin_popcount(t));
            }
        }

        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<string> arr = {"un", "iq", "ue"};
    int output = 4;
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
    int ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<string> arr = {"cha", "r", "act", "ers"};
    int output = 6;
    /*
     Possible longest valid concatenations are "chaers" ("cha" + "ers") and
     "acters" ("act" + "ers").
    */
    Solution sl;
    int ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<string> arr = {"abcdefghijklmnopqrstuvwxyz"};
    int output = 26;
    // Explanation: The only string in arr has all 26 characters.};
    Solution sl;
    int ret = sl.MaxLength(arr);
    EXPECT_EQ(ret, output);
}

TEST(t1, t1) {
    vector<string> arr = {"un", "iq", "ue"};
    int output = 4;
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
    int ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    vector<string> arr = {"cha", "r", "act", "ers"};
    int output = 6;
    /*
     Possible longest valid concatenations are "chaers" ("cha" + "ers") and
     "acters" ("act" + "ers").
    */
    Solution sl;
    int ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

TEST(t1, t3) {
    vector<string> arr = {"abcdefghijklmnopqrstuvwxyz"};
    int output = 26;
    // Explanation: The only string in arr has all 26 characters.};
    Solution sl;
    int ret = sl.MaxLengthV2(arr);
    EXPECT_EQ(ret, output);
}

#include <benchmark/benchmark.h>

#include <algorithm>
#include <vector>

static void BenchMarkV1(benchmark::State &state) {
    vector<string> arr = {"un", "iq", "ue"};
    for (auto _ : state) {
        int output = 4;

        Solution sl;
        int ret = sl.MaxLength(arr);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State &state) {
    vector<string> arr = {"un", "iq", "ue"};
    for (auto _ : state) {
        int output = 4;

        Solution sl;
        int ret = sl.MaxLengthV2(arr);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    ::benchmark::Initialize(&argc, argv);
    if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
    return ret;
}
