// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A sequence x1, x2, ..., xn is Fibonacci-like if:

n >= 3
xi + xi+1 == xi+2 for all i + 2 <= n
Given a strictly increasing array arr of positive integers forming a sequence,
return the length of the longest Fibonacci-like subsequence of arr. If one does
not exist, return 0.

A subsequence is derived from another sequence arr by deleting any number of
elements (including none) from arr, without changing the order of the remaining
elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].*/

#include <algorithm>
#include <cstring>
#include <functional>
#include <map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int LenLongestFibSubseq(vector<int>& arr) {
        // pass
        int size = arr.size();
        function<int(vector<int>&, int)> fun = [&](vector<int>& mem,
                                                   int index) -> int {
            // pass
            if (index >= size) return mem.size();
            if (mem.size() <= 1) {
                mem.push_back(arr[index]);
            } else {
              int const fib_1 = mem.back();
              mem.pop_back();
              int const fib_2 = mem.back();
              mem.push_back(fib_1);
              if (arr[index] == fib_1 + fib_2) {
                mem.push_back(arr[index]);
                }
            }

            int const ret1 = fun(mem, index + 1);

            if (mem.size()) mem.pop_back();
            int const ret2 = fun(mem, index + 1);
            return max(ret1, ret2);
        };
        vector<int> mem;
        int const ret = fun(mem, 0);

        return ret;
    }
    map<int, int> m_mp;
    int m_ans = 0;
    int m_dp[1005][1005]{};

    int Func(int i, int j, vector<int>& v) {
      if (m_mp.find(v[i] + v[j]) == m_mp.end()) {
        return 0;
      }

      if (m_dp[i][j] != -1) {
        return m_dp[i][j];
      }

      return m_dp[i][j] = 1 + Func(j, m_mp[v[i] + v[j]], v);
    }

    int LenLongestFibSubseqV2(vector<int>& v) {
      int i = 0, j = 0;
      memset(m_dp, -1, sizeof(m_dp));
      int const n = v.size();

      for (i = 0; i < n; i++) {
        m_mp[v[i]] = i;
        }

        for (i = 0; i < n - 2; i++) {
            for (j = i + 1; j < n - 1; j++) {
              if (m_mp.find(v[i] + v[j]) != m_mp.end()) {
                m_ans = max(m_ans, Func(i, j, v));
              }
            }
        }

        if (m_ans == 0) {
          return 0;
        }
        return m_ans + 2;
    }
};

TEST(length_of_longest_fibnacci_subsequence, t1) {
    std::vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8};
    int const out = 5;
    Solution sl;
    int const ret = sl.LenLongestFibSubseq(arr);
    //  The longest subsequence that is fibonacci-like: [1,2,3,5,8].
    EXPECT_EQ(ret, out);
}

TEST(length_of_longest_fibnacci_subsequence, t2) {
    std::vector<int> arr{1, 3, 7, 11, 12, 14, 18};
    int const out = 3;
    Solution sl;
    int const ret = sl.LenLongestFibSubseq(arr);
    // The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or
    // [7,11,18].
    EXPECT_EQ(ret, out);
}

TEST(length_of_longest_fibnacci_subsequence, t3) {
    std::vector<int> arr{2, 4, 7, 8, 9, 10, 14, 15, 18, 23, 32, 50};
    // 4 10 14 18 32
    int const out = 5;
    Solution sl;
    int const ret = sl.LenLongestFibSubseqV2(arr);
    // The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or
    // [7,11,18].
    EXPECT_EQ(ret, out);
}

}  // namespace
