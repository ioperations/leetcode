// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are playing a game that contains multiple characters, and each of the
characters has two main properties: attack and defense. You are given a 2D
integer array properties where properties[i] = [attacki, defensei] represents
the properties of the ith character in the game.

A character is said to be weak if any other character has both attack and
defense levels strictly greater than this character's attack and defense levels.
More formally, a character i is said to be weak if there exists another
character j where attackj > attacki and defensej > defensei.

Return the number of weak characters.*/
#include <algorithm>
#include <climits>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
    static bool Comp(vector<int> &a, vector<int> &b) {
        if (a[0] == b[0]) return a[1] > b[1];
        return a[0] < b[0];
    }

   public:
    int NumberOfWeakCharacters(vector<vector<int>> &properties) {
        int n = properties.size();
        sort(properties.begin(), properties.end(), Comp);
        int maxdef = INT_MIN;
        int count = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (properties[i][1] < maxdef) count++;
            maxdef = max(maxdef, properties[i][1]);
        }
        return count;
    }
};



TEST(the_number_of_weak_characters_in_the_game, t1) {
    std::vector<vector<int>> properties = {{5, 5}, {6, 3}, {3, 6}};
    int output = 0;
    // Explanation: No character has strictly greater attack and defense than
    // the other.
    Solution sl;
    int ret = sl.NumberOfWeakCharacters(properties);
    EXPECT_EQ(ret, output);
}

TEST(the_number_of_weak_characters_in_the_game, t2) {
    std::vector<vector<int>> properties = {{2, 2}, {3, 3}};
    int output = 1;
    // The first character is weak because the second character has a strictly
    // greater attack and defense.
    Solution sl;
    int ret = sl.NumberOfWeakCharacters(properties);
    EXPECT_EQ(ret, output);
}

TEST(the_number_of_weak_characters_in_the_game, t3) {
    std::vector<vector<int>> properties = {{1, 5}, {10, 4}, {4, 3}};
    int output = 1;
    // Explanation: The third character is weak because the second character has
    // a strictly greater attack and defense.};
    Solution sl;
    int ret = sl.NumberOfWeakCharacters(properties);
    EXPECT_EQ(ret, output);
}
TEST(the_number_of_weak_characters_in_the_game, t4) {
    std::vector<vector<int>> properties = {{1, 1}, {2, 1}, {2, 2}, {1, 2}};
    int output = 1;
    // Explanation: The third character is weak because the second character has
    // a strictly greater attack and defense.};
    Solution sl;
    int ret = sl.NumberOfWeakCharacters(properties);
    EXPECT_EQ(ret, output);
}

}
