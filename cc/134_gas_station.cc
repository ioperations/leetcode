// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
There are n gas stations along a circular route, where the amount of gas at the
ith station is gas[i].

You have a car with an unlimited gas tank and it costs cost[i] of gas to travel
from the ith station to its next (i + 1)th station. You begin the journey with
an empty tank at one of the gas stations.

Given two integer arrays gas and cost, return the starting gas station's index
if you can travel around the circuit once in the clockwise direction, otherwise
return -1. If there exists a solution, it is guaranteed to be unique
*/

#include <vector>

#include "gtest/gtest.h"

using namespace std;
#include <cstddef>

namespace {
class Solution {
   public:
    int CanCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        /*
            n == gas.length == cost.length
            1 <= n <= 105
            0 <= gas[i], cost[i] <= 104
        */
        int const n = static_cast<int>(gas.size());
        for (int i = 0; i < n; ++i) {
            int cur_gas = gas.at(i);
            for (int j = 0; j < n; ++j) {
                cur_gas -= cost.at((i + j) % n);
                if (cur_gas < 0) {
                    continue;
                }
                cur_gas += gas.at((i + j + 1) % n);
            }
            if (cur_gas > 0) {
                return i;
            }
        }
        return -1;
    }
};

class SolutionV {
   public:
    int CanCompleteCircuit(std::vector<int>& gas, std::vector<int>& cost) {
        int curr_gas = 0;
        int total_gas = 0;
        size_t start = 0;

        for (size_t i = 0; i < static_cast<size_t>(gas.size()); i++) {
            curr_gas += (gas.at(i) - cost.at(i));
            total_gas += (gas.at(i) - cost.at(i));

            if (curr_gas < 0) {
                start = i + 1;
                curr_gas = 0;
            }
        }

        if (start < static_cast<size_t>(gas.size()) && total_gas >= 0) return static_cast<int>(start);

        return -1;
    }
};

TEST(gasV, t1) {
    std::vector<int> gas = {1, 2, 3, 4, 5}, cost = {3, 4, 5, 1, 2};
    int const expected = 3;
    // Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank =
    // 0 + 4 = 4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to
    // station 0. Your tank = 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 -
    // 3 + 2 = 6 Travel to station 2. Your tank = 6 - 4 + 3 = 5 Travel to
    // station 3. The cost is 5. Your gas is just enough to travel back to
    // station 3. Therefore, return 3 as the starting index.
    Solution s;
    int const ret = s.CanCompleteCircuit(gas, cost);

    EXPECT_EQ(ret, expected);
}

TEST(gasV, t2) {
    std::vector<int> gas = {2, 3, 4}, cost = {3, 4, 3};
    int const expected = -1;
    // Start at station 3 (index 3) and fill up with 4 unit of gas. Your tank =
    // 0 + 4 = 4 Travel to station 4. Your tank = 4 - 1 + 5 = 8 Travel to
    // station 0. Your tank = 8 - 2 + 1 = 7 Travel to station 1. Your tank = 7 -
    // 3 + 2 = 6 Travel to station 2. Your tank = 6 - 4 + 3 = 5 Travel to
    // station 3. The cost is 5. Your gas is just enough to travel back to
    // station 3. Therefore, return 3 as the starting index.
    Solution s;
    int const ret = s.CanCompleteCircuit(gas, cost);
    EXPECT_EQ(ret, expected);
}

}  // namespace
