// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*There are several cards arranged in a row, and each card has an associated
number of points. The points are given in the integer array cardPoints.

In one step, you can take one card from the beginning or from the end of the
row. You have to take exactly k cards.

Your score is the sum of the points of the cards you have taken.

Given the integer array cardPoints and the integer k, return the maximum score

you can obtain.

*/
#include <algorithm>
#include <functional>
#include <map>
#include <numeric>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    int MaxScore(vector<int>& card_points, int k) {
        map<tuple<int, int, int>, int> map;
        function<int(int, int, int)> fun = [&](int left, int right,
                                               int k) -> int {
            // pass
            if (k <= 0 || left > right) return 0;
            auto tuple = make_tuple(left, right, k);
            if (map.count(tuple)) return map[tuple];

            int left_res = -1;
            int right_res = -1;

            left_res = card_points[left] + fun(left + 1, right, k - 1);
            right_res = card_points[right] + fun(left, right - 1, k - 1);

            map[tuple] = max(left_res, right_res);
            return map[tuple];
        };

        return fun(0, (int)(card_points.size() - 1), k);
    }
    int MaxScoreV2(vector<int>& card_points, int k) {
        long long const sum =
            accumulate(card_points.begin(), card_points.end(), 0LL);

        int ans = 0;
        int const n = card_points.size();
        int const window_size = n - k;
        int l = 0;
        int r = 0;
        long long window_sum = 0;

        while (r < n) {
            int const right = card_points[r++];
            window_sum += right;
            while (r - l > window_size) {
                int const left = card_points[l++];
                window_sum -= left;
            }
            if (r - l == window_size) {
                ans = max(ans, (int)(sum - window_sum));
            }
        }
        return ans;
    }
};

TEST(maximum_points_you_can_obtain_from_cards, t1) {
    vector<int> card_points = {1, 2, 3, 4, 5, 6, 1};
    int const k = 3;
    int const output = 12;
    Solution sl;
    int const ret = sl.MaxScore(card_points, k);
    EXPECT_EQ(ret, output);
    // Explanation: After the first step, your score will always be 1. However,
    // choosing the rightmost card first will maximize your total score. The
    // optimal strategy is to take the three cards on the right, giving a final
    // score of 1 + 6 + 5 = 12.
}

TEST(maximum_points_you_can_obtain_from_cards, t2) {
    vector<int> card_points = {2, 2, 2};
    int const k = 2;
    int const output = 4;
    Solution sl;
    int const ret = sl.MaxScore(card_points, k);
    EXPECT_EQ(ret, output);
    // Regardless of which two cards you take, your score will always be 4.
}

TEST(maximum_points_you_can_obtain_from_cards, t3) {
    vector<int> card_points = {9, 7, 7, 9, 7, 7, 9};
    int const k = 7;
    int const output = 55;
    Solution sl;
    int const ret = sl.MaxScore(card_points, k);
    EXPECT_EQ(ret, output);
    // You have to take all the cards. Your score is the sum of points of all
    // cards.
}

TEST(maximum_points_you_can_obtain_from_cards_v2, t1) {
    vector<int> card_points = {1, 2, 3, 4, 5, 6, 1};
    int const k = 3;
    int const output = 12;
    Solution sl;
    int const ret = sl.MaxScoreV2(card_points, k);
    EXPECT_EQ(ret, output);
    // Explanation: After the first step, your score will always be 1. However,
    // choosing the rightmost card first will maximize your total score. The
    // optimal strategy is to take the three cards on the right, giving a final
    // score of 1 + 6 + 5 = 12.
}

TEST(maximum_points_you_can_obtain_from_cards_v2, t2) {
    vector<int> card_points = {2, 2, 2};
    int const k = 2;
    int const output = 4;
    Solution sl;
    int const ret = sl.MaxScoreV2(card_points, k);
    EXPECT_EQ(ret, output);
    // Regardless of which two cards you take, your score will always be 4.
}

TEST(maximum_points_you_can_obtain_from_cards_v2, t3) {
    vector<int> card_points = {9, 7, 7, 9, 7, 7, 9};
    int const k = 7;
    int const output = 55;
    Solution sl;
    int const ret = sl.MaxScoreV2(card_points, k);
    EXPECT_EQ(ret, output);
    // You have to take all the cards. Your score is the sum of points of all
    // cards.
}
}  // namespace
