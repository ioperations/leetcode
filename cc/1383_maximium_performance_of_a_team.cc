// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given two integers n and k and two integer arrays speed and efficiency
both of length n. There are n engineers numbered from 1 to n. speed[i] and
efficiency[i] represent the speed and efficiency of the ith engineer
respectively.

Choose at most k different engineers out of the n engineers to form a team with
the maximum performance.

The performance of a team is the sum of their engineers' speeds multiplied by
the minimum efficiency among their engineers.

Return the maximum performance of this team. Since the answer can be a huge
number, return it modulo 109 + 7.*/
#include <algorithm>
#include <functional>
#include <limits>
#include <queue>
#include <set>
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
    int MaxPerformance(int n, vector<int> &speed, vector<int> &efficiency,
                       int k) {
        int mod = 1e9 + 7;
        vector<pair<int, int>> candidates(n);
        // we build the pair { efficiency, speed } so that we can sort it later
        for (int i = 0; i < n; i++) candidates[i] = {efficiency[i], speed[i]};
        // sort candidates in descending order
        sort(candidates.rbegin(), candidates.rend());
        // Using Example 1:
        // speed: [2, 10, 3, 1 ,5, 8] and efficiency: [5, 4, 3, 9, 7, 2]
        // after sort, it becomes
        // candidates: [{9, 1}, {7 ,5}, {5, 2}, {4, 10}, {3, 3}, {2, 8}]
        long speed_sum = 0, ans = 0;
        // we use priority queue here with greater<int> to store the sum
        // i.e min heap (the smallest element goes on the top)
        priority_queue<int, vector<int>, greater<int>> pq;
        // iterate each pair
        for (auto &[e, s] : candidates) {
            // put the speed to priority queue
            pq.push(s);
            // add to speedSum
            speed_sum += s;
            // we only need to choose at most k engineers
            // hence if the queue size is greater than k
            // we need to remove a candidate
            if ((int)pq.size() > k) {
                // who to remove? of course the one with smallest speed
                speed_sum -= pq.top();
                pq.pop();
            }
            // a team is formed now, calculate the performance
            ans = max(ans, speed_sum * e);
        }
        return ans % mod;
    }

    int MaxPerformanceV1(int n, vector<int> &speed, vector<int> &efficiency,
                         int k) {
        // pass
        std::set<int> choose;
        auto calculate = [&](std::set<int> &list) -> int {
            int sum = 0;
            int min = std::numeric_limits<int>::max();

            for (auto &it : list) {
                min = std::min(min, efficiency[it]);
                sum += speed[it];
            }

            return min * sum;
        };

        /// * @param next 下一个可以选择的人
        /// * @param k  还剩下多少个人可以用
        /// * #param value 当前已经选择的用户可以产生多少的价值
        function<int(int, int, int)> fun = [&](int next, int k,
                                               int value) -> int {
            if (k <= 0 || next >= n) {
                return value;
            }

            // 不让他加入团队
            int v1 = fun(next + 1, k, value);
            choose.emplace(next);
            int v2 = calculate(choose);

            // 让他加入团队
            int v3 = fun(next + 1, --k, v2);
            choose.erase(next);

            return std::max({v1, v3});
        };
        return fun(0, k, 0);
    }
};

TEST(maximium_performance_of_a_team, t1) {
    int n = 6;
    vector<int> speed = {2, 10, 3, 1, 5, 8}, efficiency = {5, 4, 3, 9, 7, 2};
    int k = 2;
    int output = 60;

    /*
    Explanation:
    We have the maximum performance of the team by selecting engineer 2 (with
    speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7).
    That is, performance = (10 + 5) * min(4, 7) = 60.
    */

    Solution sl;
    int ret = sl.MaxPerformance(n, speed, efficiency, k);
    EXPECT_EQ(ret, output);
}

TEST(maximium_performance_of_a_team, t2) {
    int n = 6;
    vector<int> speed = {2, 10, 3, 1, 5, 8}, efficiency = {5, 4, 3, 9, 7, 2};
    int k = 3;
    int output = 68;

    /*This is the same example as the first but k = 3. We can select engineer 1,
     * engineer 2 and engineer 5 to get the maximum performance of the team.
     * That is, performance = (2 + 10 + 5) * min(5, 4, 7) = 68.
     */

    Solution sl;
    int ret = sl.MaxPerformance(n, speed, efficiency, k);
    EXPECT_EQ(ret, output);
}

TEST(maximium_performance_of_a_team, t3) {
    int n = 6;
    vector<int> speed = {2, 10, 3, 1, 5, 8}, efficiency = {5, 4, 3, 9, 7, 2};
    int k = 4;
    int output = 72;

    Solution sl;
    int ret = sl.MaxPerformance(n, speed, efficiency, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
