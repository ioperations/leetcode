/*
    Given a string s, partition s such that every
    substring of the partition is a palindrome.
    Return the minimum cuts needed for a palindrome partitioning of s.
*/

#include <limits.h>

#include <map>
#include <string>
#include <unordered_map>
#include <utility>
using namespace std;

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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::string s = "aab";

    int i = 1;
    Solution sl;
    int ret = sl.MinCut(s);
    EXPECT_EQ(ret, i);
}

TEST(t0, t2) {
    std::string s = "a";

    int i = 0;
    Solution sl;
    int ret = sl.MinCut(s);
    EXPECT_EQ(ret, i);
}

TEST(t0, t3) {
    std::string s = "ab";

    int i = 1;
    Solution sl;
    int ret = sl.MinCut(s);
    EXPECT_EQ(ret, i);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
