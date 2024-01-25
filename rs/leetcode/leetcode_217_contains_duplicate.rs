// Given an integer array nums, return true if any value appears at least twice
// in the array, and return false if every element is distinct.

use std::collections::HashSet;
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn contains_duplicate(nums: &[i32]) -> bool {
        let mut hash_set = HashSet::with_capacity(nums.len());

        for i in nums {
            if hash_set.contains(&i) {
                return true;
            }
            hash_set.insert(i);
        }
        false
    }

    #[allow(unused)]
    pub fn contains_duplicate_v2(nums: &[i32]) -> bool {
        let mut set = HashSet::with_capacity(nums.len());

        nums.iter().any(|&num| !set.insert(num))
    }

    #[allow(unused)]
    pub fn contains_duplicate_v3(mut nums: Vec<i32>) -> bool {
        nums.sort_unstable();
        nums.iter().zip(nums.iter().skip(1)).any(|(&a, &b)| a == b)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 1];
        let ret = Solution::contains_duplicate(&nums);
        let output = true;
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 2, 3, 4];
        let ret = Solution::contains_duplicate(&nums);
        let output = false;
        assert_eq!(ret, output);
    }
    #[test]
    fn case3_test() {
        let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
        let ret = Solution::contains_duplicate(&nums);
        let output = true;
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let output = true;
        b.iter(|| {
            let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
            let ret = Solution::contains_duplicate(&nums);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 1];
        let ret = Solution::contains_duplicate_v2(&nums);
        let output = true;
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 2, 3, 4];
        let ret = Solution::contains_duplicate_v2(&nums);
        let output = false;
        assert_eq!(ret, output);
    }
    #[test]
    fn case3_test() {
        let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
        let ret = Solution::contains_duplicate_v2(&nums);
        let output = true;
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        let output = true;
        b.iter(|| {
            let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
            let ret = Solution::contains_duplicate_v2(&nums);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v3 {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 1];
        let ret = Solution::contains_duplicate_v3(nums.into());
        let output = true;
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 2, 3, 4];
        let ret = Solution::contains_duplicate_v3(nums.into());
        let output = false;
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2];
        let ret = Solution::contains_duplicate_v3(nums.into());
        let output = true;
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_sort(b: &mut test::Bencher) {
        let output = true;
        b.iter(|| {
            let nums = [1, 1, 1, 3, 3, 4, 3, 2, 4, 2].into();
            let ret = Solution::contains_duplicate_v3(nums);
            assert_eq!(ret, output);
        });
    }
}
