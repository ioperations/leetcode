// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Winter is coming! During the contest, your first job is to design a standard
heater with a fixed warm radius to warm all the houses.

Every house can be warmed, as long as the house is within the heater's warm
radius range.

Given the positions of houses and heaters on a horizontal line, return the
minimum radius standard of heaters so that those heaters could cover all houses.

Notice that all the heaters follow your radius standard, and the warm radius
will the same.*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    bool IsValid(int radius, vector<int>& houses, vector<int>& heaters) {
        int i = 0, j = 0;
        while (i < static_cast<int>(houses.size()) && j < static_cast<int>(heaters.size())) {
            if (houses.at(i) >= (heaters.at(j) - radius) &&
                houses.at(i) <= (heaters.at(j) + radius)) {
                i++;
            }

            else {
                j++;
            }
        }

        return i == static_cast<int>(houses.size());
    }

    int FindRadius(vector<int>& houses, vector<int>& heaters) {
        int lo = 0, hi = 1e9;
        int mid = 0;
        int ans = -1;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());

        while (lo <= hi) {
            mid = lo + (hi - lo) / 2;
            if (IsValid(mid, houses, heaters)) {
                ans = mid;
                hi = mid - 1;
            }

            else {
                lo = mid + 1;
            }
        }

        return ans;
    }
};

TEST(Heaters, t1) {
    vector<int> houses = {1, 2, 3};
    vector<int> heaters = {2};
    int const output = 1;
    Solution sl;
    int const ret = sl.FindRadius(houses, heaters);
    // The only heater was placed in the position 2, and if we use the radius 1
    // standard, then all the houses can be warmed.
    EXPECT_EQ(ret, output);
};

TEST(Heaters, t2) {
    vector<int> houses = {1, 2, 3, 4};
    vector<int> heaters = {1, 4};
    int const output = 1;
    Solution sl;
    int const ret = sl.FindRadius(houses, heaters);
    // The two heater was placed in the position 1 and 4. We need to use radius
    // 1 standard, then all the houses can be warmed.
    EXPECT_EQ(ret, output);
};

TEST(Heaters, t3) {
    vector<int> houses = {1, 5};
    vector<int> heaters = {2};
    int const output = 3;
    Solution sl;
    int const ret = sl.FindRadius(houses, heaters);
    EXPECT_EQ(ret, output);
};

}  // namespace
