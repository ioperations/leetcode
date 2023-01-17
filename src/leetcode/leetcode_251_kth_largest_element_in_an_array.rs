use std::cmp::Reverse;
use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn find_kth_largest(nums: Vec<i32>, k: i32) -> i32 {
        let mut nums_clone = nums;
        nums_clone.sort_by(|a, b| b.cmp(a));
        if k < nums_clone.len() as i32 {
            return nums_clone[(k - 1) as usize];
        }
        0
    }

    #[allow(unused)]
    pub fn find_kth_largest_min_heap(nums: Vec<i32>, k: i32) -> i32 {
        let k = k as usize;
        let mut minheap = BinaryHeap::with_capacity(k);

        nums.into_iter().for_each(|i| minheap.push(Reverse(i)));
        while minheap.len() > k {
            minheap.pop();
        }
        minheap.peek().unwrap().0
    }

    #[allow(unused)]
    pub fn find_kth_largest_max_heap(nums: Vec<i32>, k: i32) -> i32 {
        let mut k = k as usize;

        // v1: let mut maxheap = BinaryHeap::with_capacity(k);
        // nums.into_iter().for_each(|i| maxheap.push(i));

        let mut maxheap = BinaryHeap::from(nums);
        while k > 1 {
            maxheap.pop();
            k -= 1;
        }

        *maxheap.peek().unwrap()
    }

    #[allow(unused)]
    pub fn find_kth_largest_max_heap_alternative_version(
        nums: Vec<i32>,
        k: i32,
    ) -> i32 {
        let mut maxheap = BinaryHeap::from(nums);
        let mut max = maxheap.into_sorted_vec();
        max[max.len() - k as usize]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![3, 2, 1, 5, 6, 4];
        let k = 2;
        let ret = Solution::find_kth_largest(nums, k);
        assert_eq!(ret, 5);
    }

    #[test]
    fn case2_test() {
        let nums = vec![3, 2, 3, 1, 2, 4, 5, 5, 6];
        let k = 4;
        let ret = Solution::find_kth_largest(nums, k);
        assert_eq!(ret, 4);
    }

    #[test]
    fn min_heap_case1_test() {
        let nums = vec![3, 2, 1, 5, 6, 4];
        let k = 2;
        let ret = Solution::find_kth_largest_min_heap(nums, k);
        assert_eq!(ret, 5);
    }

    #[test]
    fn min_heap_case2_test() {
        let nums = vec![3, 2, 3, 1, 2, 4, 5, 5, 6];
        let k = 4;
        let ret = Solution::find_kth_largest_min_heap(nums, k);
        assert_eq!(ret, 4);
    }

    #[test]
    fn max_heap_case1_test() {
        let nums = vec![3, 2, 1, 5, 6, 4];
        let k = 2;
        let ret = Solution::find_kth_largest_max_heap(nums, k);
        assert_eq!(ret, 5);
    }

    #[test]
    fn max_heap_case2_test() {
        let nums = vec![3, 2, 3, 1, 2, 4, 5, 5, 6];
        let k = 4;
        let ret = Solution::find_kth_largest_max_heap(nums, k);
        assert_eq!(ret, 4);
    }

    #[test]
    fn max_heap_altertive_case1_test() {
        let nums = vec![3, 2, 1, 5, 6, 4];
        let k = 2;
        let ret =
            Solution::find_kth_largest_max_heap_alternative_version(nums, k);
        assert_eq!(ret, 5);
    }

    #[test]
    fn max_heap_altertive_case2_test() {
        let nums = vec![3, 2, 3, 1, 2, 4, 5, 5, 6];
        let k = 4;
        let ret =
            Solution::find_kth_largest_max_heap_alternative_version(nums, k);
        assert_eq!(ret, 4);
    }
}
