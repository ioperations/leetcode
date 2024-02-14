// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are playing a game with integers. You start with the integer 1 and you want
to reach the integer target.

In one move, you can either:

Increment the current integer by one (i.e., x = x + 1).
Double the current integer (i.e., x = 2 * x).
You can use the increment operation any number of times, however, you can only
use the double operation at most maxDoubles times.

Given the two integers target and maxDoubles, return the minimum number of moves
needed to reach target starting with 1.
 */

#include <functional>
#include <map>
#include <utility>
#include <algorithm>
#include <string>

#include "gtest/gtest.h"

using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int MinMoves(int target, int max_doubles) {
        // pass
        std::map<pair<int, int>, int> cache;
        const int half_target = target / 2;

        function<int(int, int)> fun = [&](int now_state,
                                          int max_doubles) -> int {
            // pass
            if (max_doubles <= 0 || now_state > half_target) {
                return target - now_state;
            }

            pair<int, int> n = make_pair(now_state, max_doubles);

            if (cache.count(n)) {
                return cache[n];
            }
            cache[n] = min(1 + fun(now_state + 1, max_doubles),
                           1 + fun(now_state * 2, max_doubles - 1));

            return cache[n];
        };

        return fun(1, max_doubles);
    }

    int MinMovesV1(int target, int md) {
        int ops = 0;
        while (target != 1) {
            if (md == 0) return ops + target - 1;

            if (target % 2 == 0 && md > 0)
                target /= 2, md--;
            else
                target -= 1;

            ops++;
        }
        return ops;
    }
};



TEST(t0, t1) {
    int target = 19;
    int max_double = 2;
    int ret = 7;
    Solution sl;
    int out = sl.MinMoves(target, max_double);
    /*Initially, x = 1
    Increment 3 times so x = 4
    Double once so x = 8
    Increment once so x = 9
    Double again so x = 18
    Increment once so x = 19
    */
    EXPECT_EQ(ret, out);
}

TEST(t0, t2) {
    int target = 10;
    int max_double = 4;
    int ret = 4;
    Solution sl;
    /*
     Initially, x = 1
     Increment once so x = 2
     Double once so x = 4
     Increment once so x = 5
     Double again so x = 10
    */
    int out = sl.MinMoves(target, max_double);
    EXPECT_EQ(ret, out);
}

TEST(t0, t3) {
    int target = 5;
    int max_double = 0;
    int ret = 4;
    Solution sl;
    int out = sl.MinMoves(target, max_double);
    EXPECT_EQ(ret, out);
}

TEST(t0, t4) {
    int target = 766972377;
    int max_double = 92;
    int ret = 45;
    Solution sl;
    int out = sl.MinMovesV1(target, max_double);
    EXPECT_EQ(ret, out);
}

}
