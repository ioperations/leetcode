// You are given a 0-indexed integer array nums.
//
// The distinct count of a subarray of nums is defined as:
//
// Let nums[i..j] be a subarray of nums consisting of all the indices from i to
// j such that 0 <= i <= j < nums.length. Then the number of distinct values in
// nums[i..j] is called the distinct count of nums[i..j]. Return the sum of the
// squares of distinct counts of all subarrays of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
// 1 <= nums.length <= 100
// 1 <= nums[i] <= 100

use std::collections::HashSet;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn sum_counts(nums: &[i32]) -> i32 {
        let n = nums.len();
        let mut res = 0;
        for i in 0..n {
            let mut s = HashSet::new();
            for j in i..n {
                s.insert(nums[j]);
                res += (s.len() * s.len()) as i32;
            }
        }
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 1].to_vec();

        let output = 15;
        let ret = Solution::sum_counts(&nums);
        assert_eq!(output, ret);
        // Six possible subarrays are:
        // [1]: 1 distinct value
        // [2]: 1 distinct value
        // [1]: 1 distinct value
        // [1,2]: 2 distinct values
        // [2,1]: 2 distinct values
        // [1,2,1]: 2 distinct values
        // The sum of the squares of the distinct counts in all subarrays is
        // equal to 12 + 12 + 12 + 22 + 22 + 22 = 15.
    }

    #[test]
    fn case2_test() {
        let nums = [1, 1].to_vec();

        let output = 3;
        let ret = Solution::sum_counts(&nums);
        assert_eq!(output, ret);
        // Three possible subarrays are:
        // [1]: 1 distinct value
        // [1]: 1 distinct value
        // [1,1]: 1 distinct value
        // The sum of the squares of the distinct counts in all subarrays is
        // equal to 12 + 12 + 12 = 3.
    }
}
