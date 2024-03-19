// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given a sorted integer array arr, two integers k and x, return the k closest
integers to x in the array. The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:

|a - x| < |b - x|, or
|a - x| == |b - x| and a < b*/
#include <stdlib.h>

#include <algorithm>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(concat(a, b),__LINE__)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    vector<int> FindClosestElements(vector<int> &arr, int k, int x) {
        vector<int>::iterator const iter =
            lower_bound(arr.begin(), arr.end(), x);
        int j = iter - arr.begin();
        int i = j - 1;
        vector<int> ans;
        int const n = arr.size();

        while (i >= 0 && j < n && (int)ans.size() < k) {
            if (abs(x - arr[i]) <= abs(x - arr[j])) {
                ans.push_back(arr[i]);
                i--;
            } else {
                ans.push_back(arr[j]);
                j++;
            }
        }

        while (i >= 0 && ans.size() < k) {
            ans.push_back(arr[i]);
            i--;
        }

        while (j < n && (int)ans.size() < k) {
            ans.push_back(arr[j]);
            j++;
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};

TEST(find_k_closest_elements, t1) {
    vector<int> arr = {1, 2, 3, 4, 5};
    int const k = 4, x = 3;
    vector<int> const output = {1, 2, 3, 4};
    Solution sl;
    auto ret = sl.FindClosestElements(arr, k, x);
    EXPECT_EQ(ret, output);
};

TEST(find_k_closest_elements, t2) {
    vector<int> arr = {1, 2, 3, 4, 5};
    int const k = 4, x = -1;
    vector<int> const output = {1, 2, 3, 4};
    Solution sl;
    auto ret = sl.FindClosestElements(arr, k, x);
    EXPECT_EQ(ret, output);
};
}  // namespace
