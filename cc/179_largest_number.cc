// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*

    Given a list of non-negative integers nums, arrange them such that they form
    the largest number and return it.

    Since the result may be very large, so you need to return a string instead
    of an integer.

*/

#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

using namespace std;
namespace {
class Solution {
   public:
    bool static Comp(string a, string b) { return a + b > b + a; }
    string LargestNumber(vector<int>& nums) {
        vector<string> v;
        for (auto x : nums) {
            v.push_back(to_string(x));
        }
        sort(v.begin(), v.end(), Comp);
        string ans = "";
        for (auto x : v) {
            ans += x;
        }
        // boundary case when the given vector has only zero elements
        // [0,0,0,...]
        while (ans[0] == '0' and ans.length() > 1) {
            ans.erase(0, ans.size() - 1);
        }

        return ans;
    }
};

TEST(largest_number, t1) {
    std::vector<int> nums = {10, 2};
    string const output = "210";

    Solution sl;

    string const ret = sl.LargestNumber(nums);
    EXPECT_EQ(ret, output);
}

TEST(largest_number, t2) {
    std::vector<int> nums = {3, 30, 34, 5, 9};
    string const output = "9534330";

    Solution sl;

    string const ret = sl.LargestNumber(nums);
    EXPECT_EQ(ret, output);
}

}  // namespace
