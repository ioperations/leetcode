/*
    A string s is called good if there are no two different characters in s that
    have the same frequency.

    Given a string s, return the minimum number of characters you need to delete
   to make s good.

    The frequency of a character in a string is the number of times it appears
   in the string. For example, in the string "aab", the frequency of 'a' is 2,
   while the frequency of 'b' is 1.
*/

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    fn min_deletions(s: &str) -> i32 {
        let mut hash = [0; 26];
        for ch in s.chars() {
            let i = ch as usize - 'a' as usize;
            hash[i] += 1;
        }
        hash.sort_unstable();
        let mut ans = 0;
        for i in (0..25).rev() {
            if hash[i] == 0 {
                break;
            }
            if hash[i] >= hash[i + 1] {
                let del_to = (hash[i + 1] - 1).max(0);
                ans += hash[i] - del_to;
                hash[i] = del_to;
            }
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cast1_test() {
        let s = "aab";
        let out = 0;
        let ret = Solution::min_deletions(s);
        assert_eq!(ret, out);
    }

    #[test]
    fn cast2_test() {
        let s = "aaabbbcc";
        let out = 2;
        let ret = Solution::min_deletions(s);
        assert_eq!(ret, out);
    }

    #[test]
    fn cast3_test() {
        let s = "ceabaacb";
        let out = 2;
        let ret = Solution::min_deletions(s);
        assert_eq!(ret, out);
    }
}
