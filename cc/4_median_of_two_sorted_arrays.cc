// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

#include <cstddef>
#include <vector>

#include "gtest/gtest.h"
namespace {
class Solution {
   public:
    Solution() = default;
    virtual ~Solution() = default;

    double FindMedianSortedArrays(std::vector<int>& nums1,
                                  std::vector<int>& nums2) {
        std::vector<int> merged;
        int const size = static_cast<int>(nums1.size() + nums2.size());
        merged.reserve(static_cast<size_t>(size));

        std::size_t i = 0, j = 0;

        for (; i < nums1.size() || j < nums2.size();) {
            if (i < nums1.size() && j < nums2.size()) {
                if (nums1.at(i) < nums2.at(j)) {
                    merged.push_back(nums1.at(i));
                    i++;
                } else {
                    merged.push_back(nums2.at(j));
                    j++;
                }
            } else if (i == nums1.size()) {
                merged.push_back(nums2.at(j));
                j++;
            } else if (j == nums2.size()) {
                merged.push_back(nums1.at(i));
                i++;
            }
        }

        if (size % 2 == 1) {
            return merged.at(static_cast<size_t>((size - 1) / 2));
        }

        return (static_cast<double>(merged.at(static_cast<size_t>((size - 1) / 2)) + merged.at(static_cast<size_t>(size) / 2))) / 2;
    }

   private:
};

TEST(MedianOfTwoSortedArrays, t1) {
    Solution s;
    std::vector<int> nums1{1, 3};
    std::vector<int> nums2{2};
    const double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_DOUBLE_EQ(ret, 2);
}

TEST(MedianOfTwoSortedArrays, t2) {
    Solution s;
    std::vector<int> nums1{1, 2};
    std::vector<int> nums2{3, 4};
    const double ret = s.FindMedianSortedArrays(nums1, nums2);
    EXPECT_DOUBLE_EQ(ret, 2.5);
}

}  // namespace
