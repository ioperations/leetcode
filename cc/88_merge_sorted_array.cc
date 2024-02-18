// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*

You are given two integer arrays nums1 and nums2, sorted in non-decreasing
order, and two integers m and n, representing the number of elements in nums1
and nums2 respectively.

Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be
stored inside the array nums1. To accommodate this, nums1 has a length of m + n,
where the first m elements denote the elements that should be merged, and the
last n elements are set to 0 and should be ignored. nums2 has a length of n.

*/

#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;
namespace { 
class Solution {
   public:
    void Merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        // pass
        vector<int> numz = nums1;

        int m_it = 0;
        int n_it = 0;
        for (int i = 0; i < m + n; i++) {
            if (m_it < m && n_it < n) {
                if (numz[m_it] <= nums2[n_it]) {
                    nums1[i] = numz[m_it];
                    m_it++;
                } else {
                    nums1[i] = nums2[n_it];
                    n_it++;
                }
            } else if (m_it < m) {
                nums1[i] = numz[m_it];
                m_it++;
            } else {
                nums1[i] = nums2[n_it];
                n_it++;
            }
        }
    }
};



TEST(merge_sorted_array, t1) {
    std::vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    int m = 3;
    std::vector<int> nums2 = {2, 5, 6};
    int n = 3;

    Solution s;
    s.Merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, (std::vector<int>{1, 2, 2, 3, 5, 6}));
}

TEST(merge_sorted_array, t2) {
    std::vector<int> nums1 = {1};
    int m = 1;
    std::vector<int> nums2 = {};
    int n = 0;

    Solution s;
    s.Merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, (std::vector<int>{1}));
}

TEST(merge_sorted_array, t3) {
    std::vector<int> nums1 = {0};
    int m = 0;
    std::vector<int> nums2 = {1};
    int n = 1;

    Solution s;
    s.Merge(nums1, m, nums2, n);

    EXPECT_EQ(nums1, (std::vector<int>{1}));
}
}
