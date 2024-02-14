// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given two strings stamp and target. Initially, there is a string s of
length target.length with all s[i] == '?'.

In one turn, you can place stamp over s and replace every letter in the s with
the corresponding letter from stamp.

For example, if stamp = "abc" and target = "abcba", then s is "?????" initially.
In one turn you can: place stamp at index 0 of s to obtain "abc??", place stamp
at index 1 of s to obtain "?abc?", or place stamp at index 2 of s to obtain
"??abc". Note that stamp must be fully contained in the boundaries of s in order
to stamp (i.e., you cannot place stamp at index 3 of s). We want to convert s to
target using at most 10 * target.length turns.

Return an array of the index of the left-most letter being stamped at each turn.
If we cannot obtain target from s within 10 * target.length turns, return an
empty array.*/
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    bool CanReplace(string &stamp, string &target, int pos) {
        int m = stamp.size();
        for (int i = 0; i < m; i++) {
            if (target[i + pos] != '?' and target[i + pos] != stamp[i])
                return false;
        }
        return true;
    }

    int Replace(string &stamp, string &target, int pos) {
        int cnt = 0;
        int m = stamp.size();
        for (int i = 0; i < m; i++) {
            if (target[i + pos] != '?') {
                cnt++;
                target[i + pos] = '?';
            }
        }
        return cnt;
    }

    vector<int> MovesToStamp(string stamp, string target) {
        vector<int> ans;

        int m = stamp.size(), n = target.size();

        int count = 0;

        vector<int> vis(n + 1, 0);

        while (count != n) {
            bool flag = false;
            for (int i = 0; i <= n - m; i++) {
                if (!vis[i] and CanReplace(stamp, target, i)) {
                    vis[i] = 1;
                    count += Replace(stamp, target, i);
                    flag = true;
                    ans.push_back(i);
                    if (count == n) break;
                }
            }
            if (!flag) return {};
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    string stamp = "abc", target = "ababc";
    vector<int> output = {0, 2};
    /*Explanation: Initially s = "?????".
    - Place stamp at index 0 to get "abc??".
    - Place stamp at index 2 to get "ababc".
    [1,0,2] would also be accepted as an answer, as well as some other answers.
    */
    Solution sl;
    auto ret = sl.MovesToStamp(stamp, target);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    string stamp = "abca", target = "aabcaca";
    vector<int> output = {0, 3, 1};
    /*Explanation: Initially s = "???????".
    - Place stamp at index 3 to get "???abca".
    - Place stamp at index 0 to get "abcabca".
    - Place stamp at index 1 to get "aabcaca".
    */
    Solution sl;
    auto ret = sl.MovesToStamp(stamp, target);
    EXPECT_EQ(ret, output);
}

}
