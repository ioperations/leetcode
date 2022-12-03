/*
You are playing a simplified PAC-MAN game on an infinite 2-D grid. You start
at the point [0, 0], and you are given a destination point target = [xtarget,
ytarget] that you are trying to get to. There are several ghosts on the map with
their starting positions given as a 2D array ghosts, where ghosts[i] = [xi, yi]
represents the starting position of the ith ghost. All inputs are integral
coordinates.

Each turn, you and all the ghosts may independently choose to either move 1 unit
in any of the four cardinal directions: north, east, south, or west, or stay
still. All actions happen simultaneously.

You escape if and only if you can reach the target before any ghost reaches you.
If you reach any square (including the target) at the same time as a ghost, it
does not count as an escape.

Return true if it is possible to escape regardless of how the ghosts move,
otherwise return false.

*/

#include <vector>
using namespace std;

class Solution {
   public:
    bool EscapeGhosts(vector<vector<int>>& ghosts, vector<int>& target) {
        // pass
        /*
            1 <= ghosts.length <= 100
            ghosts[i].length == 2
            j-104 <= xi, yi <= 104
            jThere can be multiple ghosts in the same location.
            jtarget.length == 2
            -104 <= xtarget, ytarget <= 104
        */
        return true;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<vector<int>> ghosts = {{1, 0}, {0, 3}};
    std::vector<int> target = {0, 1};
    Solution sl;
    bool ret = sl.EscapeGhosts(ghosts, target);
    EXPECT_EQ(ret, true);
    // You can reach the destination (0, 1) after 1 turn, while the ghosts
    // located at (1, 0) and (0, 3) cannot catch up with you.
}

TEST(t0, t2) {
    vector<vector<int>> ghosts = {{1, 0}};
    std::vector<int> target = {2, 0};
    Solution sl;
    bool ret = sl.EscapeGhosts(ghosts, target);
    EXPECT_EQ(ret, false);
    // You need to reach the destination (2, 0), but the ghost at (1, 0) lies
    // between you and the destination.
}

TEST(t0, t3) {
    vector<vector<int>> ghosts = {{2, 0}};
    std::vector<int> target = {1, 0};
    Solution sl;
    bool ret = sl.EscapeGhosts(ghosts, target);
    EXPECT_EQ(ret, false);
    //  The ghost can reach the target at the same time as you.
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
