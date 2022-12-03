#include <vector>
using namespace std;

class Solution {
   public:
    int CountPrimes(int n) {
        vector<bool> visited(n, 0);
        int count = 0;
        for (int i = 2; i < n; i++) {
            if (visited[i] == true) continue;
            count++;
            // make all multiple of current prine as visited
            for (int j = i + i; j < n; j += i) visited[j] = 1;
        }
        return count;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    int n = 10;
    int output = 4;
    // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int n = 0;
    int output = 0;
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int n = 1;
    int output = 0;
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
