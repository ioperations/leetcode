// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*integer array ratings.

You are giving candies to these children subjected to the following
requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
Return the minimum number of candies you need to have to distribute the candies
to the children.*/

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int Candy(vector<int>& ratings) {
        int n = ratings.size();
        if (n == 1) return 1;
        vector<int> candies(n, 1);

        for (int i = 1; i < n; i++) {
            if (ratings[i] > ratings[i - 1]) {
                candies[i] += candies[i - 1];
            }
        }

        for (int i = n - 2; i > -1; i--) {
            if (ratings[i] > ratings[i + 1]) {
                if (candies[i] > candies[i + 1]) continue;
                candies[i] = max(candies[i], candies[i + 1]) + 1;
            }
        }

        int sum = 0;
        for (auto x : candies) {
            sum += x;
        }
        return sum;
    }
};

TEST(candy, t1) {
    vector<int> ratings{1, 0, 2};
    int output = 5;
    Solution sl;
    int ret = sl.Candy(ratings);
    /*
     *  You can allocate to the first, second and third child with 2, 1, 2
     *  candies respectively.
     */
    EXPECT_EQ(output, ret);
}

TEST(candy, t2) {
    vector<int> ratings{1, 2, 2};
    int output = 4;
    Solution sl;
    int ret = sl.Candy(ratings);
    /*
        You can allocate to the first, second and third child with 1, 2, 1
       candies respectively. The third child gets 1 candy because it satisfies
       the above two conditions.
    */
    EXPECT_EQ(output, ret);
}

}  // namespace
