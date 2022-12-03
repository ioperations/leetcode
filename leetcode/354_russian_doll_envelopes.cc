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
#include <map>
#include <vector>
using namespace std;
class Solution {
   public:
    bool static Comp(pair<int, int>& a, pair<int, int>& b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    }

    int MaxEnvelopes(vector<vector<int>>& env) {
        int n = env.size();
        vector<pair<int, int>> vec;
        for (int i = 0; i < n; i++) vec.push_back({env[i][0], env[i][1]});
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<vector<int>> envelopes = {{5, 4}, {6, 4}, {6, 7}, {2, 3}};
    int output = 3;

    Solution sl;
    // The maximum number of envelopes you can Russian doll is 3 ([2,3] => [5,4]
    // => [6,7]).
    int ret = sl.MaxEnvelopes(envelopes);
    EXPECT_EQ(ret, output);
}
TEST(t0, t2) {
    std::vector<vector<int>> envelopes = {{1, 1}, {1, 1}, {1, 1}};
    int output = 1;

    Solution sl;
    int ret = sl.MaxEnvelopes(envelopes);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
