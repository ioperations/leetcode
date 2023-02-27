/*Given an integer array nums, return the largest perimeter of a triangle with a
   non-zero area, formed from three of these lengths. If it is impossible to
   form any triangle of a non-zero area, return 0.

*/

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    int LargestPerimeter(vector<int> &a) {
        sort(a.begin(), a.end());
        for (int i = a.size() - 1; i > 1; --i)
            if (a[i] < a[i - 1] + a[i - 2]) return a[i] + a[i - 1] + a[i - 2];
        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {2, 1, 2};
    int const output = 5;
    Solution sl;
    int const ret = sl.LargestPerimeter(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    vector<int> nums = {1, 2, 1};
    int const output = 0;
    Solution sl;
    int const ret = sl.LargestPerimeter(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
