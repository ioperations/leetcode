// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given a string s and an integer k, reverse the first k characters for every 2k
characters counting from the start of the string.

If there are fewer than k characters left, reverse all of them. If there are
less than 2k but greater than or equal to k characters, then reverse the first k
characters and leave the other as original.
*/

#include <benchmark/benchmark.h>
#include <algorithm>
#include <stack>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string ReverseStr(string s, int k) {
        // pass

        for (int i = 0; i < (int)s.size(); i += 2 * k) {
            ReverseStr(s, i, i + k - 1);
        }

        return s;
    }

    string ReverseStrV2(std::string s, int k) {
        if (k >= (int)s.length()) {
            reverse(s.begin(), s.end());
            return s;
        }
        int q = 0;
        for (int i = 0; i < (int)s.length(); i += k) {
            if (q % 2 == 0) {
                if (i + k < (int)s.length())
                    reverse(s.begin() + i, s.begin() + i + k);
                else
                    reverse(s.begin() + i, s.end());
            }
            q++;
        }
        return s;
    }

    void ReverseStr(string &s, int start, int end) {
        if (start >= (int)s.size()) {
            return;
        }
        // pass
        std::stack<char> stack;
        for (int i = start; i < (end + 1) && i < (int)s.size(); i++) {
            stack.push(s[i]);
        }

        for (int i = start; i < end + 1 && i < (int)s.size(); i++) {
            s[i] = stack.top();
            stack.pop();
        }
    }
};



TEST(reverse_string_ii, t1) {
    std::string s = "abcdefg";
    int k = 2;
    std::string output = "bacdfeg";
    Solution sl;
    auto ret = sl.ReverseStr(s, k);
    EXPECT_EQ(ret, output);
}

TEST(reverse_string_ii_v2, t1) {
    std::string s = "abcdefg";
    int k = 2;
    std::string output = "bacdfeg";
    Solution sl;
    auto ret = sl.ReverseStrV2(s, k);
    EXPECT_EQ(ret, output);
}

TEST(reverse_string_ii, t2) {
    std::string s = "abcd";
    int k = 2;
    std::string output = "bacd";
    Solution sl;
    auto ret = sl.ReverseStr(s, k);

    EXPECT_EQ(ret, output);
}
TEST(reverse_string_ii_v2, t2) {
    std::string s = "abcd";
    int k = 2;
    std::string output = "bacd";
    Solution sl;
    auto ret = sl.ReverseStrV2(s, k);

    EXPECT_EQ(ret, output);
}

static void BenchV1(benchmark::State &state) {
    std::string s = "abcd";
    int k = 2;
    std::string output = "bacd";
    Solution sl;

    for (auto _ : state) {
        auto ret = sl.ReverseStr(s, k);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchV1);
static void BenchV2(benchmark::State &state) {
    std::string s = "abcd";
    int k = 2;
    std::string output = "bacd";
    Solution sl;

    for (auto _ : state) {
        auto ret = sl.ReverseStrV2(s, k);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchV2);

}  // namespace
