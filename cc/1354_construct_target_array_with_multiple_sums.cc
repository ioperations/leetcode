// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*You are given an array target of n integers. From a starting array arr
consisting of n 1's, you may perform the following procedure :

let x be the sum of all elements currently in your array.
choose index i, such that 0 <= i < n and set the value of arr at index i to x.
You may repeat this procedure as many times as needed.
Return true if it is possible to construct the target array from arr, otherwise,
return false.*/

#include <queue>
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
    bool IsPossible(vector<int> &targets) {
        int n = targets.size();
        long s = 0;
        priority_queue<int, vector<int>> q;
        for (int i = 0; i < n; i++) s += targets[i], q.push(targets[i]);
        while (!q.empty()) {
            int now = q.top();
            q.pop();
            if (now == 1) continue;

            if (s == now || now <= s - now) return 0;
            s -= now;
            now %= s;
            if (s == 1) now = 1;
            q.push(now);
            s += now;
        }
        return 1;
    }
};

TEST(construct_target_array_with_multiple_sums, t1) {
    vector<int> target = {9, 3, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
    // Impossible to create target array from [1,1,1,1].
}

TEST(construct_target_array_with_multiple_sums, t2) {
    vector<int> target = {8, 5};
    bool output = true;
    Solution sl;
    bool ret = sl.IsPossible(target);
    EXPECT_EQ(ret, output);
}

}  // namespace
