// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an integer array nums and an integer k, return the kth largest element
in the array.

Note that it is the kth largest element in the sorted order, not the kth
distinct element.*/

#include <queue>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int FindKthLargest(vector<int> &nums, int k) {
        priority_queue<int> q;
        for (auto &ptr : nums) {
            q.push(ptr);
        }

        for (int i = 0; i < k - 1; i++) {
            q.pop();
        }
        return q.top();
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> v{3, 2, 1, 5, 6, 4};
    int k = 2;
    Solution sl;
    int ret = sl.FindKthLargest(v, k);
    EXPECT_EQ(ret, 5);
}

TEST(t0, t2) {
    std::vector<int> v{3, 2, 3, 1, 2, 4, 5, 5, 6};
    int k = 4;
    Solution sl;
    int ret = sl.FindKthLargest(v, k);
    EXPECT_EQ(ret, 4);
}

}
