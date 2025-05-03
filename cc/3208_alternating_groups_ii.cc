/*
 * There is a circle of red and blue tiles. You are given an array of integers
 * colors and an integer k. The color of tile i is represented by colors[i]:
 *
 * colors[i] == 0 means that tile i is red.
 * colors[i] == 1 means that tile i is blue.
 * An alternating group is every k contiguous tiles in the circle with
 * alternating colors (each tile in the group except the first and last one has
 * a different color from its left and right tiles).
 *
 * Return the number of alternating groups.
 *
 * Note that since colors represents a circle, the first and the last tiles are
 * considered to be next to each other.
 */

#include <vector>
using namespace std;

class Solution {
   public:
    int NumberOfAlternatingGroups(vector<int>& colors, int k) {
      colors.insert(colors.end(), colors.begin(), colors.begin() + (k - 1));
      int count = 0;
      int left = 0;

      for (int right = 0; right < colors.size(); ++right) {
        if (right > 0 && colors[right] == colors[right - 1]) {
          left = right;
        }

        if (right - left + 1 >= k) {
          count++;
        }
      }

      return count;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> colors = {0, 1, 0, 1, 0};
    int const k = 3;
    int const output = 3;
    Solution sl;
    int const ret = sl.NumberOfAlternatingGroups(colors, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> colors = {0, 1, 0, 0, 1, 0, 1};
    int const k = 6;
    int const output = 2;
    Solution sl;
    int const ret = sl.NumberOfAlternatingGroups(colors, k);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> colors = {1, 1, 0, 1};
    int const k = 4;
    int const output = 0;
    Solution sl;
    int const ret = sl.NumberOfAlternatingGroups(colors, k);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
