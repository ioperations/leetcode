// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an unsorted array of integers nums, return the length of the longest
consecutive elements sequence.

You must write an algorithm that runs in O(n) time.*/
#include <algorithm>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
   public:
    int LongestConsecutive(vector<int> &nums) {
        unordered_set<int> record(nums.begin(), nums.end());
        int ans = 0;
        for (int it : nums) {
            if (record.find(it) == record.end()) continue;
            int prev = it - 1, next = it + 1;
            while (record.find(prev) != record.end())
                prev--;  // walk left on the number line, erasing numbers as you
                         // go,
            while (record.find(next) != record.end())
                next++;  // walk right on the number line, erasing numbers as
                         // you go,
            ans = max(
                ans,
                next - prev -
                    1);  // and consider the length of the resulting sequence.
            record.erase(it);  // must do other wise you got tle
        }
        return ans;
        // upvote if you like    }
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> nums = {100, 4, 200, 1, 3, 2};
    int output = 4;

    // Explanation: The longest consecutive elements sequence is [1, 2, 3,
    // 4]. Therefore its length is 4.
    Solution sl;
    int ret = sl.LongestConsecutive(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    int output = 9;

    Solution sl;
    int ret = sl.LongestConsecutive(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
