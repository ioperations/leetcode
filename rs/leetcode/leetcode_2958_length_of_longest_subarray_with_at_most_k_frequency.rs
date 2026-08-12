//*
// * You are given an integer array nums and an integer k.
// *
// * The frequency of an element x is the number of times it occurs in an array.
// *
// * An array is called good if the frequency of each element in this array is
// * less than or equal to k.
// *
// * Return the length of the longest good subarray of nums.
// *
// * A subarray is a contiguous non-empty sequence of elements within an array.
// *
// * 1 <= nums.length <= 105
// * 1 <= nums[i] <= 109
// * 1 <= k <= nums.length

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn max_subarray_length(nums: &[i32], k: u32) -> i32 {
        let mut cnt = 0;

        let size = nums.len();

        let mut start = 0;
        let mut end = 0;

        let mut fre: HashMap<i32, u32> = HashMap::new();
        while end < size {
            let x = nums[end];

            fre.entry(x)
                .and_modify(|x| {
                    *x += 1;
                })
                .or_insert(1);

            let entry = fre.get(&x);

            while *(fre.get(&x).unwrap()) == k + 1 {
                fre.entry(nums[start]).and_modify(|x| {
                    *x -= 1;
                });
                start += 1;
            }

            cnt = cnt.max(end - start + 1);
            end += 1;
        }

        cnt as i32
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 1, 2, 3, 1, 2];
        let k = 2;
        let output = 6;
        let ret = Solution::max_subarray_length(&nums, k);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 2, 1, 2, 1, 2, 1, 2];
        let k = 1;
        let output = 2;
        let ret = Solution::max_subarray_length(&nums, k);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let nums = [5, 5, 5, 5, 5, 5, 5];
        let k = 4;
        let output = 4;
        let ret = Solution::max_subarray_length(&nums, k);
        assert_eq!(output, ret);
    }
}
