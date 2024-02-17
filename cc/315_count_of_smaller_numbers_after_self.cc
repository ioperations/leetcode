// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
    You are given an integer array nums and you have to return a new counts
   array. The counts array has the property where counts[i] is the number of
   smaller elements to the right of nums[i].

 */

#include <vector>
#include <string>
#include <utility>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    vector<int> CountSmaller(vector<int> &nums) {
        int size = nums.size();
        vector<int> ret(size, 0);
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                if (nums[j] < nums[i]) {
                    ret[i]++;
                }
            }
        }
        return ret;
    }

    void Merge(vector<int> &count, vector<pair<int, int>> &arr, int start,
               int mid, int end) {
        vector<pair<int, int>> tmp(end - start + 1);
        int i = start, j = mid + 1, k = 0, cnt = 0;
        // initially cnt is 0. Now suppose two arrays coming from left and right
        // parts be {2,5,6} and {1,2,3}. Mind it, they are in ascending order
        // when arr[i]=2 is checked with arr[j]=1, cnt is incremented to 1.
        // when arr[i]=2 is checked with arr[j]=2, cnt is given to
        // count[arr[i].second] += cnt as 2 is bigger than only 1 element from
        // the right now arr[i]=5 is checked with arr[j]=2, cnt is incremented
        // to 2. now arr[i]=5 is checked with arr[j]=3, cnt is incremented to 3.
        // we come out of the while loop as j=end+1
        while (i <= mid && j <= end) {
            if (arr[i].first <= arr[j].first) {
                count[arr[i].second] += cnt;
                tmp[k++] = arr[i++];
            } else {
                cnt++;
                tmp[k++] = arr[j++];
            }
        }

        while (i <= mid) {
            // we give all the remaining elements  count[arr[i].second] += cnt
            // because left and right parts are sorted in ascending order hence
            // if arr[i]=5 is bigger than 3 elements from the right, arr[i]=6
            // and if there were even more elements present, they all would have
            // been greater than 3(no of elements on the right!)
            count[arr[i].second] += cnt;
            tmp[k++] = arr[i++];
        }
        while (j <= end) tmp[k++] = arr[j++];

        for (int i = start; i <= end; i++) arr[i] = tmp[i - start];
    }

    void MergeSort(vector<int> &count, vector<pair<int, int>> &arr, int start,
                   int end) {
        if (start >= end) return;

        int mid = start + (end - start) / 2;
        MergeSort(count, arr, start, mid);
        MergeSort(count, arr, mid + 1, end);
        Merge(count, arr, start, mid, end);
    }

    vector<int> CountSmallerV1(vector<int> &nums) {
        int n = nums.size();

        vector<pair<int, int>> arr(n);
        for (int i = 0; i < n; i++) arr[i] = make_pair(nums[i], i);

        vector<int> count(n, 0);
        MergeSort(count, arr, 0, n - 1);

        return count;
    }
};



TEST(t0, t1) {
    vector<int> nums{5, 2, 6, 1};
    vector<int> output{2, 1, 1, 0};
    Solution sl;
    auto ret = sl.CountSmaller(nums);
    /*To the right of 5 there are 2 smaller elements (2 and 1).
    To the right of 2 there is only 1 smaller element (1).
    To the right of 6 there is 1 smaller element (1).
    To the right of 1 there is 0 smaller element.
    */
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums{-1};
    vector<int> output{0};
    Solution sl;
    auto ret = sl.CountSmaller(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> nums{-1, -1};
    vector<int> output{0, 0};
    Solution sl;
    auto ret = sl.CountSmaller(nums);
    EXPECT_EQ(ret, output);
}

}
