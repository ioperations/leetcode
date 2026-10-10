// You are given two positive 0-indexed integer arrays nums1 and nums2, both of
// length n.
//
// The sum of squared difference of arrays nums1 and nums2 is defined as the sum
// of (nums1[i] - nums2[i])2 for each 0 <= i < n.
//
// You are also given two positive integers k1 and k2. You can modify any of the
// elements of nums1 by +1 or -1 at most k1 times. Similarly, you can modify any
// of the elements of nums2 by +1 or -1 at most k2 times.
//
// Return the minimum sum of squared difference after modifying array nums1 at
// most k1 times and modifying array nums2 at most k2 times.
//
// Note: You are allowed to modify the array elements to become negative
// integers.
//

use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_sum_square_diff(
        nums1: &[i32],
        nums2: &[i32],
        k1: i32,
        k2: i32,
    ) -> i64 {
        // n == nums1.length == nums2.length
        // 1 <= n <= 105
        // 0 <= nums1[i], nums2[i] <= 105
        // 0 <= k1, k2 <= 109

        let mut al = nums1
            .iter()
            .zip(nums2.iter())
            .map(|(v, f)| (v - f).abs())
            .collect::<BinaryHeap<i32>>();

        let mut p = k1 + k2;
        while p > 0 {
            if let Some(v) = al.pop()
                && v > 0
            {
                al.push(v - 1);
            }
            p -= 1;
        }

        al.iter().map(|&v| (v as i64) * (v as i64)).sum::<i64>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums1 = [1, 2, 3, 4].to_vec();
        let nums2 = [2, 10, 20, 19].to_vec();
        let k1 = 0;
        let k2 = 0;
        let ret = Solution::min_sum_square_diff(&nums1, &nums2, k1, k2);
        let output = 579;
        assert_eq!(output, ret);
        // The elements in nums1 and nums2 cannot be modified because k1 = 0 and
        // k2 = 0. The sum of square difference will be: (1 - 2)2 + (2 -
        // 10)2 + (3 - 20)2 + (4 - 19)2 = 579.
    }

    #[test]
    fn case2_test() {
        let nums1 = [1, 4, 10, 12].to_vec();
        let nums2 = [5, 8, 6, 9].to_vec();
        let k1 = 1;
        let k2 = 1;
        let ret = Solution::min_sum_square_diff(&nums1, &nums2, k1, k2);
        let output = 43;
        assert_eq!(output, ret);
        // One way to obtain the minimum sum of square difference is:
        // - Increase nums1[0] once.
        // - Increase nums2[2] once.
        // The minimum of the sum of square difference will be:
        // (2 - 5)2 + (4 - 8)2 + (10 - 7)2 + (12 - 9)2 = 43.
        // Note that, there are other ways to obtain the minimum of the sum of
        // square difference, but there is no way to obtain a sum smaller than
        // 43.
    }

    #[test]
    fn case3_test() {
        let nums1 = [10, 10, 10, 11, 5].to_vec();
        let nums2 = [1, 0, 6, 6, 1].to_vec();
        let k1 = 11;
        let k2 = 27;
        let ret = Solution::min_sum_square_diff(&nums1, &nums2, k1, k2);
        let output = 0;
        assert_eq!(output, ret);
        // One way to obtain the minimum sum of square difference is:
        // - Increase nums1[0] once.
        // - Increase nums2[2] once.
        // The minimum of the sum of square difference will be:
        // (2 - 5)2 + (4 - 8)2 + (10 - 7)2 + (12 - 9)2 = 43.
        // Note that, there are other ways to obtain the minimum of the sum of
        // square difference, but there is no way to obtain a sum smaller than
        // 43.
    }
}
