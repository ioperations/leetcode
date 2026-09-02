// You are given an array nums1 of n distinct integers.
//
// You want to construct another array nums2 of length n such that the elements
// in nums2 are either all odd or all even.
//
// For each index i, you must choose exactly one of the following (in any
// order):
//
// nums2[i] = nums1[i]
// nums2[i] = nums1[i] - nums1[j], for an index j != i
// Return true if it is possible to construct such an array, otherwise, return
// false.

// 1 <= n == nums1.length <= 100
// 1 <= nums1[i] <= 100
// nums1 consists of distinct integers.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn uniform_array(nums1: &[i32]) -> bool {
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![2, 3];
        let output = true;
        let ret = Solution::uniform_array(&nums);
        assert_eq!(output, ret);
        // Choose nums2[0] = nums1[0] - nums1[1] = 2 - 3 = -1.
        // Choose nums2[1] = nums1[1] = 3.
        // nums2 = [-1, 3], and both elements are odd. Thus, the answer is true
    }

    #[test]
    fn case2_test() {
        let nums = vec![4, 6];
        let output = true;
        let ret = Solution::uniform_array(&nums);
        assert_eq!(output, ret);
        // Choose nums2[0] = nums1[0] = 4.
        // Choose nums2[1] = nums1[1] = 6.
        // nums2 = [4, 6], and all elements are even. Thus, the answer is true.
    }
}
