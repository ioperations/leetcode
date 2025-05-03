// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi]
represents the width and the height of an envelope.

One envelope can fit into another if and only if both the width and height of
one envelope are greater than the other envelope's width and height.

Return the maximum number of envelopes you can Russian doll (i.e., put one
inside the other).

Note: You cannot rotate an envelope.
*/

#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    bool static Comp(pair<int, int>& a, pair<int, int>& b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    }

    int MaxEnvelopes(vector<vector<int>>& env) {
      int const n = env.size();
      vector<pair<int, int>> vec;
      for (int i = 0; i < n; i++) vec.emplace_back(env[i][0], env[i][1]);
      sort(vec.begin(), vec.end(), Comp);
      vector<int> t;

      for (int i = 0; i < n; i++) {
        auto it = lower_bound(t.begin(), t.end(), vec[i].second);
        if (it == t.end())
          t.push_back(vec[i].second);
        else
          *it = vec[i].second;
        }

        return t.size();
    }
};

TEST(russian_doll_envelopes, t1) {
    std::vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int const output = 3;

    Solution sl;
    // The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4]
    // => [6,7]).
    int const ret = sl.MaxEnvelopes(envelopes);
    EXPECT_EQ(ret, output);
}
TEST(russian_doll_envelopes, t2) {
    std::vector<vector<int>> envelopes = {{1, 1}, {1, 1}, {1, 1}};
    int const output = 1;

    Solution sl;
    int const ret = sl.MaxEnvelopes(envelopes);
    EXPECT_EQ(ret, output);
}

}  // namespace
