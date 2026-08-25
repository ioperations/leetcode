// Given an integer array nums and an integer k, return the smallest positive
// multiple of k that is missing from nums.
//
// A multiple of k is any positive integer divisible by k.
//
// 1 <= nums.length <= 100
// 1 <= nums[i] <= 100
// 1 <= k <= 100

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn missing_multiple(nums: Vec<i32>, k: i32) -> i32 {
        let mut hm = HashMap::new();
        for &v in nums.iter() {
            hm.entry(v)
                .and_modify(|v| {
                    *v += 1;
                })
                .or_insert(1);
        }

        for i in 1.. {
            let v = i * k;
            if hm.get(&v).is_none() {
                return v;
            }
        }

        0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [8, 2, 3, 4, 6];
        let k = 2;
        let output = 10;
        let ret = Solution::missing_multiple(nums.into(), k);
        assert_eq!(output, ret);
        // The multiples of k = 2 are 2, 4, 6, 8, 10, 12... and the smallest
        // multiple missing from nums is 10.
    }

    #[test]
    fn case2_test() {
        let nums = [1, 4, 7, 10, 15];
        let k = 5;
        let output = 5;
        let ret = Solution::missing_multiple(nums.into(), k);
        assert_eq!(output, ret);
        // The multiples of k = 5 are 5, 10, 15, 20... and the smallest multiple
        // missing from nums is 5.
    }
}
