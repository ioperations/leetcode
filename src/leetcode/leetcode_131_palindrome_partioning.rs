// Given a string s, partition s such that every
// substring of the partition is a palindrome
// Return all possible palindrome partitioning of s.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn partition(s: &str) -> Vec<Vec<String>> {
        // 1 <= s.length <= 16
        // s contains only lowercase English letters.
        let mut ret = vec![];
        let mut t = vec![];
        let s: Vec<char> = s.chars().collect();

        Self::backtrack(0, &mut ret, &mut t, &s);
        ret
    }

    #[allow(unused)]
    fn backtrack(
        i: usize,
        ret: &mut Vec<Vec<String>>,
        t: &mut Vec<usize>,
        s: &[char],
    ) {
        if i == s.len() {
            let mut tt = Vec::with_capacity(t.len());
            for i in 1..t.len() {
                tt.push(s[t[i - 1]..t[i]].iter().collect());
            }
            tt.push(s[t[t.len() - 1]..].iter().collect());
            ret.push(tt);
            return;
        }

        t.push(i);
        for j in i..s.len() {
            if Self::is_palindrome(&s[i..=j]) {
                Self::backtrack(j + 1, ret, t, s);
            }
        }
        t.pop();
    }

    #[allow(unused)]
    fn is_palindrome(s: &[char]) -> bool {
        let len = s.len();
        !s.iter().zip(s.iter().rev()).take(len).any(|(i, j)| i != j)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "aab";

        let output: Vec<Vec<&str>> =
            [vec!["a", "a", "b"], vec!["aa", "b"]].to_vec();
        let ret = Solution::partition(s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let s = "a";

        let output: Vec<Vec<&str>> = [vec!["a"]].to_vec();
        let ret = Solution::partition(s);
        assert_eq!(ret, output);
    }
}
