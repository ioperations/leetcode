/*
 * You have n  tiles, where each tile has one letter tiles[i] printed on it.
 * Return the number of possible non-empty sequences of letters you can make
 * using the letters printed on those tiles.
 *
 */

#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int numTilePossibilities(string tiles) {
        // 1 <= tiles.length <= 7
        // tiles consists of uppercase English letters.

        s = tiles;
        size = tiles.size();
        for (int i = 0; i < size; i++) {
            visiable.push_back(true);
        }

        int ret = 0;
        string s;
        Gen(s, ret);

        return ret;
    }

    void Gen(string &str, int &num, bool allowEnd = false) {
        if (allowEnd && cache.count(str) == 0) {
            num += 1;
            cache.emplace(str);
        }

        for (int i = 0; i < size; i++) {
            if (!visiable[i]) {
                continue;
            }

            visiable[i] = false;
            str += s[i];

            Gen(str, num, true);

            str.erase(str.end() - 1);
            visiable[i] = true;
        }
    }

    std::set<string> cache;
    std::size_t size = 0;
    string s;
    vector<bool> visiable;
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    string tiles = "AAB";
    int output = 8;
    Solution sl;
    int ret = sl.numTilePossibilities(tiles);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string tiles = "AAABBC";
    int output = 188;
    Solution sl;
    int ret = sl.numTilePossibilities(tiles);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    string tiles = "V";
    int output = 1;
    Solution sl;
    int ret = sl.numTilePossibilities(tiles);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
