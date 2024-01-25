// Given an unsorted integer array nums, return the smallest missing positive
// integer. You must implement an algorithm that runs in O(n) time and uses
// constant extra space.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn first_missing_positive(nums: Vec<i32>) -> i32 {
        // swap method
        // postive -> arr[postive-1]

        let mut nums = nums;
        for i in 0..nums.len() {
            while (nums[i] > 0)
                && (nums[i] < nums.len() as i32)
                && (nums[i] != i as i32 + 1)
            {
                let j = nums[i] as usize - 1;
                if nums[j] == nums[i] {
                    break;
                }
                nums.swap(i, j);
            }
        }

        for (i, value) in nums.iter().enumerate() {
            if i as i32 + 1 != *value {
                return i as i32 + 1;
            }
        }

        nums.len() as i32 + 1
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![1, 2, 0];
        let ret = Solution::first_missing_positive(nums);
        // The numbers in the range [1,2] are all in the array.
        assert_eq!(3, ret);
    }

    #[test]
    fn case2_test() {
        let nums = vec![3, 4, -1, 1];
        let ret = Solution::first_missing_positive(nums);
        assert_eq!(2, ret);
        // 1 is in the array but 2 is missing.
    }

    #[test]
    fn case3_test() {
        let nums = vec![7, 8, 9, 11, 12];
        let ret = Solution::first_missing_positive(nums);
        assert_eq!(1, ret);
        // The smallest positive integer 1 is missing.
    }

    #[test]
    fn case4_test() {
        let nums = vec![1, 2, 3, 4, 5, 6, 7, 8, 9, 20];
        let ret = Solution::first_missing_positive(nums);
        assert_eq!(10, ret);
    }

    #[test]
    fn case5_test() {
        let nums = vec![1, 3, 3];
        let ret = Solution::first_missing_positive(nums);
        assert_eq!(2, ret);
    }
}
