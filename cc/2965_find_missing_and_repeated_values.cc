/*
 *
 * You are given a 0-indexed 2D integer matrix grid of size n * n with values in
the range [1, n2]. Each integer appears exactly once except a which appears
twice and b which is missing. The task is to find the repeating and missing
numbers a and b.

Return a 0-indexed integer array ans of size 2 where ans[0] equals to a and
ans[1] equals to b.
*/

#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> findMissingAndRepeatedValues(vector<vector<int>> &grid) {
        auto size = grid.size();
        int all = (size * size) * (size * size + 1) / 2;
        int sum = 0;

        unordered_set<int> set;
        set.reserve(size * size);
        bool record = true;
        int v = 0;

        for (auto &layer1 : grid) {
            for (auto &layer2 : layer1) {
                if (set.count(layer2) > 0) {
                    v = layer2;
                    record = false;
                }

                sum += layer2;
                if (record) {
                    set.emplace(layer2);
                }
            }
        }

        return {v, all - (sum - v)};
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<vector<int>> grid = {{1, 3}, {2, 2}};
    std::vector<int> output{2, 4};
    Solution sl;
    auto ret = sl.findMissingAndRepeatedValues(grid);
    // Number 2 is repeated and number 4 is missing so the answer is [2,4].
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<vector<int>> grid = {{9, 1, 7}, {8, 9, 2}, {3, 4, 6}};
    std::vector<int> output{
        9,
        5,
    };
    // Number 9 is repeated and number 5 is missing so the answer is [9,5].

    Solution sl;
    auto ret = sl.findMissingAndRepeatedValues(grid);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
