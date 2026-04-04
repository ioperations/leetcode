/**/
#include "gtest/gtest.h"

class Solution {
   public:
    long long ColoredCells(int n) {
        long long const b = n;

        long long const g = b * b;
        long long const p = (b - 1) * (b - 1);

        return g + p;
    }
};

TEST(colored_cells, t1) {
    Solution sl;
    long long const ret = sl.ColoredCells(1);
    EXPECT_EQ(ret, 1);
}

TEST(colored_cells, t2) {
    Solution sl;
    long long const ret = sl.ColoredCells(2);
    EXPECT_EQ(ret, 5);
}

TEST(colored_cells, t3) {
    Solution sl;
    long long const ret = sl.ColoredCells(3);
    EXPECT_EQ(ret, 13);
}

TEST(colored_cells, t4) {
    Solution sl;
    long long const ret = sl.ColoredCells(4);
    EXPECT_EQ(ret, 25);
}
