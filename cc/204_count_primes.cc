// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int CountPrimes(int n) {
        vector<bool> visited(n, false);
        int count = 0;
        for (int i = 2; i < n; i++) {
            if (visited[i] == true) continue;
            count++;
            // make all multiple of current prine as visited
            for (int j = i + i; j < n; j += i) visited[j] = true;
        }
        return count;
    }
};

TEST(count_primes, t1) {
    int const n = 10;
    int const output = 4;
    // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
    Solution sl;
    int const ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(count_primes, t2) {
    int const n = 0;
    int const output = 0;
    Solution sl;
    int const ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(count_primes, t3) {
    int const n = 1;
    int const output = 0;
    Solution sl;
    int const ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
