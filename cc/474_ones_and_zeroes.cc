// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array of binary strings strs and two integers m and n.

Return the size of the largest subset of strs such that there are at most m 0's
and n 1's in the subset.

A set x is a subset of a set y if all elements of x are also elements of y.

*/

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) concat2(a, b)
#define concat2(a, b) a##b
#define symbol(a) symbol2(a)
#define symbol2(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;
namespace {
class Solution {
   public:
    int FindMaxForm(vector<std::string> &strs, int m, int n) {
        vector<string> strings = {""};
        strings.insert(strings.end(), strs.begin(), strs.end());

        vector<vector<vector<int>>> arr(
            strings.size(), vector<vector<int>>(m + 1, vector<int>(n + 1)));

        for (int i = 0; i < (int)strings.size(); i++) {
            string now = strings[i];
            int zeros = count(now.begin(), now.end(), '0');
            int ones = count(now.begin(), now.end(), '1');

            for (int j = 0; j <= m; j++) {
                for (int k = 0; k <= n; k++) {
                    if (i == 0 || (j == 0 && k == 0))
                        arr[i][j][k] = 0;
                    else if (zeros <= j && ones <= k) {
                        arr[i][j][k] = max(1 + arr[i - 1][j - zeros][k - ones],
                                           arr[i - 1][j][k]);
                    } else
                        arr[i][j][k] = arr[i - 1][j][k];
                }
            }
        }

        return arr[strings.size() - 1][m][n];
    }
    int FindMaxFormV1(vector<std::string> &strs, int m, int n) {
        // pass
        vector<pair<int /* length of 1 */, int /* length of 0 */>> strs_count;
        strs_count.reserve(strs.size());

        for (auto &ptr : strs) {
            // int first = std::count(ptr.begin(), ptr.end(), [](const char c) {
            // return c == '1'; });
            int first = 0;
            int second = ptr.size() - first;
            strs_count.push_back(make_pair(first, second));
        }

        return 0;
    }
};



TEST(ones_and_zeroes, t1) {
    vector<string> strs = {"10", "0001", "111001", "1", "0"};
    int m = 5, n = 3;
    int output = 4;
    // Explanation: The largest subset with at most 5 0's and 3 1's is {"10",
    // "0001", "1", "0"}, so the answer is 4. Other valid but smaller subsets
    // include {"0001", "1"} and {"10", "1", "0"}. {"111001"} is an invalid
    // subset because it contains 4 1's, greater than the maximum of 3. Example
    // 2:

    Solution sl;
    int ret = sl.FindMaxForm(strs, m, n);
    EXPECT_EQ(ret, output);
}

TEST(ones_and_zeroes, t2) {
    vector<string> strs = {"10", "0", "1"};
    int m = 1, n = 1;
    int output = 2;
    // Explanation: The largest subset is {"0", "1"}, so the answer is 2.
    Solution sl;
    int ret = sl.FindMaxForm(strs, m, n);
    EXPECT_EQ(ret, output);
}

} // namespace
