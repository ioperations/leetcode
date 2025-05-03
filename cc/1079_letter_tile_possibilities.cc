/*
 * You have n  tiles, where each tile has one letter tiles[i] printed on it.
 * Return the number of possible non-empty sequences of letters you can make
 * using the letters printed on those tiles.
 *
 */

#include <cstddef>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
   public:
    int NumTilePossibilities(string tiles) {
      // 1 <= tiles.length <= 7
      // tiles consists of uppercase English letters.

      m_s = tiles;
      m_size = tiles.size();
      for (int i = 0; i < m_size; i++) {
        m_visiable.push_back(true);
      }

      int ret = 0;
      string s;
      Gen(s, ret);

      return ret;
    }

    void Gen(string& str, int& num, bool allow_end = false) {
      if (allow_end && m_cache.count(str) == 0) {
        num += 1;
        m_cache.emplace(str);
      }

      for (int i = 0; i < m_size; i++) {
        if (!m_visiable[i]) {
          continue;
        }

        m_visiable[i] = false;
        str += m_s[i];

        Gen(str, num, true);

        str.erase(str.end() - 1);
        m_visiable[i] = true;
      }
    }

    std::set<string> m_cache;
    std::size_t m_size = 0;
    string m_s;
    vector<bool> m_visiable;
};

#include <gtest/gtest.h>

TEST(t0, t1) {
  string const tiles = "AAB";
  int const output = 8;
  Solution sl;
  int const ret = sl.NumTilePossibilities(tiles);
  EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
  string const tiles = "AAABBC";
  int const output = 188;
  Solution sl;
  int const ret = sl.NumTilePossibilities(tiles);
  EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
  string const tiles = "V";
  int const output = 1;
  Solution sl;
  int const ret = sl.NumTilePossibilities(tiles);
  EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
