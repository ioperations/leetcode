// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*An integer array original is transformed into a doubled array changed by
appending twice the value of every element in original, and then randomly
shuffling the resulting array.

Given an array changed, return original if changed is a doubled array. If
changed is not a doubled array, return an empty array. The elements in original
may be returned in any order.*/
#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
   public:
    std::vector<int> FindOriginalArray(std::vector<int>& changed) {
        unordered_map<int, int> freq{};
        vector<int> result{};

        sort(changed.begin(), changed.end());

        for (int const& val : changed) freq[val]++;

        for (int const& val : changed) {
            if (freq[val] <= 0) continue;

            freq[val]--;

            if (freq[2 * val] > 0) {
                freq[2 * val]--;
                result.push_back(val);
                continue;
            }

            break;
        }

        if (2 * result.size() != changed.size()) return {};

        return result;
    }
};

#include <set>

TEST(find_original_array_from_doubled_array, t1) {
    std::vector<int> changed = {1, 3, 4, 2, 6, 8};
    std::vector<int> output = {1, 3, 4};
    std::set<int> const output_set(output.begin(), output.end());
    // Explanation: One possible original array could be [1,3,4]:
    // - Twice the value of 1 is 1 * 2 = 2.
    // - Twice the value of 3 is 3 * 2 = 6.
    // - Twice the value of 4 is 4 * 2 = 8.
    // Other original arrays could be [4,3,1] or [3,1,4].

    Solution sl;
    auto ret = sl.FindOriginalArray(changed);
    std::set<int> const ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
}

TEST(find_original_array_from_doubled_array, t2) {
    std::vector<int> changed = {6, 3, 0, 1};
    std::vector<int> output = {};
    std::set<int> const output_set(output.begin(), output.end());
    // changed is not a doubled array.

    Solution sl;
    auto ret = sl.FindOriginalArray(changed);
    std::set<int> const ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
}

TEST(find_original_array_from_doubled_array, t3) {
    std::vector<int> changed = {1};
    std::vector<int> output = {};
    std::set<int> const output_set(output.begin(), output.end());
    // changed is not a doubled array.
    Solution sl;
    auto ret = sl.FindOriginalArray(changed);
    std::set<int> const ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, output_set);
}

}  // namespace
