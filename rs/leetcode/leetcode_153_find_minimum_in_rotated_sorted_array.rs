// Suppose an array of length n sorted in ascending order is rotated between 1
// and n times. For example, the array nums = [0,1,2,4,5,6,7] might become:
//
// [4,5,6,7,0,1,2] if it was rotated 4 times.
// [0,1,2,4,5,6,7] if it was rotated 7 times.
// Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results
// in the array [a[n-1], a[0], a[1], a[2], ..., a[n-2]].
// Given the sorted rotated array nums of unique elements,
// return the minimum element of this array.
// You must write an algorithm that runs in O(log n) time.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_min(nums: &[i32]) -> i32 {
        let mut l: usize = 1;
        let mut h: usize = nums.len();
        let n = nums.len();
        while (l < h) {
            let i = usize::midpoint(l, h);
            if (nums[i] > nums[0]) {
                l = i + 1;
            } else {
                h = i;
            }
        }
        nums[l % n]
    }

    #[allow(unused)]
    pub fn find_min_o_n_(nums: Vec<i32>) -> i32 {
        let mut nums = nums;
        nums.sort_unstable();
        nums[0]
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = vec![3, 4, 5, 1, 2];
        let output = 1;
        // Explanation: The original array was [1,2,3,4,5] rotated 3 times.
        let ret = Solution::find_min(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = vec![4, 5, 6, 7, 0, 1, 2];
        let output = 0;
        // Explanation: The original array was [0,1,2,4,5,6,7] and it was
        // rotated 4 times.
        let ret = Solution::find_min(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = vec![11, 13, 15, 17];
        let output = 11;
        // Explanation: The original array was [11,13,15,17] and it was rotated
        // 4 times.
        let ret = Solution::find_min(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let nums = vec![4, 5, 6, 7, 2];
        let output = 2;
        // Explanation: The original array was [2,4,5,6,7] and it was rotated 4
        // times.
        let ret = Solution::find_min(&nums);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_o_log_n(b: &mut test::Bencher) {
        b.iter(|| {
            let nums: Vec<_> = (8..=999).collect();
            let val = Solution::find_min(&nums);
            assert_eq!(val, 8);
        });
    }
}

#[cfg(test)]
mod testsv2 {
    use super::Solution;
    extern crate test;

    #[test]
    fn case1_test() {
        let nums = vec![3, 4, 5, 1, 2];
        let output = 1;
        // Explanation: The original array was [1,2,3,4,5] rotated 3 times.
        let ret = Solution::find_min_o_n_(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = vec![4, 5, 6, 7, 0, 1, 2];
        let output = 0;
        // Explanation: The original array was [0,1,2,4,5,6,7] and it was
        // rotated 4 times.
        let ret = Solution::find_min_o_n_(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = vec![11, 13, 15, 17];
        let output = 11;
        // Explanation: The original array was [11,13,15,17] and it was rotated
        // 4 times.
        let ret = Solution::find_min_o_n_(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let nums = vec![4, 5, 6, 7, 2];
        let output = 2;
        // Explanation: The original array was [2,4,5,6,7] and it was rotated 4
        // times.
        let ret = Solution::find_min_o_n_(nums);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_o_n(b: &mut test::Bencher) {
        b.iter(|| {
            let nums = (8..=999).collect();
            let val = Solution::find_min_o_n_(nums);
            assert_eq!(val, 8);
        });
    }
}
