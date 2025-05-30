// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array target of n integers. From a starting array arr
consisting of n 1's, you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < n and set the value of arr at index i to x.
You may repeat this procedure as many times as needed.
Return true if it is possible to construct the target array from arr, otherwise,
return false.*/

#include <queue>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IsPossible(vector<int>& targets) {
        int const n = targets.size();
        long s = 0;
        priority_queue<int, vector<int>> q;
        for (int i = 0; i < n; i++) s += targets[i], q.push(targets[i]);
        while (!q.empty()) {
            int now = q.top();
            q.pop();
            if (now == 1) continue;

            if (s == now || now <= s - now) return false;
            s -= now;
            now %= s;
            if (s == 1) now = 1;
            q.push(now);
            s += now;
        }
        return true;
    }
};

TEST(construct_target_array_with_multiple_sums, t1) {
    vector<int> target = {9, 3, 5};
    bool const output = true;
    Solution sl;
    bool const ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
    // Impossible to create target array from [1,1,1,1].
}

TEST(construct_target_array_with_multiple_sums, t2) {
    vector<int> target = {8, 5};
    bool const output = true;
    Solution sl;
    bool const ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
}

}  // namespace
