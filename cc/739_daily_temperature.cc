// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of integers temperatures represents the daily temperatures,
   return an array answer such that answer[i] is the number of days you have to
   wait after the ith day to get a warmer temperature. If there is no future day
   for which this is possible, keep answer[i] == 0 instead.

*/
#include <vector>
#include <string>

using namespace std;
#include <stack>

#include "gtest/gtest.h"

namespace { 
class Solution {
   public:
    vector<int> DailyTemperatures(vector<int> &temperatures) {
        int size = temperatures.size();

        vector<int> ret(size, 0);
        stack<int> stack;

        for (int i = 0; i < size; i++) {
            while (stack.size() &&
                   temperatures[stack.top()] < temperatures[i]) {
                ret[stack.top()] = i - stack.top();
                stack.pop();
            }
            stack.push(i);
        }

        return ret;
    }
};



TEST(t0, t1) {
    std::vector<int> temperatures{73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> output{1, 1, 4, 2, 1, 1, 0, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> temperatures{30, 40, 50, 60};
    vector<int> output{1, 1, 1, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    std::vector<int> temperatures{30, 60, 90};
    vector<int> output{1, 1, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

}
