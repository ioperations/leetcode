// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*In an alien language, surprisingly, they also use English lowercase letters,
but possibly in a different order. The order of the alphabet is some permutation
of lowercase letters.

Given a sequence of words written in the alien language, and the order of the
alphabet, return true if and only if the given words are sorted
lexicographically in this alien language.*/

#include <map>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    std::map<char, int> map;

   public:
    bool IsAlienSorted(vector<string> &words, string order) {
        int i = 0;
        for (auto &ptr : order) {
            map[ptr] = i;
            i++;
        }

        int size = words.size();
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (Greather(words[i], words[j])) {
                    return false;
                }
            }
        }

        return true;
    }

    bool Greather(string &a, string &b) {
        int size_a = a.size();
        int size_b = b.size();
        for (int i = 0; i < size_a && i < size_b; i++) {
            if (map[a[i]] > map[b[i]]) {
                return true;
            }
            if (map[a[i]] < map[b[i]]) {
                return false;
            }
        }
        return size_a > size_b;
    }
};

TEST(verifying_an_alien_dictionary, t1) {
    vector<string> words = {"hello", "leetcode"};
    string order = "hlabcdefgijkmnopqrstuvwxyz";
    Solution sl;
    int ret = sl.IsAlienSorted(words, order);
    // As 'h' comes before 'l' in this language, then the sequence is sorted.
    EXPECT_EQ(true, ret);
}

TEST(verifying_an_alien_dictionary, t2) {
    vector<string> words = {"word", "world", "row"};
    string order = "worldabcefghijkmnpqstuvxyz";
    Solution sl;
    int ret = sl.IsAlienSorted(words, order);
    // As 'd' comes after 'l' in this language, then words[0] > words[1], hence
    // the sequence is unsorted.
    EXPECT_EQ(false, ret);
}

TEST(verifying_an_alien_dictionary, t3) {
    vector<string> words = {"apple", "app"};
    string order = "abcdefghijklmnopqrstuvwxyz";
    Solution sl;
    int ret = sl.IsAlienSorted(words, order);
    // The first three characters "app" match, and the second string is shorter
    // (in size.) According to lexicographical rules "apple" > "app", because
    // 'l' > '∅', where '∅' is defined as the blank character which is less than
    // any other character (More info).

    EXPECT_EQ(false, ret);
}

}  // namespace
