// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
// 题目大概意思是说找到一个数组当中右边第一个比他大的索引的位置

#include <stack>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    std::vector<int> Solve(vector<int> &nums) {
        int size = nums.size();
        std::vector<int> ret(size, -1);
        stack<int> stack;

        for (int i = 0; i < size; i++) {
            while (stack.size() && nums[stack.top()] < nums[i]) {
                ret[stack.top()] = i;
                stack.pop();
            }
            stack.push(i);
        }
        return ret;
    }
};

TEST(monotonous_stack, t1) {
    std::vector<int> nums{1, 2, 3, 4, 5, 6};
    Solution sl;
    std::vector<int> output{1, 2, 3, 4, 5, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

TEST(monotonous_stack, t2) {
    std::vector<int> nums{6, 5, 4, 3, 2, 1};
    Solution sl;
    std::vector<int> output{-1, -1, -1, -1, -1, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

TEST(monotonous_stack, t3) {
    std::vector<int> nums{1, 9, 2, 4, 3, 1};
    Solution sl;
    std::vector<int> output{1, -1, 3, -1, -1, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
