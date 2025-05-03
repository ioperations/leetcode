// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
A city's skyline is the outer contour of the silhouette formed by all the
buildings in that city when viewed from a distance. Given the locations and
heights of all the buildings, return the skyline formed by these buildings
collectively.

The geometric information of each building is given in the array buildings where
buildings[i] = [lefti, righti, heighti]:

lefti is the x coordinate of the left edge of the ith building.
righti is the x coordinate of the right edge of the ith building.
heighti is the height of the ith building.
You may assume all buildings are perfect rectangles grounded on an absolutely
flat surface at height 0.

The skyline should be represented as a list of "key points" sorted by their
x-coordinate in the form [[x1,y1],[x2,y2],...]. Each key point is the left
endpoint of some horizontal segment in the skyline except the last point in the
list, which always has a y-coordinate 0 and is used to mark the skyline's
termination where the rightmost building ends. Any ground between the leftmost
and rightmost buildings should be part of the skyline's contour.

Note: There must be no consecutive horizontal lines of equal height in the
output skyline. For instance, [...,[2 3],[4 5],[7 5],[11 5],[12 7],...] is not
acceptable; the three lines of height 5 should be merged into one in the final
output as such: [...,[2 3],[4 5],[12 7],...]

*/
#include <algorithm>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    vector<vector<int>> GetSkyline(vector<vector<int>>& buildings) {
        std::vector<std::pair<int, int>> coords;
        for (const auto& b : buildings) {
            // Building end is processed first if two x-coordinates are a tie.
            coords.push_back({b[0], -b[2]});
            // And add building start.
            coords.push_back({b[1], b[2]});
        }

        // Sort coordinates so buildings ending are processed before buildings
        // starting left to right.
        std::sort(coords.begin(), coords.end());

        // Frequency table for heights.
        // Key: When a height frequency is zero, the height is no longer the
        // tallest current height.
        std::map<int, int> heights;

        std::vector<std::vector<int>> xs;

        // Zero height is always available.
        heights[0] = 1;
        for (const auto& cur : coords) {
            // Building start, encounter new height.
            if (cur.second < 0)
                ++heights[-cur.second];
            else
                // Building end, height no longer available. If no other active
                // buildings have the same height, remove it.
                if (--heights[cur.second] == 0) heights.erase(cur.second);

            // Currently at building start/end x, height is the largest
            // available height.
            int const x = cur.first, y = heights.rbegin()->first;
            if (xs.size()) {
                int const prev_x = xs.back()[0], prev_y = xs.back()[1];

                // If the previous recorded height is the same as the current
                // height, skip inserting duplicate points.
                if (prev_y == y) continue;

                // If the previous point is the same one, disregard the previous
                // and replace it with the latest max height for this x
                // coordinate.
                if (prev_x == x) xs.pop_back();
            }

            xs.push_back({x, y});
        }

        return xs;
    }
};

TEST(the_skyline_problem, t1) {
    vector<vector<int>> buildings = {
        {2, 9, 10}, {3, 7, 15}, {5, 12, 12}, {15, 20, 10}, {19, 24, 8}};
    vector<vector<int>> const output = {{2, 10},  {3, 15}, {7, 12}, {12, 0},
                                        {15, 10}, {20, 8}, {24, 0}};
    /*
    Explanation:
    Figure A shows the buildings of the input.
    Figure B shows the skyline formed by those buildings. The red points in
    figure B represent the key points in the output list.
    */

    Solution sl;
    auto ret = sl.GetSkyline(buildings);
    EXPECT_EQ(ret, output);
}

TEST(the_skyline_problem, t2) {
    vector<vector<int>> buildings = {{0, 2, 3}, {2, 5, 3}};
    vector<vector<int>> const output = {{0, 3}, {5, 0}};
    /*
    Explanation:
    Figure A shows the buildings of the input.
    Figure B shows the skyline formed by those buildings. The red points in
    figure B represent the key points in the output list.
    */

    Solution sl;
    auto ret = sl.GetSkyline(buildings);
    EXPECT_EQ(ret, output);
}

}  // namespace
