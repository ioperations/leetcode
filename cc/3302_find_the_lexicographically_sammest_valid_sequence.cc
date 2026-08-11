/*
 * You are given two strings word1 and word2.
 *
 * A string x is called almost equal to y if you can change at most one
 * character in x to make it identical to y.
 *
 * A sequence of indices seq is called valid if:
 *
 * The indices are sorted in ascending order.
 * Concatenating the characters at these indices in word1 in the same order
 * results in a string that is almost equal to word2. Return an array of size
 * word2.length representing the lexicographically smallest valid sequence of
 * indices. If no such sequence of indices exists, return an empty array.
 *
 * Note that the answer must represent the lexicographically smallest array, not
 * the corresponding string formed by those indices.
 *
 * 1 <= word2.length < word1.length <= 3 * 105
 * word1 and word2 consist only of lowercase English letters.
 **/
#include <string>
#include <vector>
using namespace std;

namespace {

class Solution {
   public:
    vector<int> ValidSequence(const string& word1, const string& word2) {
        // pass
        vector<int> ret;
        return ret;
    }
};
}  // namespace
   //

#include <gtest/gtest.h>

TEST(validSequence, t0) {
    string word1 = "vbcca";
    string word2 = "abc";
    std::vector<int> output{0, 1, 2};
    Solution sl;
    auto ret = sl.ValidSequence(word1, word2);
    EXPECT_EQ(output, ret);
    /*The lexicographically smallest valid sequence of
     * indices is [0, 1, 2]:
     *
     *Change word1[0] to 'a'.
     *word1[1] is already 'b'.
     *word1[2] is already 'c'.
     */
}

TEST(validSequence, t1) {
    string word1 = "bacdc";
    string word2 = "abc";
    std::vector<int> output{1, 2, 4};
    Solution sl;
    auto ret = sl.ValidSequence(word1, word2);
    EXPECT_EQ(output, ret);
    /*The lexicographically smallest valid sequence of indices is [1, 2, 4]:

    word1[1] is already 'a'.
    Change word1[2] to 'b'.
    word1[4] is already 'c'.*/
}
TEST(validSequence, t2) {
    string word1 = "aaaaaa";
    string word2 = "aaabc";
    std::vector<int> output{};
    Solution sl;
    auto ret = sl.ValidSequence(word1, word2);
    EXPECT_EQ(output, ret);
    /*There is no valid sequence of indices.
     */
}
TEST(validSequence, t3) {
    string word1 = "abc";
    string word2 = "ab";
    std::vector<int> output{0, 1};
    Solution sl;
    auto ret = sl.ValidSequence(word1, word2);
    EXPECT_EQ(output, ret);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
