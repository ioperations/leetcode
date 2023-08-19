// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*A car travels from a starting position to a destination which is target miles
east of the starting position.

There are gas stations along the way. The gas stations are represented as an
array stations where stations[i] = [positioni, fueli] indicates that the ith gas
station is positioni miles east of the starting position and has fueli liters of
gas.

The car starts with an infinite tank of gas, which initially has startFuel
liters of fuel in it. It uses one liter of gas per one mile that it drives. When
the car reaches a gas station, it may stop and refuel, transferring all the gas
from the station into the car.

Return the minimum number of refueling stops the car must make in order to reach
its destination. If it cannot reach the destination, return -1.

Note that if the car reaches a gas station with 0 fuel left, the car can still
refuel there. If the car reaches the destination with 0 fuel left, it is still
considered to have arrived.*/
#include <algorithm>
#include <functional>
#include <map>
#include <vector>

using namespace std;

namespace { 
class Solution {
    ///* 1 <= target, startFuel <= 109
    ///* 0 <= stations.length <= 500
    ///* 0 <= positioni <= positioni+1 < target
    ///* 1 <= fueli < 109
   public:
    /// solve
    int MinRefuelStops(int target, int start_fuel,
                       vector<vector<int>> &stations) {
        /*
           We have to create a dp table ; where dp[i] indicates the maximum
           distance we can traverse by using exactly i number of fuel stops.
           */

        int n = stations.size();

        vector<long long> dp(n + 1);

        // By Default

        dp[0] = start_fuel;

        for (int i = 0; i < n; i++) {
            // FAQ : Why the inner loop is in reverse order , if we traverse the
            // loop
            //       from forward direction , the it destroys the previous state
            //       ( Do a dry run and it is crystal clear for you)

            for (int j = i; j >= 0; j--) {
                // Condition given in the question
                if (dp[j] >= stations[i][0])
                    dp[j + 1] = max(dp[j + 1], dp[j] + stations[i][1]);
            }
        }

        for (int i = 0; i <= n; i++) {
            if (dp[i] >= target) return i;
        }
        return -1;
    }

    int MinRefuelStopsV2(int target, int start_fuel,
                         vector<vector<int>> &stations) {
        int size = stations.size();
        // 从start节点开始，带着current_fuel升汽油，到达target花费最小的加油次数
        function<int(int, int, int)> fun = [&](int start, int current_fuel,
                                               int current_route) -> int {
            // 选择加油完成接下来的路程
            // 还是不加油直接到下一站决定
            if (current_route >= target) return 0;
            int c1 = -1;
            int c2 = -1;
            if (size > start) {
                // 表明这里有加油站
                if (current_fuel < stations[start][0]) return -1;
                c1 = 1 +
                     fun(start + 1,
                         current_fuel - stations[start][0] + stations[start][1],
                         current_route + stations[start][0]);
                if (current_fuel >= stations[start][0]) {
                    c2 = fun(start + 1, current_fuel - stations[start][0],
                             current_route + stations[start][0]);
                }
            }
            if (c1 == -1) return c2;
            if (c2 == -1) return c1;
            return min(c1, c2);
        };
        return fun(0, start_fuel, 0);
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    int target = 1, start_fuel = 1;
    vector<vector<int>> stations = {};
    int output = 0;
    // Explanation: We can reach the target without refueling.
    Solution sl;
    int ret = sl.MinRefuelStops(target, start_fuel, stations);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int target = 100, start_fuel = 0;
    vector<vector<int>> stations = {{10, 100}};
    int output = -1;
    // We can not reach the target (or even the first gas station).
    Solution sl;
    int ret = sl.MinRefuelStops(target, start_fuel, stations);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int target = 100, start_fuel = 10;
    vector<vector<int>> stations = {{10, 60}, {20, 30}, {30, 30}, {60, 40}};
    int output = 2;
    /* We start with 10 liters of fuel.
    We drive to position 10, expending 10 liters of fuel.  We refuel from 0
    liters to 60 liters of gas. Then, we drive from position 10 to position 60
    (expending 50 liters of fuel), and refuel from 10 liters to 50 liters of
    gas.  We then drive to and reach the target. We made 2 refueling stops along
    the way, so we return 2.
    */
    Solution sl;
    int ret = sl.MinRefuelStops(target, start_fuel, stations);
    EXPECT_EQ(ret, output);
}

}
