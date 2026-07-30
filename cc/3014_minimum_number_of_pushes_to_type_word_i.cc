/*
 * You are given a string word containing distinct lowercase English letters.
 *
 * Telephone keypads have keys mapped with distinct collections of lowercase
 * English letters, which can be used to form words by pushing them. For
 * example, the key 2 is mapped with ["a","b","c"], we need to push the key one
 * time to type "a", two times to type "b", and three times to type "c" .
 *
 * It is allowed to remap the keys numbered 2 to 9 to distinct collections of
 * letters. The keys can be remapped to any amount of letters, but each letter
 * must be mapped to exactly one key. You need to find the minimum number of
 * times the keys will be pushed to type the string word.
 *
 * Return the minimum number of pushes needed to type word after remapping the
 * keys.
 *
 * An example mapping of letters to keys on a telephone keypad is given below.
 * Note that 1, *, #, and 0 do not map to any letters. 1 <= word.length <= 26
 * word consists of lowercase English letters.
 * All letters in word are distinct.
 */
#include <array>
#include <string>
using namespace std;
namespace {

class Solution {
   public:
    int MinimumPushes(const string& word) {
        int v = 0;
        int sum = 0;
        for (char i : word) {
            auto j = i - 'a';
            auto value = m_key2Times[j];
            if (value != 0) {
                sum += value;
                continue;
            }
            value = 1 + v / model;
            m_key2Times[j] = value;
            sum += value;
            v++;
        }
        return sum;
    }

   private:
    constexpr static int model = 8;
    std::array<int, 26> m_key2Times{0};
};

}  // namespace

#include <gtest/gtest.h>

TEST(minimumPushes, t0) {
    string word = "abcde";
    int output = 5;
    Solution sl;
    auto ret = sl.MinimumPushes(word);
    EXPECT_EQ(output, ret);
    /*
     * Explanation: The remapped keypad given in the image provides the minimum
     * cost. "a" -> one push on key 2 "b" -> one push on key 3 "c" -> one push
     * on key 4 "d" -> one push on key 5 "e" -> one push on key 6 Total cost is
     * 1 + 1 + 1 + 1 + 1 = 5. It can be shown that no other mapping
     * can provide a lower cost.
     */
}
TEST(minimumPushes, t1) {
    string word = "xycdefghij";
    int output = 12;
    Solution sl;
    auto ret = sl.MinimumPushes(word);
    EXPECT_EQ(output, ret);
    /*
     * * The remapped keypad given in the image provides the minimum cost.
     * "x" -> one push on key 2
     * "y" -> two pushes on key 2
     * "c" -> one push on key 3
     * "d" -> two pushes on key 3
     * "e" -> one push on key 4
     * "f" -> one push on key 5
     * "g" -> one push on key 6
     * "h" -> one push on key 7
     * "i" -> one push on key 8
     * "j" -> one push on key 9
     * Total cost is 1 + 2 + 1 + 2 + 1 + 1 + 1 + 1 + 1 + 1 = 12.
     * It can be shown that no other mapping can provide a lower cost.
     */
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
