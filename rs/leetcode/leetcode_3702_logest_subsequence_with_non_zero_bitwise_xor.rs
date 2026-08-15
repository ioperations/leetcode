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
    pub fn longest_subsequence(numbers: Vec<i32>) -> i32 {
        // 展开为2进制，每一竖排1的个数为奇数 直接返回当前的长度
        let cnt = numbers.len();

        let mut v: Vec<Vec<i32>> = Vec::with_capacity(cnt);
        let mut p = vec![];
        p.resize(32, 0);

        v.resize(cnt, p);
        for (idx, mut value) in numbers.into_iter().enumerate() {
            for i in 0..32 {
                v[idx][32 - 1 - i] = if value % 2 == 0 { 0 } else { 1 };

                value /= 2;
            }
        }

        let mut q = false;
        for i in 0..32 {
            let mut size = 0;
            for j in 0..cnt {
                size += if v[j][i] == 1 { 1 } else { 0 };
            }

            if (size % 2 == 1) {
                return cnt as i32;
            } else if (size != 0) {
                q = true;
            }
        }

        if (q) {
            return (cnt as i32) - 1;
        }

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
        let ret = Solution::longest_subsequence(numbers.into());
        assert_eq!(output, ret);
        // One longest subsequence is [2, 3]. The bitwise XOR is computed as 2
        // XOR 3 = 1, which is non-zero.
    }

    #[test]
    fn case2_test() {
        let numbers = [2, 3, 4];
        let output = 3;
        let ret = Solution::longest_subsequence(numbers.into());
        assert_eq!(output, ret);
        // The longest subsequence is [2, 3, 4]. The bitwise XOR is computed as
        // 2 XOR 3 XOR 4 = 5, which is non-zero.
    }
}
