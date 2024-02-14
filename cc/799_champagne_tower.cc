/**
 * We stack glasses in a pyramid, where the first row has 1 glass, the second
 * row has 2 glasses, and so on until the 100th row.  Each glass holds one cup
 * of champagne. Then, some champagne is poured into the first glass at the top.
 * When the topmost glass is full, any excess liquid poured will fall equally to
 * the glass immediately to the left and right of it.  When those glasses become
 * full, any excess champagne will fall equally to the left and right of those
 * glasses, and so on.  (A glass at the bottom row has its excess champagne fall
 * on the floor.) For example, after one cup of champagne is poured, the top
 * most glass is full.  After two cups of champagne are poured, the two glasses
 * on the second row are half full.  After three cups of champagne are poured,
 * those two cups become full - there are 3 full glasses total now.  After four
 * cups of champagne are poured, the third row has the middle glass half full,
 * and the two outside glasses are a quarter full, as pictured below.
 *
 * Now after pouring some non-negative integer cups of champagne, return how
 * full the jth glass in the ith row is (both i and j are 0-indexed.)
 * */

#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    double ChampagneTower(int poured, int query_row, int query_glass) {
        if (poured == 0) return 0;
        vector<double> row(1, poured);
        for (int i = 0; i < query_row; i++) {
            vector<double> next(i + 2, 0);
            for (int j = 0; j <= i; j++) {
                if (row[j] <= 1) continue;
                double excess = (row[j] - 1) / 2.0;
                next[j] += excess;
                next[j + 1] += excess;
            }
            row = next;
        }
        return min(1.0, row[query_glass]);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int poured = 1, query_row = 1, query_glass = 1;
    double output = 0.00000;
    Solution sl;
    double ret = sl.ChampagneTower(poured, query_row, query_glass);
    EXPECT_DOUBLE_EQ(output, ret);
    // Explanation: We poured 1 cup of champange to the top glass of the tower
    // (which is indexed as (0, 0)). There will be no excess liquid so all the
    // glasses under the top glass will remain empty.
}

TEST(t0, t2) {
    int poured = 2, query_row = 1, query_glass = 1;
    double output = 0.50000;
    Solution sl;
    double ret = sl.ChampagneTower(poured, query_row, query_glass);
    EXPECT_DOUBLE_EQ(output, ret);
    // ќ Explanation: We poured 1 cup of champange to the top glass of the tower
    // We poured 2 cups of champange to the top glass of the tower (which is
    // indexed as (0, 0)). There is one cup of excess liquid. The glass indexed
    // as (1, 0) and the glass indexed as (1, 1) will share the excess liquid
    // equally, and each will get half cup of champange.
}

TEST(t0, t3) {
    int poured = 100000009, query_row = 33, query_glass = 17;
    double output = 1.00000;
    Solution sl;
    double ret = sl.ChampagneTower(poured, query_row, query_glass);
    EXPECT_DOUBLE_EQ(output, ret);
}

}
