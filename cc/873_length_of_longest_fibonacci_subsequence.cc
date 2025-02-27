/*A sequence x1, x2, ..., xn is Fibonacci-like if:

n >= 3
xi + xi+1 == xi+2 for all i + 2 <= n
Given a strictly increasing array arr of positive integers forming a sequence,
return the length of the longest Fibonacci-like subsequence of arr. If one does
not exist, return 0.

A subsequence is derived from another sequence arr by deleting any number of
elements (including none) from arr, without changing the order of the remaining
elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].

*/

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
   public:
    int lenLongestFibSubseq(vector<int> &arr) {
        /*
         * 3 <= arr.length <= 1000
         * 1 <= arr[i] < arr[i + 1] <= 109
         */
        size = arr.size();
        for (size_t i = 0; i < size; ++i) {
            valueToIndex[arr[i]] = i;
        }
        this->arr = arr;
        auto v = Next(0, 0, 0, 0);
        if (v <= 2) {
            return 0;
        }
        return v;
    }

    size_t Next(int index, int now, int next, int currLen) {
        if (index >= size) {
            return currLen;
        }
        if (currLen == 0) {
            return max(Next(index + 1, now, next, currLen),
                       Next(index + 1, arr[index], next, 1));
        }

        if (currLen == 1) {
            return max(Next(index + 1, arr[index], now + arr[index], 2),
                       Next(index + 1, now, next, 1));
        }

        auto it = valueToIndex.find(next);
        if (it == valueToIndex.end()) {
            return currLen;
        }

        return Next(it->second + 1, next, next + now, currLen + 1);
    }

    unordered_map<int, int> valueToIndex;
    vector<int> arr;
    size_t size = 0;
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    int output = 5;
    Solution sl;
    auto ret = sl.lenLongestFibSubseq(arr);
    EXPECT_EQ(ret, output);
    // Explanation: The longest subsequence that is fibonacci-like: [1,2,3,5,8].
}

TEST(t0, t2) {
    vector<int> arr = {1, 3, 7, 11, 12, 14, 18};
    int output = 3;
    Solution sl;
    auto ret = sl.lenLongestFibSubseq(arr);
    EXPECT_EQ(ret, output);
    // The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or
}

TEST(t0, t3) {
    vector<int> arr = {2392, 2545, 2666, 5043, 5090, 5869, 6978, 7293, 7795};
    int output = 0;
    Solution sl;
    auto ret = sl.lenLongestFibSubseq(arr);
    EXPECT_EQ(ret, output);
    // The longest subsequence that is fibonacci-like: [1,11,12], [3,11,14] or
}
int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
