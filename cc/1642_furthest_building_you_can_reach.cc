// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an integer array heights representing the heights of buildings,
some bricks, and some ladders.

You start your journey from building 0 and move to the next building by possibly
using bricks or ladders.

While moving from building i to building i+1 (0-indexed),

If the current building's height is greater than or equal to the next building's
height, you do not need a ladder or bricks. If the current building's height is
less than the next building's height, you can either use one ladder or (h[i+1] -
h[i]) bricks. Return the furthest building index (0-indexed) you can reach if
you use the given ladders and bricks optimally*/
#include <functional>
#include <map>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

#include<gtest/gtest.h>
namespace { 
class Solution {
   public:
    int FurthestBuilding(vector<int> &heights, int bricks, int ladders) {
        // pass
        int size = heights.size();

        map<tuple<int, int, int>, int> cache;

        // 在当前的位置上，根据自身条件，最多能向前走几步
        function<int(int, int, int)> fun = [&](int i, int bricks,
                                               int ladders) -> int {
            if ((i + 1) >= size) return 0;

            int candidates = -1;
            int candidates2 = -1;
            if (heights[i + 1] <= heights[i]) {
                return 1 + fun(i + 1, bricks, ladders);
            }
            if (ladders > 0) {
                candidates = 1 + fun(i + 1, bricks, ladders - 1);
            }
            int minus = heights[i + 1] - heights[i];
            if (minus <= bricks) {
                candidates2 = 1 + fun(i + 1, bricks - minus, ladders);
            }
            return max(candidates2, candidates);
        };

        return fun(0, bricks, ladders);
    }

    int FurthestBuilding2(vector<int> &heights, int bricks, int ladders) {
        int total_count = 0;
        priority_queue<int> max_heap;
        for (int i = 0; i < (int)heights.size() - 1; i++) {
            // If height of next building is smaller jump on it
            if (heights[i] >= heights[i + 1]) {
                continue;
            }  // Difference between both heights
            int diff = heights[i + 1] - heights[i];

            // Total count of bricks needed
            total_count += diff;

            // If count of bricks is greater than existing bricks return the
            // current height as no ladder is remaining
            if (ladders == 0 && total_count > bricks) return i;

            // If count of bricks is lesser than existing bricks move to
            // next building
            if (ladders == 0 && total_count <= bricks) continue;

            // Insert the current differnce into maxheap to retrive the
            // highest diff if needed for the ladder
            max_heap.push(diff);

            // If total count of bricks is greater than the max bricks
            // retrive the highest diff and use ladder and delete it from
            // total count
            if (total_count > bricks) {
                total_count -= max_heap.top();
                max_heap.pop();
                ladders--;
            }
        }
        // Return the last element as it reached till the end
        return heights.size() - 1;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> heights{4, 2, 7, 6, 9, 14, 12};
    int bricks = 5, ladders = 1;

    Solution sl;
    int ret = sl.FurthestBuilding2(heights, bricks, ladders);
    /*
        Starting at building 0, you can follow these steps:
        - Go to building 1 without using ladders nor bricks since 4 >= 2.
        - Go to building 2 using 5 bricks. You must use either bricks or ladders
       because 2 < 7.
        - Go to building 3 without using ladders nor bricks since 7 >= 6.
        - Go to building 4 using your only ladder. You must use either bricks or
       ladders because 6 < 9. It is impossible to go beyond building 4 because
       you do not have any more bricks or ladders.
    */
    EXPECT_EQ(ret, 4);
}

TEST(t0, t2) {
    vector<int> heights{4, 12, 2, 7, 3, 18, 20, 3, 19};
    int bricks = 10, ladders = 2;

    Solution sl;
    int ret = sl.FurthestBuilding2(heights, bricks, ladders);
    EXPECT_EQ(ret, 7);
}

TEST(t0, t3) {
    vector<int> heights{14, 3, 19, 3};
    int bricks = 17, ladders = 0;

    Solution sl;
    int ret = sl.FurthestBuilding2(heights, bricks, ladders);
    EXPECT_EQ(ret, 3);
}

}
