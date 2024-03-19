// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You have n flower seeds. Every seed must be planted first before it can begin
to grow, then bloom. Planting a seed takes time and so does the growth of a
seed. You are given two 0-indexed integer arrays plantTime and growTime, of
length n each:

plantTime[i] is the number of full days it takes you to plant the ith seed.
Every day, you can work on planting exactly one seed. You do not have to work on
planting the same seed on consecutive days, but the planting of a seed is not
complete until you have worked plantTime[i] days on planting it in total.
growTime[i] is the number of full days it takes the ith seed to grow after being
completely planted. After the last day of its growth, the flower blooms and
stays bloomed forever. From the beginning of day 0, you can plant the seeds in
any order.

Return the earliest possible day where all seeds are blooming.*/

#include <algorithm>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int EarliestFullBloom(vector<int> &plant_time, vector<int> &grow_time) {
        /*
        This solution employs plot-based (visual) calculation of total time.
        Time complexity is logarithmic: O(N*logN). Space complexity is linear:
        O(N).

        Comments. The approach relies on the following strategy.

        It is straightforward that the answer can not be less than T0 =
        sum(plantTime) + min(growTime). Thus, for optimal strategy, the plant
        with minimal growth time should be planted last. Now, we're left with
        n-1 plants where the same logic applies. Thus, we come to a conclusion
        that plants should be planted according to the reverse-sorted list of
        growth time. Now let's count time. Is T0 the final answer? No, it might
        so happen, that on each iteration the time accumulated on previous steps
        surpasses the contribution from the current step. Thus, we need to
        account for this by taking appropriate max-values. To VISUALLY calculate
        the minimal time according the strategy above, just run this code that
        will basically plot the timeline. The length of the longest string is
        the answer.
        */
        /*
            def earliestFullBloom(self, plantTime: List[int], growTime:
        List[int]) -> int:

                acc_plant = 0   # accumulated plant time on each step
                min_time = 0
                for grow, cur_plant in reversed(sorted(zip(growTime,
        plantTime))): log_str = " " * acc_plant + "." * cur_plant + "^" * grow
                                print(log_str)
                    acc_plant += cur_plant
                    min_time = max(min_time, len(log_str))

                    return min_time
        For example, for plantTime = [1,4,3,2] and growTime = [2,6,1,8], it
        produces the following output:

        ..^^^^^^^^
          ....^^^^^^
              .^^
               ...^
        From the plot, it's clear what the answer is.

        ✅ NICE, HUH? UPVOTING WILL HELP PROMOTING THIS SOLUTION TO OTHERS.    }

        */
        vector<pair<int, int>> pairs;
        for (auto i = 0; i < (int)plant_time.size(); ++i)
            pairs.emplace_back(grow_time[i], plant_time[i]);

        // nice trick with reverse iterators for reverse sorting
        sort(pairs.rbegin(), pairs.rend());

        int c = 0, t = 0;
        for (auto [g, p] : pairs) {
            c += p;
            t = max(t, c + g);
        }

        return t;
    }
};

TEST(earliest_possibly_day_of_full_bloom, t1) {
    vector<int> plant_time = {1, 4, 3}, grow_time = {2, 3, 1};
    int output = 9;
    /*
    Explanation: The grayed out pots represent planting days, colored pots
    represent growing days, and the flower represents the day it blooms. One
    optimal way is: On day 0, plant the 0th seed. The seed grows for 2 full
    days and blooms on day 3. On days 1, 2, 3, and 4, plant the 1st seed.
    The seed grows for 3 full days and blooms on day 8. On days 5, 6, and 7,
    plant the 2nd seed. The seed grows for 1 full day and blooms on day 9.
    Thus, on day 9, all the seeds are blooming.
    */

    Solution sl;

    int ret = sl.EarliestFullBloom(plant_time, grow_time);
    EXPECT_EQ(ret, output);
}

TEST(earliest_possibly_day_of_full_bloom, t2) {
    vector<int> plant_time = {1, 2, 3, 2}, grow_time = {2, 1, 2, 1};
    int output = 9;
    /*
    Explanation: The grayed out pots represent planting days, colored pots
    represent growing days, and the flower represents the day it blooms. One
    optimal way is: On day 1, plant the 0th seed. The seed grows for 2 full
    days and blooms on day 4. On days 0 and 3, plant the 1st seed. The seed
    grows for 1 full day and blooms on day 5. On days 2, 4, and 5, plant the
    2nd seed. The seed grows for 2 full days and blooms on day 8. On days 6
    and 7, plant the 3rd seed. The seed grows for 1 full day and blooms on
    day 9. Thus, on day 9, all the seeds are blooming.    int output = 9;
    */

    Solution sl;

    int ret = sl.EarliestFullBloom(plant_time, grow_time);
    EXPECT_EQ(ret, output);
}

TEST(earliest_possibly_day_of_full_bloom, t3) {
    vector<int> plant_time = {1}, grow_time = {1};
    int output = 2;
    /*
    Explanation: On day 0, plant the 0th seed. The seed grows for 1 full day
    and blooms on day 2. Thus, on day 2, all the seeds are blooming
    */
    Solution sl;

    int ret = sl.EarliestFullBloom(plant_time, grow_time);
    EXPECT_EQ(ret, output);
}
}  // namespace
