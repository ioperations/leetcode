// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <algorithm>
#include <iterator>
#include <vector>

class Solution {
   public:
    std::vector<int> TwoSum(std::vector<int> &nums, int target) {
        std::vector<int> ret;
        for (size_t i = 0; i < nums.size(); ++i) {
            for (size_t j = i + 1; j < nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    return std::vector<int>{(int)i, (int)j};
                }
            }
        }

        return ret;
    }

   private:
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t1, t1) {
    Solution s;
    std::vector<int> nums{2, 7, 11, 15};
    int target = 9;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{0, 1}));
}

TEST(t1, t2) {
    Solution s;
    std::vector<int> nums{3, 2, 4};
    int target = 6;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{1, 2}));
}

TEST(t1, t3) {
    Solution s;
    std::vector<int> nums{3, 3};
    int target = 6;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{0, 1}));
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
