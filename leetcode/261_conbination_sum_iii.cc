// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Find all valid combinations of k numbers that sum up to n such that the
following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the
same combination twice, and the combinations may be returned in any order.
*/

#include <vector>
using namespace std;

namespace { 
class Solution {
   public:
    vector<vector<int>> CombinationSum3(int k, int n) {
        std::vector<std::vector<int>> ans;
        Process(ans, {}, 0, 1, k, n);
        return ans;
    }

    void Process(std::vector<std::vector<int>> &ans, std::vector<int> temp,
                 int sum, int index, int k, int n) {
        if (sum == n && (int)temp.size() == k) {
            ans.push_back(temp);
            return;
        }
        if (sum > n || (int)temp.size() > k) return;
        for (int i = index; i <= 9; ++i) {
            temp.push_back(i);
            Process(ans, temp, sum + i, i + 1, k, n);
            temp.pop_back();
        }
    }
};
} 

#include <gtest/gtest.h>

#include <iostream>

namespace { 
TEST(t0, t1) {
    int k = 3, n = 7;
    std::vector<vector<int>> output = {{1, 2, 4}};

    Solution sl;
    auto ret = sl.CombinationSum3(k, n);
    // Explanation:
    EXPECT_EQ(ret, output);

    /* 1 + 2 + 4 = 7 */
    /* There are no other valid combinations. */
}
TEST(t0, t2) {
    int k = 3, n = 9;
    std::vector<vector<int>> output = {{1, 2, 6}, {1, 3, 5}, {2, 3, 4}};
    Solution sl;
    auto ret = sl.CombinationSum3(k, n);
    EXPECT_EQ(ret, output);

    /* Explanation: */
    /* 1 + 2 + 6 = 9 */
    /* 1 + 3 + 5 = 9 */
    /* 2 + 3 + 4 = 9 */
    /* There are no other valid combinations. */
}

TEST(t0, t3) {
    int k = 4, n = 1;
    std::vector<vector<int>> output = {};
    Solution sl;
    auto ret = sl.CombinationSum3(k, n);

    EXPECT_EQ(ret, output);
    // Explanation: There are no valid combinations.
    // Using 4 different numbers in the range [1,9], the smallest sum we can get
    // is 1+2+3+4 = 10 and since 10 > 1, there are no valid combination.
}

}
