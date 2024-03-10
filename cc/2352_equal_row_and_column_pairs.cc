/*Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri,
cj) such that row ri and column cj are equal.

A row and column pair is considered equal if they contain the same elements in
the same order (i.e., an equal array).

*/
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    string Mapping(vector<int> &row) {
        std::string ans = "";

        for (int j : row) ans += to_string(j) + "#";

        return ans;
    }

    int EqualPairs(vector<vector<int>> &grid) {
        int count = 0;
        int n = grid.size();
        unordered_map<string, int> mp;

        // mapping the rows with the help of mapping function to create keys
        for (int i = 0; i < n; i++) mp[Mapping(grid[i])]++;

        for (int i = 0; i < n; i++) {
            string ans = "";

            // Traversing the matrix column wise and generating new key
            for (int j = 0; j < n; j++) ans += to_string(grid[j][i]) + "#";

            // adding the number of occurences of the key generated
            count += mp[ans];
        }

        return count;
    }
};

TEST(equal_row_and_column_pairs, t1) {
    // clang-format off
    vector<vector<int>> grid = {
        {3, 2, 1},
        {1, 7, 6},
        {2, 7, 7}
    };
    // clang-format on
    int output = 1;
    // Explanation: There is 1 equal row and column pair:
    // - (Row 2, Column 1): [2,7,7]
    Solution sl;
    int ret = sl.EqualPairs(grid);
    EXPECT_EQ(ret, output);
}

TEST(equal_row_and_column_pairs, t2) {
    // clang-format off
    vector<vector<int>> grid = {
        {3, 1, 2, 2},
        {1, 4, 4, 5},
        {2, 4, 2, 2},
        {2, 4, 2, 2}
    };
    // clang-format on
    int output = 3;
    // Explanation: There are 3 equal row and column pairs:
    // (Row 0, Column 0): [3,1,2,2]
    // (Row 2, Column 2): [2,4,2,2]
    // (Row 3, Column 2): [2,4,2,2]

    Solution sl;
    int ret = sl.EqualPairs(grid);
    EXPECT_EQ(ret, output);
}

}  // namespace
