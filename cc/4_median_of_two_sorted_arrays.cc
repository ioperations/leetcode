// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include "gtest/gtest.h"

#include<vector>
namespace { 
class Solution {
   public:
    Solution(){};
    virtual ~Solution(){};

    double FindMedianSortedArrays(std::vector<int> &nums1,
                                  std::vector<int> &nums2) {
        std::vector<int> merged;
        const int size = nums1.size() + nums2.size();
        merged.reserve(size);

        std::size_t i = 0, j = 0;

        for (; i < nums1.size() || j < nums2.size();) {
            if (i < nums1.size() && j < nums2.size()) {
                if (nums1[i] < nums2[j]) {
                    merged.push_back(nums1[i]);
                    i++;
                } else {
                    merged.push_back(nums2[j]);
                    j++;
                }
            } else if (i == nums1.size()) {
                merged.push_back(nums2[j]);
                j++;
            } else if (j == nums2.size()) {
                merged.push_back(nums1[i]);
                i++;
            }
        }

        if (size % 2 == 1) {
            return merged[(size - 1) / 2];
        }

        return (double)(merged[(size - 1) / 2] + merged[(size) / 2]) / 2;
    }

   private:
};



TEST(median_of_two_sorted_arrays, t1) {
    Solution s;
    std::vector<int> nums1{1, 3};
    std::vector<int> nums2{2};
    double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_EQ(ret, 2);
}

TEST(median_of_two_sorted_arrays, t2) {
    Solution s;
    std::vector<int> nums1{1, 2};
    std::vector<int> nums2{3, 4};
    double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_EQ(ret, 2.5);
}

} // namespace
