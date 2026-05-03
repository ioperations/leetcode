// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A super ugly number is a positive integer whose prime factors are in the array
primes.

Given an integer n and an array of integers primes, return the nth super ugly
number.

The nth super ugly number is guaranteed to fit in a 32-bit signed integer.*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    int NthSuperUglyNumber(int n, vector<int>& primes) {
        int const n2 = static_cast<int>(primes.size());
        vector<int> dp(n2, 0);
        vector<long long> ans{1};

        while (static_cast<int>(ans.size()) < n) {
            int mn = 0;
            for (int i = 0; i < n2; i++) {
                if (ans.at(dp.at(i)) * primes.at(i) < ans.at(dp.at(mn)) * primes.at(mn)) mn = i;
            }

            ans.push_back(ans.at(dp.at(mn)) * primes.at(mn));

            for (int i = 0; i < n2; i++) {
                if (ans.back() == ans.at(dp.at(i)) * primes.at(i)) dp.at(i)++;
            }
        }

        return static_cast<int>(ans.at(n - 1));
    }
};

TEST(SuperUglyNumber, t1) {
    int const n = 12;
    vector<int> primes = {2, 7, 13, 19};
    int const output = 32;
    // Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the
    // first 12 super ugly numbers given primes = [2,7,13,19].
    Solution sl;
    int const ret = sl.NthSuperUglyNumber(n, primes);
    EXPECT_EQ(ret, output);
}

TEST(SuperUglyNumber, t2) {
    int const n = 1;
    vector<int> primes = {2, 3, 5};
    int const output = 1;
    // 1 has no prime factors, therefore all of its prime factors are in the
    // array primes = [2,3,5]
    Solution sl;
    int const ret = sl.NthSuperUglyNumber(n, primes);
    EXPECT_EQ(ret, output);
}

}  // namespace
