// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given a 0-indexed integer array nums representing the contents of a
pile, where nums[0] is the topmost element of the pile.

In one move, you can perform either of the following:

If the pile is not empty, remove the topmost element of the pile.
If there are one or more removed elements, add any one of them back onto the
pile. This element becomes the new topmost element. You are also given an
integer k, which denotes the total number of moves to be made.

Return the maximum value of the topmost element of the pile possible after
exactly k moves. In case it is not possible to obtain a non-empty pile after k
moves, return -1.*/

#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int MaximumTop(vector<int> &nums, int k) {
        // sloution v1
        int z_max = -1;
        if (nums.size() == 1 && k % 2 == 1) return -1;
        if (k == 1 || k == 0) return nums[k];
        for (int i = 0; i < (int)nums.size(); i++) {
            if (nums[i] > z_max) z_max = nums[i];
            k--;
            if (k <= 1) {
                if (nums[i + 2] > z_max) return nums[i + 2];
                break;
            }
        }
        return z_max;
    }
};

TEST(maximize_the_topmost_element_adter_k_moves, t1) {
    std::vector<int> nums{5, 2, 2, 4, 0, 6};
    int k = 4;
    int output = 5;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /*One of the ways we can end with 5 at the top of the pile after 4 moves is
    as follows:
    - Step 1: Remove the topmost element = 5. The pile becomes [2,2,4,0,6].
    - Step 2: Remove the topmost element = 2. The pile becomes [2,4,0,6].
    - Step 3: Remove the topmost element = 2. The pile becomes [4,0,6].
    - Step 4: Add 5 back onto the pile. The pile becomes [5,4,0,6].
    Note that this is not the only way to end with 5 at the top of the pile. It
    can be shown that 5 is the largest answer possible after 4 moves.
    */
    EXPECT_EQ(ret, output);
}

TEST(maximize_the_topmost_element_adter_k_moves, t2) {
    std::vector<int> nums{2};
    int k = 1;
    int output = -1;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /* In the first move, our only option is to pop the topmost element of the
    pile. Since it is not possible to obtain a non-empty pile after one move, we
    return -1.*/
    EXPECT_EQ(ret, output);
}

TEST(maximize_the_topmost_element_adter_k_moves, t3) {
    std::vector<int> nums{99, 95, 68, 24, 18};
    int k = 69;
    int output = 99;
    Solution sl;
    int ret = sl.MaximumTop(nums, k);
    /* In the first move, our only option is to pop the topmost element of the
    pile. Since it is not possible to obtain a non-empty pile after one move, we
    return -1.*/
    EXPECT_EQ(ret, output);
}
}  // namespace
