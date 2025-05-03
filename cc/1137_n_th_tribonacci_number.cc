// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*The Tribonacci sequence Tn is defined as follows:

T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.

Given n, return the value of Tn.*/

#include <map>

#include "gtest/gtest.h"

namespace {
class Solution {
  std::map<int, int> m_cache;

 public:
  int Tribonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;
    if (m_cache.count(n)) {
      return m_cache[n];
    }
    int const ret = Tribonacci(n - 3) + Tribonacci(n - 2) + Tribonacci(n - 1);
    m_cache[n] = ret;

    return ret;
    }
};

TEST(n_th_tribonacci_number, t1) {
  int const n = 4;
  int const out = 4;
  Solution sl;
  int const ret = sl.Tribonacci(n);
  /*
      T_3 = 0 + 1 + 1 = 2
      T_4 = 1 + 1 + 2 = 4
  */
  EXPECT_EQ(ret, out);
}

TEST(n_th_tribonacci_number, t2) {
  int const n = 25;
  int const out = 1389537;
  Solution sl;
  int const ret = sl.Tribonacci(n);
  EXPECT_EQ(ret, out);
}

}  // namespace
