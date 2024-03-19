// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
You are given an integer array nums and an integer k.
In one operation, you can pick two numbers from the array whose sum equals k and
remove them from the array.

Return the maximum number of operations you can perform on the array.
*/

#include <algorithm>
#include <unordered_map>
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
    int MaxOperations(vector<int> &nums, int sum) {
        // pass
        unordered_map<int, int> freq;
        for (int e : nums) freq[e]++;
        int ans = 0;
        for (auto &[k, v] : freq) {
            if (2 * k == sum)
                ans += v / 2, v -= v / 2 * 2;
            else if (v > 0 && freq.count(sum - k) && freq[sum - k] > 0) {
                int pair_cnt = min(v, freq[sum - k]);
                ans += pair_cnt;
                v -= pair_cnt;
                freq[sum - k] -= pair_cnt;
            }
        }
        return ans;
    }

    int MaxOperationsV2(vector<int> &nums, int k) {
        unordered_map<int, int> freq;
        int ans = 0;
        for (auto cur : nums) {
            int complement = k - cur;
            if (freq[complement] > 0) {
                ans++;
                freq[complement]--;
            } else
                freq[cur]++;
        }
        return ans;
    }

    int MaxOperationsV3(vector<int> &nums, int k) {
        sort(nums.begin(), nums.end());
        int count = 0;
        int left = 0;
        int right = nums.size() - 1;
        while (left < right && nums[left] < k) {  // pruning:  nums[left] < k
            if (nums[left] + nums[right] < k) {
                left++;
            } else if (nums[left] + nums[right] > k) {
                right--;
            } else {
                left++;
                right--;
                count++;
            }
        }
        return count;
    }
};

TEST(max_number_of_k_sum_pairs, t1) {
    std::vector<int> nums = {1, 2, 3, 4};
    int k = 5;
    int output = 2;

    /*
        Explanation: Starting with nums = [1,2,3,4]:
        - Remove numbers 1 and 4, then nums = [2,3]
        - Remove numbers 2 and 3, then nums = []
        There are no more pairs that sum up to 5, hence a total of 2 operations.
    */
    Solution sl;
    int ret = sl.MaxOperations(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(max_number_of_k_sum_pairs_v2, t1) {
    std::vector<int> nums = {1, 2, 3, 4};
    int k = 5;
    int output = 2;

    /*
        Explanation: Starting with nums = [1,2,3,4]:
        - Remove numbers 1 and 4, then nums = [2,3]
        - Remove numbers 2 and 3, then nums = []
        There are no more pairs that sum up to 5, hence a total of 2 operations.
    */
    Solution sl;
    int ret = sl.MaxOperationsV2(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(max_number_of_k_sum_pairs_v3, t1) {
    std::vector<int> nums = {1, 2, 3, 4};
    int k = 5;
    int output = 2;

    /*
        Explanation: Starting with nums = [1,2,3,4]:
        - Remove numbers 1 and 4, then nums = [2,3]
        - Remove numbers 2 and 3, then nums = []
        There are no more pairs that sum up to 5, hence a total of 2 operations.
    */
    Solution sl;
    int ret = sl.MaxOperationsV3(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(max_number_of_k_sum_pairs, t2) {
    std::vector<int> nums = {3, 1, 3, 4, 3};
    int k = 6;
    int output = 1;

    /*
        Starting with nums = [3,1,3,4,3]:
        - Remove the first two 3's, then nums = [1,4,3]
        There are no more pairs that sum up to 6, hence a total of 1 operation.
    */
    Solution sl;
    int ret = sl.MaxOperations(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(max_number_of_k_sum_pairs_v2, t2) {
    std::vector<int> nums = {3, 1, 3, 4, 3};
    int k = 6;
    int output = 1;

    /*
        Starting with nums = [3,1,3,4,3]:
        - Remove the first two 3's, then nums = [1,4,3]
        There are no more pairs that sum up to 6, hence a total of 1 operation.
    */
    Solution sl;
    int ret = sl.MaxOperationsV2(nums, k);
    EXPECT_EQ(ret, output);
}

TEST(max_number_of_k_sum_pairs_v3, t2) {
    std::vector<int> nums = {3, 1, 3, 4, 3};
    int k = 6;
    int output = 1;

    /*
        Starting with nums = [3,1,3,4,3]:
        - Remove the first two 3's, then nums = [1,4,3]
        There are no more pairs that sum up to 6, hence a total of 1 operation.
    */
    Solution sl;
    int ret = sl.MaxOperationsV3(nums, k);
    EXPECT_EQ(ret, output);
}

}  // namespace
