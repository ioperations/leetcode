/*Given a binary array nums, you should delete one element from it.

Return the size of the longest non-empty subarray containing only 1's in the
resulting array. Return 0 if there is no such subarray.*/

#include <map>
#include <vector>
using namespace std;

class Solution {
   public:
    int LongestSubarray(vector<int>& nums) {
        map<int /*index*/, int>
            z;  // 代表删除第index处的0之后，后面能拼接起来的1的长度
        vector<int> arr;  // 代表数字为0的点的index
                          // 特别的，相邻为0的点只会记录第一次出现0的地方

        int num1_size = 0;
        int num0_index = 0;
        int last0_index = 0;
        int size = nums.size();

        for (int i = 0; i < size; i++) {
            if (nums[i]) {
                // ptr == 1
                num1_size++;

            } else {
                //  ptr == 0
                num0_index = i;
            }
        }
        return 0;
    }
};

#include <gtest/gtest.h>

#include <iostream>

TEST(t0, t1) {
    vector<int> nums = {1, 1, 0, 1};
    int output = 3;
    Solution sl;
    int ret = sl.LongestSubarray(nums);
    EXPECT_EQ(ret, output);
    // Explanation: After deleting the number in position 2, [1,1,1] contains 3
    // numbers with value of 1's.
}

TEST(t0, t2) {
    vector<int> nums = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    int output = 5;
    Solution sl;
    int ret = sl.LongestSubarray(nums);
    // After deleting the number in position 4, [0,1,1,1,1,1,0,1] longest
    // subarray with value of 1's is [1,1,1,1,1].
    EXPECT_EQ(ret, output);
}

TEST(t0, t3) {
    vector<int> nums = {1, 1, 1};
    int output = 2;
    Solution sl;
    int ret = sl.LongestSubarray(nums);
    // You must delete one element.
    EXPECT_EQ(ret, output);
}
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

