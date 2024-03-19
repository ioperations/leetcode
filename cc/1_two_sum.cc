// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
#include <stddef.h>

#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

namespace {
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

TEST(two_sum_v2, t1) {
    Solution s;
    std::vector<int> nums{2, 7, 11, 15};
    int target = 9;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{0, 1}));
}

TEST(two_sum_v2, t2) {
    Solution s;
    std::vector<int> nums{3, 2, 4};
    int target = 6;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{1, 2}));
}

TEST(two_sum_v2, t3) {
    Solution s;
    std::vector<int> nums{3, 3};
    int target = 6;
    auto ret = s.TwoSum(nums, target);
    EXPECT_EQ(ret, (std::vector<int>{0, 1}));
}
}  // namespace
