/**
 * You are given a 0-indexed array of n integers differences, which describes
 * the differences between each pair of consecutive integers of a hidden
 * sequence of length (n + 1). More formally, call the hidden sequence hidden,
 * then we have that differences[i] = hidden[i + 1] - hidden[i].
 *
 * You are further given two integers lower and upper that describe the
 * inclusive range of values [lower, upper] that the hidden sequence can
 * contain.
 *
 * For example, given differences = [1, -3, 4], lower = 1, upper = 6, the hidden
 * sequence is a sequence of length 4 whose elements are in between 1 and 6
 * (inclusive). [3, 4, 1, 5] and [4, 5, 2, 6] are possible hidden sequences. [5,
 * 6, 3, 7] is not possible since it contains an element greater than 6. [1, 2,
 * 3, 4] is not possible since the differences are not correct. Return the
 * number of possible hidden sequences there are. If there are no possible
 * sequences, return 0.
 */

#include <algorithm>
#include <vector>
using namespace std;

class Solution {
   public:
    int NumberOfArrays(vector<int>& differences, int lower, int upper) {
        // n == differences.length
        // 1 <= n <= 105
        // -105 <= differences[i] <= 105
        // -105 <= lower <= upper <= 105
        int start = lower;

        int lowerlst = lower;
        int upperlst = lower;

        for (auto& diff : differences) {
            start = start + diff;
            lowerlst = std::min(lowerlst, start);
            upperlst = std::max(upperlst, start);
            if (upper - (upperlst + (lower - lowerlst)) < 0) {
                return 0;
            }
        }

        return std::max(0, upper - (upperlst + (lower - lowerlst)) + 1);
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    vector<int> differences = {1, -3, 4};
    int lower = 1, upper = 6;
    int const output = 2;
    Solution sl;
    int const ret = sl.NumberOfArrays(differences, lower, upper);
    EXPECT_EQ(ret, output);
    // Explanation: The possible hidden sequences are:
    // - [3, 4, 1, 5]
    // - [4, 5, 2, 6]
    // Thus, we return 2.
}

TEST(t0, t2) {
    vector<int> differences = {3, -4, 5, 1, -2};
    int lower = -4, upper = 5;
    int const output = 4;
    Solution sl;
    int const ret = sl.NumberOfArrays(differences, lower, upper);
    EXPECT_EQ(ret, output);
    // Explanation: The possible hidden sequences are:
    // [-3, 0, -4, 1, 2, 0]
    // - [-2, 1, -3, 2, 3, 1]
    // - [-1, 2, -2, 3, 4, 2]
    // - [0, 3, -1, 4, 5, 3]
    // Thus, we return 4.
}

TEST(t0, t3) {
    vector<int> differences = {4, -7, 2};
    int lower = 3, upper = 6;
    int const output = 0;
    Solution sl;
    int const ret = sl.NumberOfArrays(differences, lower, upper);
    EXPECT_EQ(ret, output);
    // There are no possible hidden sequences. Thus, we return 0.
}

TEST(t0, t4) {
    vector<int> differences = {83702, -5216};
    int lower = -82788, upper = 14602;
    int const output = 13689;
    Solution sl;
    int const ret = sl.NumberOfArrays(differences, lower, upper);
    EXPECT_EQ(ret, output);
    // There are no possible hidden sequences. Thus, we return 0.
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
