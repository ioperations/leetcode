// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
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

TEST(count_primes, t1) {
    int n = 10;
    int output = 4;
    // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(count_primes, t2) {
    int n = 0;
    int output = 0;
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

TEST(count_primes, t3) {
    int n = 1;
    int output = 0;
    Solution sl;
    int ret = sl.CountPrimes(n);
    EXPECT_EQ(ret, output);
}

}  // namespace
