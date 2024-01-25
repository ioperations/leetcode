// Given an integer array nums, return the number of subarrays filled with 0.
//
// A subarray is a contiguous non-empty sequence of elements within an array.

#![allow(unused)]

use std::collections::HashMap;
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn zero_filled_subarray(nums: &[i32]) -> i64 {
        fn cal(n: i32, cache: &mut HashMap<i32, i64>) -> i64 {
            if let Some(&v) = cache.get(&n) {
                return v;
            }
            match n {
                0 => 0,
                1 => 1,
                val => {
                    let ret = val as i64 + cal(val - 1, cache);
                    cache.insert(val, ret);
                    ret
                }
            }
        }
        fn my_impl(nums: &[i32]) -> i64 {
            let mut hash = HashMap::new();
            let (x, val) = nums
                .iter()
                .scan((0, 0), |(x, ret), &val| {
                    if val == 0 {
                        *x += 1;
                    } else {
                        *ret += cal(*x, &mut hash);
                        *x = 0;
                    }
                    Some((*x, *ret))
                })
                .last()
                .unwrap();
            val + cal(x, &mut hash)
        }
        my_impl(nums)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 3, 0, 0, 2, 0, 0, 4];
        let output = 6;
        // Explanation:
        // There are 4 occurrences of [0] as a subarray.
        // There are 2 occurrences of [0,0] as a subarray.
        // There is no occurrence of a subarray with a size more than 2 filled
        // with 0. Therefore, we return 6.
        let ret = Solution::zero_filled_subarray(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [0, 0, 0, 2, 0, 0];
        let output = 9;
        // Explanation:
        // There are 5 occurrences of [0] as a subarray.
        // There are 3 occurrences of [0,0] as a subarray.
        // There is 1 occurrence of [0,0,0] as a subarray.
        // There is no occurrence of a subarray with a size more than 3 filled
        // with 0. Therefore, we return 9.
        //
        let ret = Solution::zero_filled_subarray(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [2, 10, 2019];
        let output = 0;
        // Explanation:
        // There is no subarray filled with 0. Therefore, we return 0.
        let ret = Solution::zero_filled_subarray(&nums);
        assert_eq!(ret, output);
    }
}
