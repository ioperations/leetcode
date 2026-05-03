// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.*/

#include <benchmark/benchmark.h>

#include <array>
#include <cstddef>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int CountSubstrings(string s) {
        int count = static_cast<int>(s.size());
        for (int i = 0; i < static_cast<int>(s.size()); i++) {
            for (int j = i + 1; j < static_cast<int>(s.size()); j++) {
                if (IsParlindromic(s, i, j)) {
                    count++;
                }
            }
        }
        return count;
    }
    bool IsParlindromic(std::string& s, int i, int j) {
        while (i < j) {
            if (s.at(i) == s.at(j)) {
                i++;
                j--;
            } else {
                return false;
            }
        }
        return true;
    }

    int CountSubstringsV1(string s) {
        int count = 0;
        std::size_t const n = s.size();
        if (n == 1) return 1;
        std::array<std::array<bool, 1001>, 1001> dp = {{{false}}};
        for (int i = 0; i < static_cast<int>(n); ++i) {
            dp[i][i] = true;
            count++;
        }
        for (int i = static_cast<int>(n - 1); i >= 0; --i) {
            for (size_t j = i + 1; j < n; ++j) {
                if (s.at(i) == s.at(j)) {
                    if (j - i == 1 || dp[i + 1][j - 1] == true) {
                        dp[i][j] = true;
                        count++;
                    }
                }
            }
        }
        return count;
    }
};

TEST(palindromicV, t1) {
    string const s = "abc";
    int const output = 3;
    // Explanation: Three palindromic strings: "a", "b", "c".

    Solution sl;
    int const ret = sl.CountSubstrings(s);
    EXPECT_EQ(ret, output);
}

TEST(palindromicV, t2) {
    string const s = "aaa";
    int const output = 6;
    // Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

    Solution sl;
    int const ret = sl.CountSubstrings(s);
    EXPECT_EQ(ret, output);
}

TEST(palindromicsubstringsV2, t1) {
    string const s = "abc";
    int const output = 3;
    // Explanation: Three palindromic strings: "a", "b", "c".

    Solution sl;
    int const ret = sl.CountSubstringsV1(s);
    EXPECT_EQ(ret, output);
}

TEST(palindromicsubstringsV2, t2) {
    string const s = "aaa";
    int const output = 6;
    // Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

    Solution sl;
    int const ret = sl.CountSubstringsV1(s);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV1(benchmark::State& state) {
    for (auto _ : state) {
        string const s = "aaa";
        int const output = 6;
        // Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa",
        // "aaa".

        Solution sl;
        int const ret = sl.CountSubstringsV1(s);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV0(benchmark::State& state) {
    for (auto _ : state) {
        string const s = "aaa";
        int const output = 6;
        // Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa",
        // "aaa".

        Solution sl;
        int const ret = sl.CountSubstrings(s);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV0);

}  // namespace
