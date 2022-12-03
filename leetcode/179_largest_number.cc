/*

    Given a list of non-negative integers nums, arrange them such that they form
    the largest number and return it.

    Since the result may be very large, so you need to return a string instead
    of an integer.

*/

#include <functional>
#include <queue>
#include <string>
#include <vector>

using namespace std;
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

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    std::vector<int> nums = {10, 2};
    string output = "210";

    Solution sl;

    string ret = sl.LargestNumber(nums);
    EXPECT_EQ(ret, output);
}

TEST(t0, t2) {
    std::vector<int> nums = {3, 30, 34, 5, 9};
    string output = "9534330";

    Solution sl;

    string ret = sl.LargestNumber(nums);
    EXPECT_EQ(ret, output);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
