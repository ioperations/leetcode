// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
 * Given a string array words, return the maximum value of length(word[i])
 * length(word[j]) where the two words do not share common letters. If no such
 * two words exist, return 0.*/

#include <algorithm>
#include <string>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int MaxProductV1(vector<string> &words) {
        // pass
        int ret = 0;

        int size = words.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (!ShareSameChar(words[i], words[j])) {
                    ret =
                        std::max(ret, (int)(words[i].size() * words[j].size()));
                }
            }
        }
        return ret;
    }

    bool ShareSameChar(std::string &a, std::string &b) {
        // pass
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int c_b = b.size();
        int i = 0;
        for (auto &ptr_a : a) {
            while (i < c_b && b[i] <= ptr_a) {
                if (b[i] == ptr_a) {
                    return true;
                }
                i++;
            }
            if (i >= c_b) return false;
        }
        return true;
    }

    int MaxProduct(vector<string> &words) {
        int ans = 0;
        vector<vector<int>> dp(words.size(), vector<int>(26));
        for (int i = 0; i < (int)words.size(); i++) {
            for (int j = 0; j < (int)words[i].size(); j++) {
                dp[i][words[i][j] - 'a']++;
            }
        }

        for (int i = 0; i < (int)words.size(); i++) {
            for (int j = i + 1; j < (int)words.size(); j++) {
                bool common = true;
                for (int k = 0; k < 26; k++) {
                    if (dp[i][k] > 0 && dp[j][k] > 0) {
                        common = false;
                    }
                }
                if (common) {
                    int cur = words[i].size() * words[j].size();
                    ans = max(ans, cur);
                }
            }
        }

        return ans;
    }
};



TEST(maximium_product_of_word_lengths, t1) {
    std::vector<string> words = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    int output = 16;
    // Explanation: The two words can be "abcw", "xtfn".
    Solution sl;
    int ret = sl.MaxProduct(words);
    EXPECT_EQ(ret, output);
}

TEST(maximium_product_of_word_lengths, t2) {
    std::vector<string> words = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
    int output = 4;
    // The two words can be "ab", "cd".
    Solution sl;
    int ret = sl.MaxProduct(words);
    EXPECT_EQ(ret, output);
}

TEST(maximium_product_of_word_lengths, t3) {
    std::vector<string> words = {"a", "aa", "aaa", "aaaa"};
    int output = 0;
    // No such pair of words.
    Solution sl;
    int ret = sl.MaxProduct(words);
    EXPECT_EQ(ret, output);
}

} // namespace
