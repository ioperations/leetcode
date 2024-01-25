// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*Given an integer n, return the number of structurally unique BST's (binary
   search trees) which has exactly n nodes of unique values from 1 to n.

*/
#include <functional>
#include <tuple>
#include <unordered_map>
#include <vector>
using namespace std;
#include <map>

class Solution {
   public:
    int NumTrees(int n) {
        // pass
        map<int, int> cache;
        function<int(int)> fun = [&](int j) -> int {
            if (j == 0) return 1;
            if (j == 1) return 1;
            if (j == 2) return 2;

            if (cache.count(j)) return cache[j];
            int ret = 0;
            for (int i = 0; i < j; i++) {
                ret += fun(j - i - 1) * fun(i);
            }
            cache[j] = ret;
            return ret;
        };
        return fun(n);
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 3;
    int out = 5;
    Solution sl;
    int ret = sl.NumTrees(n);
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    int n = 1;
    int out = 1;
    Solution sl;
    int ret = sl.NumTrees(n);
    EXPECT_EQ(ret, out);
}

TEST(t0, t3) {
    vector<int> test_case{1,       1,        2,         5,         14,
                          42,      132,      429,       1430,      4862,
                          16796,   58786,    208012,    742900,    2674440,
                          9694845, 35357670, 129644790, 477638700, 1767263190};
    Solution sl;
    int size = test_case.size();
    for (int i = 1; i < size; i++) {
        int ret = sl.NumTrees(i);
        EXPECT_EQ(ret, test_case[i]);
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
