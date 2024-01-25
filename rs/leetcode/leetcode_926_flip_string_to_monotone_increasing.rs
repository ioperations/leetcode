// A binary string is monotone increasing if it consists of some number of 0's
// (possibly none), followed by some number of 1's (also possibly none). You are
// given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1
// to 0. Return the minimum number of flips to make s monotone increasing.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_flips_mono_incr(s: &str) -> i32 {
        let n = s.len();
        let mut f = vec![vec![0; 2]; n + 1];
        let chars: Vec<char> = s.chars().collect();

        for i in 1..=n {
            f[i][0] = f[i - 1][0] + i32::from(chars[i - 1] == '1');
            f[i][1] = std::cmp::min(f[i - 1][0], f[i - 1][1])
                + i32::from(chars[i - 1] == '0');
        }

        std::cmp::min(f[n][0], f[n][1])
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "00110";
        let output = 1;
        // Explanation: We flip the last digit to get 00111.
        let ret = Solution::min_flips_mono_incr(s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let s = "010110";
        let output = 2;
        // Explanation: We flip to get 011111, or alternatively 000111.
        let ret = Solution::min_flips_mono_incr(s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let s = "00011000";
        let output = 2;
        // Explanation: We flip to get 00000000.
        let ret = Solution::min_flips_mono_incr(s);
        assert_eq!(ret, output);
    }
}
