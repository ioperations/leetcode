/*
You have a set of integers s, which originally contains all the numbers from 1
to n. Unfortunately, due to some error, one of the numbers in s got duplicated
to another number in the set, which results in repetition of one number and loss
of another number.

You are given an integer array nums representing the data status of this set
after the error.

Find the number that occurs twice and the number that is missing and return them
in the form of an array.
*/

#include <vector>
using namespace std;

class Solution {
   public:
    vector<int> FindErrorNums(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n + 1, 0);
        vector<int> vec;

        for (auto i : nums) {
            arr[i]++;
        }

        for (int i = 1; i < n + 1; i++) {
            if (arr[i] > 1) vec.push_back(i);
        }
        for (int i = 1; i < n + 1; i++) {
            if (arr[i] == 0) vec.push_back(i);
        }
        return vec;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 2, 2, 4};
    vector<int> output = {2, 3};

    Solution sl;
    auto ret = sl.FindErrorNums(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {1, 1};

    vector<int> const output = {1, 2};
    Solution sl;
    auto ret = sl.FindErrorNums(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
