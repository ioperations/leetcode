// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com

/*

Given an integer array nums, return the number of reverse pairs in the array.

A reverse pair is a pair (i, j) where 0 <= i < j < nums.length and nums[i] > 2 *
nums[j].

*/

#include <vector>

#include <catch2/catch_test_macros.hpp>

#define TEST(a, b) TEST_CASE(#a,#b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int ReversePairs(vector<int> &nums) {
        // pass

        int count = 0;
        for (int i = 0; i < (int)nums.size(); i++) {
            for (int j = i + 1; j < (int)nums.size(); j++) {
                if (nums[i] / 2 > nums[j]) {
                    count++;
                }
                if (nums[i] / 2 == nums[j] && nums[i] % 2 == 1) {
                    count++;
                }
            }
        }
        return count;
    }
};

class SolutionV2 {
   public:
    int ReversePairs(vector<int> &nums) {
        vector<int> temp(nums.size());
        return Merge(nums, 0, nums.size(), temp);
    }
    int BinaryCnt(vector<int> &nums, int left, int right, double n,
                  bool direction) {
        int size = right - left;
        int ori_left = left;
        right--;
        int mid;
        while (left <= right) {
            mid = left + (right - left) / 2;
            if (direction) {
                if (nums[mid] > n)
                    right = mid - 1;
                else
                    left = mid + 1;
            } else {
                if (nums[mid] >= n)
                    right = mid - 1;
                else
                    left = mid + 1;
            }
        }

        if (direction) return size - (left - ori_left);
        return (left - ori_left);
    };

    int Merge(vector<int> &nums, int left, int right, vector<int> &temp) {
        long cnt = 0;
        if (right - left < 2) {
            return cnt;
        }
        int mid = left + (right - left) / 2;
        cnt += Merge(nums, left, mid, temp);
        cnt += Merge(nums, mid, right, temp);

        for (int i = left; i < right; ++i) {
            temp[i] = nums[i];
        }
        int left_p = left;
        int right_p = mid;
        int idx = left;
        while (left_p < mid && right_p < right) {
            if (temp[left_p] < temp[right_p]) {
                cnt += BinaryCnt(temp, right_p, right,
                                 (double)(temp[left_p]) / 2, false);
                nums[idx++] = temp[left_p++];
            } else {
                cnt += BinaryCnt(temp, left_p, mid, (double)(temp[right_p]) * 2,
                                 true);
                nums[idx++] = temp[right_p++];
            }
        }
        while (left_p < mid) {
            nums[idx++] = temp[left_p++];
        }
        return cnt;
    };
};

TEST(reverse_pairs, t1) {
    std::vector<int> nums = {1, 3, 2, 3, 1};
    int expected = 2;

    Solution sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}

TEST(reverse_pairs_v2, t1) {
    std::vector<int> nums = {1, 3, 2, 3, 1};
    int expected = 2;

    SolutionV2 sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}

TEST(reverse_pairs, t2) {
    std::vector<int> nums = {2, 4, 3, 5, 1};
    int expected = 3;

    Solution sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}

TEST(reverse_pairs_v2, t2) {
    std::vector<int> nums = {2, 4, 3, 5, 1};
    int expected = 3;

    SolutionV2 sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}

TEST(reverse_pairs, t3) {
    std::vector<int> nums = {2147483647, 2147483647, 2147483647,
                             2147483647, 2147483647, 2147483647};
    int expected = 0;

    Solution sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}
TEST(reverse_pairs_v2, t3) {
    std::vector<int> nums = {2147483647, 2147483647, 2147483647,
                             2147483647, 2147483647, 2147483647};
    int expected = 0;

    SolutionV2 sl;
    int ret = sl.ReversePairs(nums);
    EXPECT_EQ(ret, expected);
}

}  // namespace
