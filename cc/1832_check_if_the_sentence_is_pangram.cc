// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A pangram is a sentence where every letter of the English alphabet appears at
least once.

Given a string sentence containing only lowercase English letters, return true
if sentence is a pangram, or false otherwise.

*/

#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>
#include <set>
#include <string>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b), __LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

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

TEST(check_if_the_sentence_is_pangram, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;
    bool ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(check_if_the_sentence_is_pangram, t2) {
    string sentence = "leetcode";
    bool const output = false;
    Solution sl;
    bool ret = sl.CheckIfPangram(sentence);
    EXPECT_EQ(ret, output);
}

TEST(check_if_the_sentence_is_pangram_v2, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;
    bool ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

TEST(check_if_the_sentence_is_pangram_v2, t2) {
    string sentence = "leetcode";
    bool const output = false;
    Solution sl;
    bool ret = sl.CheckIfPangramV2(sentence);
    EXPECT_EQ(ret, output);
}

TEST(CheckIfPangram, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;

    BENCHMARK("BenchMarkV1") {
        bool ret = sl.CheckIfPangram(sentence);
        EXPECT_EQ(ret, output);
    };
}

TEST(CheckIfPangramV2, t1) {
    string sentence = "thequickbrownfoxjumpsoverthelazydog";
    bool const output = true;
    // Explanation: sentence contains at least one of every letter of the
    // English alphabet.
    Solution sl;

    BENCHMARK("BenchMarkV2") {
        bool ret = sl.CheckIfPangramV2(sentence);
        EXPECT_EQ(ret, output);
    };
}

}  // namespace
