// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Suppose Andy and Doris want to choose a restaurant for dinner, and they both
have a list of favorite restaurants represented by strings.

You need to help them find out their common interest with the least list index
sum. If there is a choice tie between answers, output all of them with no order
requirement. You could assume there always exists an answer.
*/

#include <climits>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    vector<string> FindRestaurant(vector<string>& list1,
                                  vector<string>& list2) {
        unordered_map<string, int> pos;
        vector<string> ans;
        int min_sum = INT_MAX;
        for (int i = 0; i < (int)list1.size(); i++) {
            string key = list1[i];
            pos[key] = i + 1;
        }
        for (int i = 0; i < (int)list2.size(); i++) {
            string st = list2[i];
            if (pos[st] > 0) {
                int sum = i + 1 + pos[st];
                if (sum < min_sum) {
                    min_sum = sum;
                    ans.clear();
                    ans.push_back(st);
                } else if (sum == min_sum) {
                    ans.push_back(st);
                }
            }
        }
        return ans;
    }
};

TEST(minimum_index_sum_of_two_lists, t1) {
    vector<string> list1 = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
    vector<string> list2 = {"Piatti", "The Grill at Torrey Pines",
                            "Hungry Hunter Steakhouse", "Shogun"};
    vector<string> output = {"Shogun"};
    // Explanation: The only restaurant they both like is "Shogun".
    Solution sl;
    auto ret = sl.FindRestaurant(list1, list2);
    EXPECT_EQ(ret, output);
}

TEST(minimum_index_sum_of_two_lists, t2) {
    vector<string> list1 = {"Shogun", "Tapioca Express", "Burger King", "KFC"};
    vector<string> list2 = {"KFC", "Shogun", "Burger King"};
    vector<string> output = {"Shogun"};
    // The restaurant they both like and have the least index sum is "Shogun"
    // with index sum 1 (0+1).
    Solution sl;
    auto ret = sl.FindRestaurant(list1, list2);
    EXPECT_EQ(ret, output);
}

}  // namespace
