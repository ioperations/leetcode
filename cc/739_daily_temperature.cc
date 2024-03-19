// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of integers temperatures represents the daily temperatures,
   return an array answer such that answer[i] is the number of days you have to
   wait after the ith day to get a warmer temperature. If there is no future day
   for which this is possible, keep answer[i] == 0 instead.

*/
#include <vector>

using namespace std;
#include <stack>

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

TEST(daily_temperature, t1) {
    std::vector<int> temperatures{73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> output{1, 1, 4, 2, 1, 1, 0, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

TEST(daily_temperature, t2) {
    std::vector<int> temperatures{30, 40, 50, 60};
    vector<int> output{1, 1, 1, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

TEST(daily_temperature, t3) {
    std::vector<int> temperatures{30, 60, 90};
    vector<int> output{1, 1, 0};
    Solution sl;
    auto ret = sl.DailyTemperatures(temperatures);
    EXPECT_EQ(ret, output);
}

}  // namespace
