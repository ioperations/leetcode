// Given an array of integers nums, sort the array in ascending order and return
// it. You must solve the problem without using any built-in functions in
// O(nlog(n)) time complexity and with the smallest space complexity possible.
#![allow(unused)]
struct Solution;
use std::cmp::Reverse;
use std::collections::BinaryHeap;

impl Solution {
    #[allow(unused)]
    pub fn sort_array(nums: &[i32]) -> Vec<i32> {
        fn merge(nums: &[i32], nums2: &[i32]) -> Vec<i32> {
            let mut bh = BinaryHeap::new();
            for &ele in nums.iter().chain(nums2.iter()) {
                bh.push(ele);
            }

            let mut ret = Vec::with_capacity(nums.len() + nums2.len());
            while !bh.is_empty() {
                ret.push(bh.pop().unwrap());
            }
            ret.into_iter().rev().collect()
        };

        fn myimpl(nums: &[i32]) -> Vec<i32> {
            if nums.len() == 1 {
                return vec![nums[0]];
            }
            let half = nums.len() / 2;
            let left = myimpl(&nums[0..half]);
            let right = myimpl(&nums[half..]);
            merge(&left, &right)
        };

        myimpl(nums)
    }

    #[allow(unused)]
    pub fn sort_array_v2(nums: &[i32]) -> Vec<i32> {
        fn merge(nums: &[i32], nums2: &[i32]) -> Vec<i32> {
            let mut bh = BinaryHeap::new();
            for &ele in nums.iter().chain(nums2.iter()) {
                bh.push(Reverse(ele));
            }

            let mut ret = Vec::with_capacity(nums.len() + nums2.len());
            while let Some(Reverse(v)) = bh.pop() {
                ret.push(v);
            }
            ret
        };

        fn myimpl(nums: &[i32]) -> Vec<i32> {
            if nums.len() == 1 {
                return vec![nums[0]];
            }
            let half = nums.len() / 2;
            let left = myimpl(&nums[0..half]);
            let right = myimpl(&nums[half..]);
            merge(&left, &right)
        };

        myimpl(nums)
    }
}

#[cfg(test)]
mod test {

    use super::*;

    extern crate test;
    #[test]
    fn case1_test() {
        let nums = [5, 2, 3, 1];
        let output = [1, 2, 3, 5];
        // Explanation: After sorting the array, the positions of some numbers
        // are not changed (for example, 2 and 3), while the positions of other
        // numbers are changed (for example, 1 and 5).
        let ret = Solution::sort_array(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [5, 1, 1, 2, 0, 0];
        let output = [0, 0, 1, 1, 2, 5];
        // Note that the values of nums are not necessairly unique.
        let ret = Solution::sort_array(&nums);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        b.iter(|| {
            let nums = [5, 1, 1, 2, 0, 0, 8, 7, 6, 5, 4, 3, 2, 1];
            let output = [0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 8];
            // Note that the values of nums are not necessairly unique.
            let ret = Solution::sort_array(&nums);
            assert_eq!(ret, output);
        });
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        b.iter(|| {
            let nums = [5, 1, 1, 2, 0, 0, 8, 7, 6, 5, 4, 3, 2, 1];
            let output = [0, 0, 1, 1, 1, 2, 2, 3, 4, 5, 5, 6, 7, 8];
            // Note that the values of nums are not necessairly unique.
            let ret = Solution::sort_array_v2(&nums);
            assert_eq!(ret, output);
        });
    }
}
