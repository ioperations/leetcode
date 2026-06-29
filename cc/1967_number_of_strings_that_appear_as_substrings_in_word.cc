/*
 * Given an array of strings patterns and a string word, return the number of
 * strings in patterns that exist as a substring in word.
 *
 * A substring is a contiguous sequence of characters within a string.
 *
 *
 * 1 <= patterns.length <= 100
 * 1 <= patterns[i].length <= 100
 * 1 <= word.length <= 100
 * patterns[i] and word consist of lowercase English letters.
 * */

#include <string>
#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    int NumOfStrings(vector<string>& patterns, const string& word) {
        int ret = 0;
        for (auto& str : patterns) {
            auto it = word.find(str);
            if (it != std::string::npos) {
                ret++;
            }
        }
        return ret;
    }
};
}  // namespace

#include <gtest/gtest.h>

TEST(numOfStrings, t0) {
    vector<string> patterns = {"a", "abc", "bc", "d"};
    string word = "abc";
    int output = 3;
    Solution sl;
    int ret = sl.NumOfStrings(patterns, word);
    EXPECT_EQ(output, ret);
    /*
     * Explanation:
     * - "a" appears as a substring in "abc".
     * - "abc" appears as a substring in "abc".
     * - "bc" appears as a substring in "abc".
     * - "d" does not appear as a substring in "abc".
     * 3 of the strings in patterns appear as a substring in word.
     */
}

TEST(numOfStrings, t2) {
    vector<string> patterns = {"a", "a", "a"};
    string word = "ab";
    int output = 3;
    Solution sl;
    int ret = sl.NumOfStrings(patterns, word);
    EXPECT_EQ(output, ret);
    /*
     * Explanation:
     * Each of the patterns appears as a substring in word "ab".
     */
}

TEST(numOfStrings, t3) {
    vector<string> patterns = {"a", "b", "c"};
    string word = "aaaaabbbbb";
    int output = 2;
    Solution sl;
    int ret = sl.NumOfStrings(patterns, word);
    EXPECT_EQ(output, ret);
    /*
     * Explanation:
     * "a" appears as a substring in "aaaaabbbbb".
     * - "b" appears as a substring in "aaaaabbbbb".
     * - "c" does not appear as a substring in "aaaaabbbbb".
     * 2 of the strings in patterns appear as a substring in word
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
