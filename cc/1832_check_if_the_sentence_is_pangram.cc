// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A pangram is a sentence where every letter of the English alphabet appears at
least once.

Given a string sentence containing only lowercase English letters, return true
if sentence is a pangram, or false otherwise.

*/

#include <benchmark/benchmark.h>

#include <set>
#include <string>

#include "gtest/gtest.h"

namespace {

class Solution {
   public:
    bool CheckIfPangram(std::string& sentence) const {
        std::set<char> s(sentence.begin(), sentence.end());
        constexpr int kAlphabetSize = 26;
        return s.size() == kAlphabetSize;
    }
    bool CheckIfPangramV2(std::string& sentence) const {
        constexpr int kAlphabetSize = 26;
        int const max = (1 << kAlphabetSize) - 1;
        int temp = 0;
        for (auto& ptr : sentence) {
            temp |= 1 << (ptr - 'a');
            if (temp == max) {
                return true;
            }
        }
        return false;
    }
};

TEST(CheckIfTheSentenceIsPangram, t1) {
    std::string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution const sl;
    bool const ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(CheckIfTheSentenceIsPangram, t2) {
    std::string sentence = "leetcode";
    bool const output = false;
    Solution const sl;
    bool const ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(CheckIfTheSentenceIsPangramV2, t1) {
    std::string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution const sl;
    bool const ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

TEST(CheckIfTheSentenceIsPangramV2, t2) {
    std::string sentence = "leetcode";
    bool const output = false;
    Solution const sl;
    bool const ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

static void BenchMarkV1(benchmark::State& state) {
    std::string sentence = "thequickbrownfoxjumpsoverthelazydog";
    for (auto&& _ : state) {
        bool const output = true;
        // Explanation: sentence contains at least one of every letter of the
        // English alphabet.
        Solution const sl;
        bool const ret = sl.CheckIfPangram(sentence);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV1);

static void BenchMarkV2(benchmark::State& state) {
    std::string sentence = "thequickbrownfoxjumpsoverthelazydog";
    for (auto&& _ : state) {
        bool const output = true;
        // Explanation: sentence contains at least one of every letter of the
        // English alphabet.
        Solution const sl;
        bool const ret = sl.CheckIfPangramV2(sentence);
        EXPECT_EQ(ret, output);
    }
}
BENCHMARK(BenchMarkV2);

}  // namespace
