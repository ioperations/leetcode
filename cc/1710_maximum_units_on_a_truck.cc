// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are assigned to put some amount of boxes onto one truck. You are given a
2D array boxTypes, where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:

numberOfBoxesi is the number of boxes of type i.
numberOfUnitsPerBoxi is the number of units in each box of the type i.
You are also given an integer truckSize, which is the maximum number of boxes
that can be put on the truck. You can choose any boxes to put on the truck as
long as the number of boxes does not exceed truckSize.

Return the maximum total number of units that can be put on the truck.*/

#include <algorithm>
#include <vector>
#include <string>

#include "gtest/gtest.h"

using namespace std;

namespace { 
class Solution {
   public:
    static bool Comp(vector<int> &p1, vector<int> &p2) {
        return (p1[1] > p2[1]);
    }

    int MaximumUnits(vector<vector<int>> &b, int t) {
        sort(b.begin(), b.end(), Comp);

        int ret = 0, i = 0, n = b.size();

        while (t > 0 && i < n) {
            if (t >= b[i][0]) {
                ret += b[i][0] * b[i][1];
                t -= b[i][0];
            } else {
                ret += b[i][1] * t;
                t = 0;
            }
            i++;
        }

        return (ret);
    }
};



TEST(t0, t1) {
    vector<vector<int>> box_types = {{1, 3}, {2, 2}, {3, 1}};
    int truck_size = 4;
    int output = 8;
    Solution sl;
    int ret = sl.MaximumUnits(box_types, truck_size);
    EXPECT_EQ(ret, output);
    // Explanation: There are:
    // - 1 box of the first type that contains 3 units.
    // - 2 boxes of the second type that contain 2 units each.
    // - 3 boxes of the third type that contain 1 unit each.
    // You can take all the boxes of the first and second types, and one box of
    // the third type. The total number of units will be = (1 * 3) + (2 * 2) +
    // (1 * 1) = 8.
}

TEST(t0, t2) {
    vector<vector<int>> box_types = {{5, 10}, {2, 5}, {4, 7}, {3, 9}};
    int truck_size = 10;
    int output = 91;
    Solution sl;
    int ret = sl.MaximumUnits(box_types, truck_size);
    EXPECT_EQ(ret, output);
}

}
