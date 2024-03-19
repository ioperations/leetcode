// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums and an integer k, return true if nums has a
continuous subarray of size at least two whose elements sum up to a multiple of
k, or false otherwise.

An integer x is a multiple of k if there exists an integer n such that x = n *
k. 0 is always a multiple of k.
*/

#include <unordered_map>
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
    bool CheckSubarraySum(vector<int> &nums, int k) {
        // Questions to ask the interviewer -

        // 1. So you said k is an integer? Can the k be equal to 0? Can it
        // be n-ve?
        //  ANS - k can be positive, zero or negative - consider all cases !

        // Positive case - [23, 2, 4, 6, 7],  k=6; ANS = true
        // Negative Case - [23,2,4,6,7], k= -6; ANS = true (Since n=-1 and
        // -1*-6=6) Zero Case - [0,0], k=0; ANS = true

        // 2. 'n' can be anything right? positive, negative and zero

        // Explanation of algorithm to interviewer -

        // A proof sketch:
        //  Suppose sum_i represents the running sum starting from index 0
        //  and ending at i once we find a mod that has been seen, say modk,
        //  we have:

        // current one: sum_i = m*k + modk
        // previous one: sum_j = n*k + modk
        // Thus,
        // sum_i - sum_j = (m - n) *k

        // so if two runningSum mod k have the same values, then when they
        // are subtracted, they are bound to be multiples of k

        // base checking - first check if the size of the array is less than
        // 2

        if (nums.size() < 2) return false;

        // Create a hashmap of the running_sum remainder and it's respective
        // index

        unordered_map<int, int> mp;

        // Why to insert <0,-1> for the hashmap

        // <0,-1> can allow it to return true when the runningSum%k=0,

        // for example [1,2,3] is input and k=6
        // then the remainders are [ 1,3,0] i.e runningSum = runningSum%k
        // now 1+2+3=6 which is actually a multiple of 6 and hence 0 should be
        // stored in the hashmap

        // ok - but why -1?
        //-1 is good for storing for 0 because - it will remove the case where
        // we consider only the first element which alone may be a multiple as
        // 0-(-1) is not greater than 1

        // In addition, it also avoids the first element of the array is the
        // multiple of k, since 0-(-1)=1 is not greater than 1.

        mp[0] = -1;

        int running_sum = 0;

        for (int i = 0; i < (int)nums.size(); i++) {
            running_sum += nums[i];

            if (k != 0) running_sum = running_sum % k;

            // check if the runningsum already exists in the hashmap
            if (mp.find(running_sum) != mp.end()) {
                // if it exists, then the current location minus the previous
                // location must be greater than1

                if (i - mp[running_sum] > 1) return true;
            } else {
                // otherwise if the current runningSum doesn't exist in the
                // hashmap, then store it as it maybe used later on

                mp[running_sum] = i;
            }
        }

        return false;
    }
};

TEST(continus_subarray_sum, t1) {
    vector<int> nums = {23, 2, 4, 6, 7};
    int k = 6;
    bool output = true;
    // Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum
    // up to 6.
    Solution sl;
    bool ret = sl.CheckSubarraySum(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(continus_subarray_sum, t2) {
    vector<int> nums = {23, 2, 6, 4, 7};
    int k = 6;
    bool output = true;
    // Explanation: [23, 2, 6, 4, 7] is an continuous subarray of size 5 whose
    // elements sum up to 42. 42 is a multiple of 6 because 42 = 7 * 6 and 7 is
    // an integer.
    Solution sl;
    bool ret = sl.CheckSubarraySum(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(continus_subarray_sum, t3) {
    vector<int> nums = {23, 2, 6, 4, 7};
    int k = 13;
    bool output = false;
    Solution sl;
    bool ret = sl.CheckSubarraySum(nums, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
