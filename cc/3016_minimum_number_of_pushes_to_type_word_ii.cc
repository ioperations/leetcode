/*
 * You are given a string word containing lowercase English letters.
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
 * Note that 1, *, #, and 0 do not map to any letters.
 *
 * 1 <= word.length <= 105
 * word consists of lowercase English letters.
 */
#include <array>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;

namespace {
class Solution {
   public:
    int MinimumPushes(const string& word) {
        unordered_map<char, int> map;
        for (auto& k : word) {
            map[k]++;
        }

        priority_queue<Node> node;
        for (auto& [k, v] : map) {
            node.emplace(k - 'a', v);
        }
        int ret = 0;

        int size = 0;
        while (!node.empty()) {
            auto top = node.top();

            node.pop();

            if (m_key2Times[top.k] != 0) {
                ret += top.v * (m_key2Times[top.k]);
                continue;
            }
            int value = 1 + size / 8;
            m_key2Times[top.k] = value;
            ret += top.v * value;
            size++;
        }

        return ret;
    }

   private:
    struct Node {
        int k = 0;
        int v = 0;
        Node(int k, int v) : k(k), v(v) {}
        bool operator<(const Node& n) const { return v < n.v; }
    };

    std::array<int, 26> m_key2Times{0};
};
}  // namespace
#include <gtest/gtest.h>

TEST(minimumPushes, t0) {
    string word = "abcde";
    int output = 5;
    Solution sl;
    int ret = sl.MinimumPushes(word);
    EXPECT_EQ(output, ret);
    /*Explanation: The remapped keypad given in the image provides the minimum
    cost. "a" -> one push on key 2 "b" -> one push on key 3 "c" -> one push on
    key 4 "d" -> one push on key 5 "e" -> one push on key 6 Total cost is 1 + 1
    + 1 + 1 + 1 = 5. It can be shown that no other mapping can provide a lower
    cost.
    */
}
TEST(minimumPushes, t1) {
    string word = "xyzxyzxyzxyz";
    int output = 12;
    Solution sl;
    int ret = sl.MinimumPushes(word);
    EXPECT_EQ(output, ret);
    /*
     * The remapped keypad given in the image provides the minimum cost.
     * "x" -> one push on key 2
     * "y" -> one push on key 3
     * "z" -> one push on key 4
     * Total cost is 1 * 4 + 1 * 4 + 1 * 4 = 12
     * It can be shown that no other mapping can provide a lower cost.
     * Note that the key 9 is not mapped to any letter: it is not necessary to
     * map letters to every key, but to map all the letters.
     */
}

TEST(minimumPushes, t2) {
    string word = "aabbccddeeffgghhiiiiii";
    int output = 24;
    Solution sl;
    int ret = sl.MinimumPushes(word);
    EXPECT_EQ(output, ret);
    /*
     * The remapped keypad given in the image provides the minimum cost.
     * "a" -> one push on key 2
     * "b" -> one push on key 3
     * "c" -> one push on key 4
     * "d" -> one push on key 5
     * "e" -> one push on key 6
     * "f" -> one push on key 7
     * "g" -> one push on key 8
     * "h" -> two pushes on key 9
     * "i" -> one push on key 9
     * Total cost is 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 1 * 2 + 2 *
     * 2 + 6 * 1 = 24. It can be shown that no other mapping can provide a lower
     * cost.
     */
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
