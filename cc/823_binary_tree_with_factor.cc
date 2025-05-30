// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*Given an array of unique integers, arr, where each integer arr[i] is strictly
greater than 1.

We make a binary tree using these integers, and each number may be used for any
number of times. Each non-leaf node's value should be equal to the product of
the values of its children.

Return the number of binary trees we can make. The answer may be too large so
return the answer modulo 109 + 7.*/

#include <algorithm>
#include <functional>
#include <map>
#include <set>
#include <vector>

#include "gtest/gtest.h"

using namespace std;

namespace {
class Solution {
    std::map<int, int> m_cache;

   public:
    int NumFactoredBinaryTrees(vector<int>& arr) {
        // pass
        sort(arr.begin(), arr.end());
        std::set<int> set(arr.begin(), arr.end());

        // 表示从index对应的arr的值作为顶开始，向左走，能有多少组合
        function<int(int)> fun = [&](int index) -> int {
            // pass
            if (m_cache.count(index)) return m_cache[index];
            int num = 1;
            for (int i = 0; i < index; i++) {
                if ((arr[index] % arr[i]) == 0 &&
                    set.count(arr[index] / arr[i])) {
                    num += fun(i) * fun(arr[index] / arr[i]);
                }
            }
            return m_cache[index] = num;
        };

        int ret = 0;
        for (int i = 0; i < (int)arr.size(); i++) {
            ret += fun(i);
        }
        return ret;
    }
    const int m_mod = 1e9 + 7;
    int V2(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int const n = arr.size();

        vector<int> dp(n, 1);

        for (int i = 1; i < n; i++) {
            int l = 0, r = i - 1;
            while (l <= r) {
                if (arr[l] * 1LL * arr[r] == arr[i] * 1LL) {
                    if (l != r)
                        dp[i] = (dp[i] +
                                 (dp[l] * 1LL * dp[r] % m_mod * 2LL % m_mod)) %
                                m_mod;
                    else
                        dp[i] = (dp[i] + (dp[l] * 1LL * dp[r] % m_mod)) % m_mod;
                    l++, r--;
                } else if (arr[l] * 1LL * arr[r] > arr[i] * 1LL)
                    r--;
                else
                    l++;
            }
        }

        int ans = 0;
        for (auto i : dp) ans = (ans + i) % m_mod;
        return ans;
    }
};

TEST(binary_tree_with_factor, t1) {
    vector<int> arr = {2, 4};
    int const output = 3;
    Solution sl;
    int const ret = sl.V2(arr);
    // We can make these trees: [2], [4], [4, 2, 2]
    EXPECT_EQ(ret, output);
}

TEST(binary_tree_with_factor, t2) {
    vector<int> arr = {2, 4, 5, 10};
    int const output = 7;
    // We can make these trees: [2], [4], [5], [10], [4, 2, 2], [10, 2, 5], [10,
    // 5, 2].
    Solution sl;
    int const ret = sl.V2(arr);
    EXPECT_EQ(ret, output);
}

}  // namespace
