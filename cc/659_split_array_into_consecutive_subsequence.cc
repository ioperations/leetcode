// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an integer array nums that is sorted in non-decreasing order.

Determine if it is possible to split nums into one or more subsequences such
that both of the following conditions are true:

Each subsequence is a consecutive increasing sequence (i.e. each integer is
exactly one more than the previous integer). All subsequences have a length of 3
or more. Return true if you can split nums according to the above conditions, or
false otherwise.

A subsequence of an array is a new array that is formed from the original array
by deleting some (can be none) of the elements without disturbing the relative
positions of the remaining elements. (i.e., [1,3,5] is a subsequence of
[1,2,3,4,5] while [1,3,2] is not).*/

#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IsPossible(vector<int> &nums) {
        priority_queue<int, vector<int>, greater<int>> pq;
        unordered_map<int, int> um;
        for (int &num : nums) {
            pq.push(num);
            um[num]++;
        }
        queue<int> q;
        int count = 0, prev;
        while (!pq.empty()) {
            if (count == 0) {
                prev = pq.top();
                pq.pop();
                count++;
            } else if (pq.top() == prev + 1) {
                if (um[pq.top()] >= um[prev]) {
                    um[prev]--;
                    pq.pop();
                    prev += 1;
                    count++;
                } else if (um[pq.top()] < um[prev]) {
                    um[prev]--;
                    if (count <= 2) return false;
                    while (!q.empty()) {
                        pq.push(q.front());
                        q.pop();
                    }
                    count = 0;
                }
            } else if (pq.top() == prev) {
                q.push(pq.top());
                pq.pop();
                if (pq.empty()) {
                    if (count <= 2) return false;
                    while (!q.empty()) {
                        pq.push(q.front());
                        q.pop();
                    }
                    count = 0;
                }
            } else if (pq.top() > prev + 1) {
                if (count <= 2) return false;

                while (!q.empty()) {
                    pq.push(q.front());
                    q.pop();
                }
                count = 0;
            }
        }
        if (count > 0 && count <= 2) return false;
        return true;
    }
};

TEST(split_array_into_consecutive_subsequence, t1) {
    vector<int> nums = {1, 2, 3, 3, 4, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(nums);
    /*nums can be split into the following subsequences:
    [1,2,3,3,4,5] --> 1, 2, 3
    [1,2,3,3,4,5] --> 3, 4, 5*/
    EXPECT_EQ(ret, output);
}

TEST(split_array_into_consecutive_subsequence, t2) {
    vector<int> nums = {1, 2, 3, 3, 4, 4, 5, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(nums);
    /* nums can be split into the following subsequences:
    [1,2,3,3,4,4,5,5] --> 1, 2, 3, 4, 5
    [1,2,3,3,4,4,5,5] --> 3, 4, 5*/
    EXPECT_EQ(ret, output);
}
TEST(split_array_into_consecutive_subsequence, t3) {
    vector<int> nums = {1, 2, 3, 4, 4, 5};
    bool output = false;
    Solution sl;
    bool ret = sl.IsPossible(nums);
    /*It is impossible to split nums into consecutive increasing subsequences of
     * length 3 or more.*/
    EXPECT_EQ(ret, output);
}

}  // namespace
