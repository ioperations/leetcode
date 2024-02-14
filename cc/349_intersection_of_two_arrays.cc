// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given two integer arrays nums1 and nums2, return an array of their intersection.
Each element in the result must be unique and you may return the result in any
order.
*/
#include <algorithm>
#include <set>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    vector<int> Intersection(vector<int> &nums1, vector<int> &nums2) {
        set<int> ret;
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());

        const int size1 = nums1.size();
        const int size2 = nums2.size();

        for (int i = 0, j = 0; i < size1 && j < size2;) {
            if (nums1[i] == nums2[j]) {
                ret.emplace(nums1[i]);
                i++;
                j++;
            } else if (nums1[i] > nums2[j]) {
                j++;
            } else
                i++;
        }

        return vector<int>(ret.begin(), ret.end());
    }
};



TEST(t0, t1) {
    std::vector<int> v{1, 2, 2, 1};
    std::vector<int> v2{2, 2};
    Solution sl;
    std::vector<int> ret = sl.Intersection(v, v2);
    EXPECT_EQ(ret, std::vector<int>{2});
}

TEST(t0, t2) {
    std::vector<int> v{4, 9, 5};
    std::vector<int> v2{9, 4, 9, 8, 4};
    Solution sl;
    std::vector<int> ret = sl.Intersection(v, v2);
    EXPECT_EQ(ret, (std::vector<int>{4, 9}));
    //
}

}
