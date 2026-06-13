/*
 * You are given an array of strings words, where each string represents a word
 * containing lowercase English letters.
 *
 * You are also given an integer array weights of length 26, where weights[i]
 * represents the weight of the ith lowercase English letter.
 *
 * The weight of a word is defined as the sum of the weights of its characters.
 *
 * For each word, take its weight modulo 26 and map the result to a lowercase
 * English letter using reverse alphabetical order (0 -> 'z', 1 -> 'y', ..., 25
 * -> 'a').
 *
 * Return a string formed by concatenating the mapped characters for all words
 * in order.
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 10
 * weights.length == 26
 * 1 <= weights[i] <= 100
 * words[i] consists of lowercase English letters.
 *
 */

#include <array>
#include <string>
#include <vector>

using namespace std;

namespace {

class Solution {
   public:
    Solution() { BuildMap(); }
    string MapWordWeights(vector<string>& words, vector<int>& weights) {
        std::string ret = "";
        for (auto& p : words) {
            int v = 0;
            for (auto& q : p) {
                int w = weights[q - 'a'];
                v += w;
            }
            v = v % 26;
            ret += m_array[v];
        }
        return ret;
    }

   private:
    void BuildMap() {
        for (int i = 0; i < 26; i++) {
            m_array[i] = 'z' - i;
        }
    }
    std::array<char, 26> m_array;
};

}  // namespace

#include <gtest/gtest.h>

TEST(mapWordWeights, t0) {
    std::vector<std::string> words = {"abcd", "def", "xyz"};
    std::vector<int> weights = {5, 3, 12, 14, 1, 2, 3, 2, 10, 6, 6, 9, 7,
                                8, 7, 10, 8,  9, 6, 9, 9, 8,  3, 7, 7, 2};

    string output = "rij";
    Solution sl;
    auto ret = sl.MapWordWeights(words, weights);
    EXPECT_EQ(output, ret);

    /*Explanation:
     * The weight of "abcd" is 4 + 3 + 12 + 14 = 34. The result modulo 26 is 34
     * % 26 = 8, which maps to 'r'. The weight of "def" is 14 + 1 + 2 = 17. The
     * result modulo  26 is 17 % 26 = 17, which maps to 'i'. The weight of "xyz"
     * is 7 + 7 + 2 = 16.
     * The result modulo 26 is 16 % 26 = 16, which maps to 'j'. Thus,
     * the string formed by concatenating the mapped characters is "rij".
     */
}

TEST(mapWordWeights, t1) {
    std::vector<std::string> words = {"a", "b", "c"};
    std::vector<int> weights = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    string output = "yyy";
    Solution sl;
    auto ret = sl.MapWordWeights(words, weights);
    EXPECT_EQ(output, ret);

    /* Explanation:
     * Each word has weight 1. The result modulo 26 is 1 % 26 = 1, which maps to
     * 'y'.
     * Thus, the string formed by concatenating the mapped characters is "yyy".
     */
}

TEST(mapWordWeights, t2) {
    std::vector<std::string> words = {"abcd"};
    std::vector<int> weights = {7, 5, 3,  4, 3, 5, 4, 9, 4, 2, 2, 7, 10,
                                2, 5, 10, 6, 1, 2, 2, 4, 1, 3, 4, 4, 5};

    string output = "g";
    Solution sl;
    auto ret = sl.MapWordWeights(words, weights);
    EXPECT_EQ(output, ret);

    /* Explanation:
     *
     * The weight of "abcd" is 7 + 5 + 3 + 4 = 19. The result modulo 26 is 19 %
     * 26 = 19, which maps to 'g'.
     *
     * Thus, the string formed by concatenating the mapped characters is "g".
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
