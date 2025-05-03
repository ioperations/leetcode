/*
 * A happy string is a string that:
 * consists only of letters of the set ['a', 'b', 'c'].
 * s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is
 * 1-indexed). For example, strings "abc", "ac", "b" and "abcbabcbcb" are all
 happy
 * strings and strings "aa", "baa" and "ababbc" are not happy strings.
 *
 * Given two integers n and k, consider a list of all happy strings of length n
 * sorted in lexicographical order.
 *
 * Return the kth string of this list or return an empty string if there are
 less
 * than k happy strings of length n.
 *
 */

#include <string>
#include <vector>
using namespace std;

class Solution {
   public:
    string GetHappyString(int n, int k) {
      // 1 <= n <= 10
      // 1 <= k <= 100
      string const ret;

      vector<string> all;
      string cur(n, '0');
      Gen(all, cur, '0', 0, n);
      if (k > all.size()) {
        return "";
      }
      return all[k - 1];
    }

    void Gen(vector<string>& list, string& cur, char last, int index, int n) {
        if (index >= n) {
            list.push_back(cur);
            return;
        }
        for (int i = 0; i < 3; i++) {
          char const now = 'a' + i;
          if (now == last) {
            continue;
            }
            cur[index] = now;
            Gen(list, cur, now, index + 1, n);
        }
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    int n = 1, k = 3;
    string const output = "c";
    Solution sl;
    auto ret = sl.GetHappyString(n, k);
    EXPECT_EQ(ret, output);
    // The list ["a", "b", "c"] contains all happy strings of length 1. The
    // third string is "c".
}

TEST(t0, t2) {
    int n = 1, k = 4;
    string const output = "";
    Solution sl;
    auto ret = sl.GetHappyString(n, k);
    EXPECT_EQ(ret, output);
    //  There are only 3 happy strings of length 1.
}
TEST(t0, t3) {
    int n = 3, k = 9;
    string const output = "cab";
    Solution sl;
    auto ret = sl.GetHappyString(n, k);
    EXPECT_EQ(ret, output);
    // There are 12 different happy string of length 3 ["aba", "abc", "aca",
    // "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will
    // find the 9th string = "cab"
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
