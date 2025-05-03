// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    Given a string s, partition s such that every
    substring of the partition is a palindrome.
    Return the minimum cuts needed for a palindrome partitioning of s.
*/

#include <algorithm>
#include <climits>
#include <string>
#include <unordered_map>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MinCut(string s) {
        unordered_map<string, int> mp;
        return MinCut(s, mp) - 1;
    }
    int MinCut(string s, unordered_map<string, int>& mp) {
        if (s.size() == 0) return 0;

        if (mp.find(s) != mp.end()) return mp[s];

        string tmp;
        int ans = INT_MAX;
        for (int i = 0; i < (int)s.size(); i++) {
            tmp += s[i];
            if (Palindrome(tmp)) ans = min(ans, MinCut(s.substr(i + 1), mp));
        }

        return mp[s] = ans + 1;
    }

    bool Palindrome(string& s) {
        int i = 0, j = s.size() - 1;
        while (i < j)
            if (s[i++] != s[j--]) return false;

        return true;
    }
};

TEST(palindrome_partitioning_ii, t1) {
  std::string const s = "aab";

  int const i = 1;
  Solution sl;
  int const ret = sl.MinCut(s);
  EXPECT_EQ(ret, i);
}

TEST(palindrome_partitioning_ii, t2) {
  std::string const s = "a";

  int const i = 0;
  Solution sl;
  int const ret = sl.MinCut(s);
  EXPECT_EQ(ret, i);
}

TEST(palindrome_partitioning_ii, t3) {
  std::string const s = "ab";

  int const i = 1;
  Solution sl;
  int const ret = sl.MinCut(s);
  EXPECT_EQ(ret, i);
}
}  // namespace
