// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given two integers n and k, return all possible combinations of k numbers out
of the range [1, n].

You may return the answer in any order.

*/

#include <catch2/catch_test_macros.hpp>
#include <set>
#include <vector>

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
    void Fn(int i, int k, int n, vector<int> &nums, vector<int> &v,
            vector<vector<int>> &ans) {
        // base case
        if (i > n || k == 0) {
            if (k == 0) ans.push_back(v);
            return;
        }

        // pick up the element
        v.push_back(nums[i]);
        Fn(i + 1, k - 1, n, nums, v, ans);
        v.pop_back();

        // dont pick up the element
        Fn(i + 1, k, n, nums, v, ans);
    }
    vector<vector<int>> Combine(int n, int k) {
        vector<int> v, nums(n + 1, 0);
        vector<vector<int>> ans;
        for (int i = 1; i <= n; i++) {
            nums[i] = i;
        }
        Fn(1, k, n, nums, v, ans);
        return ans;
    }
};

TEST(combinations, t1) {
    int n = 4;
    int k = 2;
    vector<vector<int>> o{
        {2, 4}, {3, 4}, {2, 3}, {1, 2}, {1, 3}, {1, 4},
    };
    std::set<vector<int>> o_set(o.begin(), o.end());
    Solution sl;
    auto ret = sl.Combine(n, k);

    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, o_set);
}
TEST(combinations, t2) {
    int n = 1;
    int k = 1;
    vector<vector<int>> o{{1}};
    std::set<vector<int>> o_set(o.begin(), o.end());
    Solution sl;
    auto ret = sl.Combine(n, k);

    set<vector<int>> ret_set(ret.begin(), ret.end());
    EXPECT_EQ(ret_set, o_set);
}

}  // namespace
