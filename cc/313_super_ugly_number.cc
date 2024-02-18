// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A super ugly number is a positive integer whose prime factors are in the array
primes.

Given an integer n and an array of integers primes, return the nth super ugly
number.

The nth super ugly number is guaranteed to fit in a 32-bit signed integer.*/

#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    int NthSuperUglyNumber(int n, vector<int> &primes) {
        int n2 = primes.size();
        vector<int> dp(n2, 0);
        vector<long long> ans{1};

        while ((int)ans.size() < n) {
            int mn = 0;
            for (int i = 0; i < n2; i++)
                if (ans[dp[i]] * primes[i] < ans[dp[mn]] * primes[mn]) mn = i;

            ans.push_back(ans[dp[mn]] * primes[mn]);

            for (int i = 0; i < n2; i++)
                if (ans.back() == ans[dp[i]] * primes[i]) dp[i]++;
        }

        return ans[n - 1];
    }
};



TEST(super_ugly_number, t1) {
    int n = 12;
    vector<int> primes = {2, 7, 13, 19};
    int output = 32;
    // Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the
    // first 12 super ugly numbers given primes = [2,7,13,19].
    Solution sl;
    int ret = sl.NthSuperUglyNumber(n, primes);
    EXPECT_EQ(ret, output);
}

TEST(super_ugly_number, t2) {
    int n = 1;
    vector<int> primes = {2, 3, 5};
    int output = 1;
    // 1 has no prime factors, therefore all of its prime factors are in the
    // array primes = [2,3,5]
    Solution sl;
    int ret = sl.NthSuperUglyNumber(n, primes);
    EXPECT_EQ(ret, output);
}

}
