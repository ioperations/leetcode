// Given two strings text1 and text2, return the length of their longest common subsequence.
// If there is no common subsequence, return 0.
// A subsequence of a string is a new string generated from the original string
// with some characters (can be none) deleted without changing the relative order of the remaining characters.
// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn longest_common_subsequence(text1: &str, text2: &str) -> i32 {
        let n = text1.len();
        let m = text2.len();
        let mut table = vec![vec![0; m + 1]; n + 1];
        for (i, ch1) in text1.chars().enumerate() {
            for (j, ch2) in text2.chars().enumerate() {
                if ch1 == ch2 {
                    table[i + 1][j + 1] = table[i][j] + 1;
                } else {
                    table[i + 1][j + 1] = table[i][j + 1].max(table[i + 1][j]);
                }
            }
        }
        table[n][m]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let text1 = "abcde";
        let text2 = "ace";
        let output = 3;
        // Explanation: The longest common subsequence is "ace" and its length is 3.
        let ret = Solution::longest_common_subsequence(text1, text2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let text1 = "abc";
        let text2 = "abc";
        let output = 3;
        // The longest common subsequence is "abc" and its length is 3.
        let ret = Solution::longest_common_subsequence(text1, text2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let text1 = "abc";
        let text2 = "def";
        let output = 0;
        // There is no such common subsequence, so the result is 0.
        let ret = Solution::longest_common_subsequence(text1, text2);
        assert_eq!(ret, output);
    }
}
