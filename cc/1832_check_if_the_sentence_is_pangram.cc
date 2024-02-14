// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A pangram is a sentence where every letter of the English alphabet appears at
least once.

Given a string sentence containing only lowercase English letters, return true
if sentence is a pangram, or false otherwise.

*/

#include <benchmark/benchmark.h>
#include <gtest/gtest.h>

#include <set>
#include <string>
using namespace std;

namespace {

class Solution {
   public:
    bool CheckIfPangram(string &sentence) {
        std::set<char> s;
        for (auto &ptr : sentence) {
            s.emplace(ptr);
        }
        return s.size() == 26;
    }
    bool CheckIfPangramV2(string &sentence) {
        int max = (1 << 26) - 1;
        int temp = 0;
        for (auto &ptr : sentence) {
            temp |= 1 << (ptr - 'a');
            if (temp == max) return true;
        }
        return false;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;
    bool ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string sentence = "leetcode";
    bool const output = false;
    Solution sl;
    bool ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(t1, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;
    bool ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

TEST(t1, t2) {
    string sentence = "leetcode";
    bool const output = false;
    Solution sl;
    bool ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV1(benchmark::State &state) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    for (auto _ : state) {
        bool const output = true;
        // Explanation: sentence contains at least one of every letter of the
        // English alphabet.
        Solution sl;
        bool ret = sl.CheckIfPangram(sentence);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State &state) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    for (auto _ : state) {
        bool const output = true;
        // Explanation: sentence contains at least one of every letter of the
        // English alphabet.
        Solution sl;
        bool ret = sl.CheckIfPangramV2(sentence);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

}  // namespace
