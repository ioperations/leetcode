// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java:
// https://pvs-studio.com
/*
Given an integer array nums and an integer val, remove all occurrences of val in
nums in-place. The relative order of the elements may be changed.

Since it is impossible to change the length of the array in some languages, you
must instead have the result be placed in the first part of the array nums. More
formally, if there are k elements after removing the duplicates, then the first
k elements of nums should hold the final result. It does not matter what you
leave beyond the first k elements.

Return k after placing the final result in the first k slots of nums.

Do not allocate extra space for another array. You must do this by modifying the
input array in-place with O(1) extra memory.

The judge will test your solution with the following code:

int[] nums = [...]; // Input array
int val = ...; // Value to remove
int[] expectedNums = [...]; // The expected answer with correct length.
                            // It is sorted with no values equaling val.

assert k == expectedNums.length;
sort(nums, 0, k); // Sort the first k elements of nums
for (int i = 0; i < actualLength; i++) {
    assert nums[i] == expectedNums[i];
}
If all assertions pass, then your solution will be accepted.
*/

#include <vector>

#include <catch2/catch_test_macros.hpp>

#define concat(a, b) a##b
#define symbol(a) #a
#define TEST(a, b) TEST_CASE(symbol(concat(a, b)), #b)
#define EXPECT_EQ(a, b) REQUIRE(a == b)
#define EXPECT_TRUE(a) REQUIRE(a)
#define EXPECT_FALSE(a) REQUIRE(!a)

using namespace std;

namespace {
class Solution {
   public:
    int RemoveElement(vector<int> &nums, int val) {
        // pass
        int n = nums.size();

        int i = 0, j = 0;

        while (j < n) {
            if (nums[j] != val) {
                nums[i++] = nums[j];
            }
            j++;
        }

        return i;
    }
};

TEST(remove_element, t1) {
    std::vector<int> v{3, 2, 2, 3};
    int val = 3;
    int output = 2;
    std::vector<int> nums_expected = {2, 2};
    // Explanation: Your function should return k = 2, with the first two
    // elements of nums being 2. It does not matter what you leave beyond the
    // returned k (hence they are underscores).
    Solution sl;
    int ret = sl.RemoveElement(v, val);
    EXPECT_EQ(ret, output);
    for (int i = 0; i < output; i++) {
        EXPECT_EQ(v[i], nums_expected[i]);
    }
}

TEST(remove_element, t2) {
    std::vector<int> v{0, 1, 2, 2, 3, 0, 4, 2};
    int val = 2;
    int output = 5;
    std::vector<int> nums_expected = {0, 1, 3, 0, 4};
    // Your function should return k = 5, with the first five elements of nums
    // containing 0, 0, 1, 3, and 4. Note that the five elements can be returned
    // in any order. It does not matter what you leave beyond the returned k
    // (hence they are underscores).   Solution sl;
    Solution sl;
    int ret = sl.RemoveElement(v, val);
    EXPECT_EQ(ret, output);
    for (int i = 0; i < output; i++) {
        EXPECT_EQ(v[i], nums_expected[i]);
    }
}

}  // namespace
