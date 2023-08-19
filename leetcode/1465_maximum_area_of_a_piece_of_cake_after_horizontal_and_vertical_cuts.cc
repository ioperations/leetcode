// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given a rectangular cake of size h x w and two arrays of integers
horizontalCuts and verticalCuts where:

horizontalCuts[i] is the distance from the top of the rectangular cake to the
ith horizontal cut and similarly, and verticalCuts[j] is the distance from the
left of the rectangular cake to the jth vertical cut. Return the maximum area of
a piece of cake after you cut at each horizontal and vertical position provided
in the arrays horizontalCuts and verticalCuts. Since the answer can be a large
number, return this modulo 109 + 7.*/

#include <gtest/gtest.h>

#include <vector>
using namespace std;
namespace { 
class Solution {
   public:
    int MaxArea(int h, int w, vector<int> &horizontal_cuts,
                vector<int> &vertical_cuts) {
        // pass
        int maxh = 0, maxv = 0;

        horizontal_cuts.push_back(0);
        horizontal_cuts.push_back(h);
        sort(horizontal_cuts.begin(), horizontal_cuts.end());
        for (int i = 1; i < (int)horizontal_cuts.size(); i++) {
            maxh = max(maxh, horizontal_cuts[i] - horizontal_cuts[i - 1]);
        }

        vertical_cuts.push_back(0);
        vertical_cuts.push_back(w);
        sort(vertical_cuts.begin(), vertical_cuts.end());
        for (int i = 1; i < (int)vertical_cuts.size(); i++) {
            maxv = max(maxv, vertical_cuts[i] - vertical_cuts[i - 1]);
        }
        return (1LL * maxh * maxv) %
               1000000007;  // 1LL used to make the product long long or integer
                            // sign overflow will occur.
    }
};
} 

namespace { 
TEST(t0, t1) {
    int h = 5, w = 4;
    vector<int> horizontal_cuts = {1, 2, 4};
    vector<int> vertical_cuts = {1, 3};
    int output = 4;
    Solution sl;
    int ret = sl.MaxArea(h, w, horizontal_cuts, vertical_cuts);
    /*The figure above represents the given rectangular cake. Red lines are the
     * horizontal and vertical cuts. After you cut the cake, the green piece of
     * cake has the maximum area.*/
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    int h = 5, w = 4;
    vector<int> horizontal_cuts = {3, 1};
    vector<int> vertical_cuts = {1};
    int output = 6;
    Solution sl;
    /* The figure above represents the given rectangular cake. Red lines are the
     * horizontal and vertical cuts. After you cut the cake, the green and
     * yellow pieces of cake have the maximum area.*/
    int ret = sl.MaxArea(h, w, horizontal_cuts, vertical_cuts);
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    int h = 5, w = 4;
    vector<int> horizontal_cuts = {3};
    vector<int> vertical_cuts = {3};
    int output = 9;
    Solution sl;
    int ret = sl.MaxArea(h, w, horizontal_cuts, vertical_cuts);
    EXPECT_EQ(ret, output);
}

}
