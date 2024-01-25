// Given an integer array nums and an integer k, return the kth largest element
// in the array. Note that it is the kth largest element in the sorted order,
// not the kth distinct element. Can you solve it without sorting?

use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_kth_largest(nums: &[i32], k: i32) -> i32 {
        let mut binary_heap = BinaryHeap::new();

        for &i in nums {
            binary_heap.push(i);
        }

        for i in (0..k - 1) {
            binary_heap.pop();
        }

        match binary_heap.peek() {
            Some(i) => *i,
            None => todo!(),
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [3, 2, 1, 5, 6, 4];
        let k = 2;
        let output = 5;
        let ret = Solution::find_kth_largest(&nums, k);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let nums = [3, 2, 3, 1, 2, 4, 5, 5, 6];
        let k = 4;
        let output = 4;
        let ret = Solution::find_kth_largest(&nums, k);
        assert_eq!(output, ret);
    }
}
