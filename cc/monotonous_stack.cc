// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
// 题目大概意思是说找到一个数组当中右边第一个比他大的索引的位置

#include <stack>
#include <vector>
#include <string>

#include "gtest/gtest.h"

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


TEST(t0, t1) {
    std::vector<int> nums{1, 2, 3, 4, 5, 6};
    Solution sl;
    std::vector<int> output{1, 2, 3, 4, 5, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> nums{6, 5, 4, 3, 2, 1};
    Solution sl;
    std::vector<int> output{-1, -1, -1, -1, -1, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    std::vector<int> nums{1, 9, 2, 4, 3, 1};
    Solution sl;
    std::vector<int> output{1, -1, 3, -1, -1, -1};
    auto ret = sl.Solve(nums);
    EXPECT_EQ(ret, output);
}

}
