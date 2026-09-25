// You are given an integer array nums.
//
// Return the smallest index i such that the sum of the digits of nums[i] is
// equal to i.
//
// If no such index exists, return -1.
//
// 1 <= nums.length <= 100
// 0 <= nums[i] <= 1000
#[allow(unused)]
struct Solution;

impl Solution {
    fn sum(mut num: i32) -> usize {
        let mut ret = 0;
        while num > 0 {
            ret += num as usize % 10;
            num /= 10;
        }
        ret
    }

    #[allow(unused)]
    pub fn smallest_index(nums: &[i32]) -> i32 {
        for (index, &v) in nums.iter().enumerate() {
            if Solution::sum(v) == index {
                return index as i32;
            }
        }
        -1
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![1, 3, 2];
        let output = 2;
        let ret = Solution::smallest_index(&nums);
        assert_eq!(output, ret);
        // For nums[2] = 2, the sum of digits is 2, which is equal to index i =
        // 2. Thus, the output is 2.
    }

    #[test]
    fn case2_test() {
        let nums = vec![1, 10, 11];
        let output = 1;
        let ret = Solution::smallest_index(&nums);
        assert_eq!(output, ret);
        // For nums[1] = 10, the sum of digits is 1 + 0 = 1, which is equal to
        // index i = 1. For nums[2] = 11, the sum of digits is 1 + 1 =
        // 2, which is equal to index i = 2. Since index 1 is the
        // smallest, the output is 1.
    }

    #[test]
    fn case3_test() {
        let nums = vec![1, 2, 3];
        let output = -1;
        let ret = Solution::smallest_index(&nums);
        assert_eq!(output, ret);
        // Since no index satisfies the condition, the output is -1.
    }
}
