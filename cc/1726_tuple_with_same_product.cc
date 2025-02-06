/*
 * Given an array nums of distinct positive integers, return the number of
 * tuples (a, b, c, d) such that a * b = c * d where a, b, c, and d are elements
 * of nums, and a != b != c != d.
 *
 */

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int tupleSameProduct(vector<int> &nums) {
        /*
         * 1 <= nums.length <= 1000
         * 1 <= nums[i] <= 104
         * All elements in nums are distinct
         */

        /*
         *Intuition
         The task is to find tuples (𝑎,𝑏,𝑐,𝑑) such that 𝑎×𝑏=𝑐×𝑑. Each such tuple
         can be counted by iterating through pairs of numbers and checking their
         products. If two pairs have the same product, we can form tuples with
         them.

         Approach
         Product Map:
         Use a hash map to store the product of each pair of numbers.
         The key is the product, and the value is the count of pairs that
         produce this product. Iterate Over Pairs: Iterate through all possible
         pairs (𝑖,𝑗) in the array and calculate their product. Update the hash
         map with the product. Count Tuples: For each unique product in the map,
         count the number of valid tuples. If a product has been seen 𝑛 times,
         the number of ways to choose 2 pairs from 𝑛 pairs is given by
         𝑛𝐶2=𝑛(𝑛−1)2. Each combination can form 8 tuples (𝑎,𝑏,𝑐,𝑑) by arranging
         the pairs.

         Complexity Time complexity: O(n^2) Space complexity: O(n^2)
        *
        */

        auto size = nums.size();
        unordered_map<int, int> map;
        int res = 0;

        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                map[nums[i] * nums[j]]++;
            }
        }

        for (auto &[_, times] : map) {
            if (times >= 2) {
                res += 8 * (times * (times - 1) / 2);
            }
        }

        return res;
    }
};

#include <gtest/gtest.h>

TEST(t0, t1) {
    std::vector<int> nums = {2, 3, 4, 6};
    int output = 8;
    Solution sl;
    auto ret = sl.tupleSameProduct(nums);
    EXPECT_EQ(ret, output);

    /*
     Explanation: There are 8 valid tuples:
     (2,6,3,4) , (2,6,4,3 , (6,2,3,4) , (6,2,4,3)
     (3,4,2,6) , (4,3,2,6) , (3,4,6,2) , (4,3,6,2)
     */
}

TEST(t0, t2) {
    std::vector<int> nums = {1, 2, 4, 5, 10};
    int output = 16;
    Solution sl;
    auto ret = sl.tupleSameProduct(nums);
    EXPECT_EQ(ret, output);
    /*
     Explanation: There are 16 valid tuples:
     (1,10,2,5) , (1,10,5,2) , (10,1,2,5) , (10,1,5,2)
     (2,5,1,10) , (2,5,10,1) , (5,2,1,10) , (5,2,10,1)
     (2,10,4,5) , (2,10,5,4) , (10,2,4,5) , (10,2,5,4)
     (4,5,2,10) , (4,5,10,2) , (5,4,2,10) , (5,4,10,2)
     */
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
