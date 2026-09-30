// You are given an integer array nums.
//
// Return the length of the longest subsequence in nums whose bitwise XOR is
// non-zero. If no such subsequence exists, return 0.
//
// 1 <= nums.length <= 105
// 0 <= nums[i] <= 109

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn longest_subsequence(numbers: &[i32]) -> i32 {
        // XOR of every element equals XOR of any subsequence that keeps all of
        // them, so if the total XOR is non-zero the whole array already works.
        let total_xor = numbers.iter().fold(0i32, |acc, &x| acc ^ x);
        let cnt = numbers.len() as i32;

        if total_xor != 0 {
            return cnt;
        }

        // Dropping exactly one element flips its bits, which turns a zero XOR
        // into that element's value. So dropping any non-zero element works.
        if numbers.iter().any(|&x| x != 0) {
            return cnt - 1;
        }

        // Every element is zero, so no non-empty subsequence can have a
        // non-zero XOR.
        0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let numbers = [1, 2, 3];
        let output = 2;
        let ret = Solution::longest_subsequence(&numbers);
        assert_eq!(output, ret);
        // One longest subsequence is [2, 3]. The bitwise XOR is computed as 2
        // XOR 3 = 1, which is non-zero.
    }

    #[test]
    fn case2_test() {
        let numbers = [2, 3, 4];
        let output = 3;
        let ret = Solution::longest_subsequence(&numbers);
        assert_eq!(output, ret);
        // The longest subsequence is [2, 3, 4]. The bitwise XOR is computed as
        // 2 XOR 3 XOR 4 = 5, which is non-zero.
    }
}
