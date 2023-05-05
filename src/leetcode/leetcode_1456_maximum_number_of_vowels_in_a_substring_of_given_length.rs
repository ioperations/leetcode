// Given a string s and an integer k, return the maximum number of vowel letters
// in any substring of s with length k.
//
// Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
//
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_vowels(s: &str, k: i32) -> i32 {
        // 1 <= s.length <= 105
        // s consists of lowercase English letters.
        // 1 <= k <= s.length

        let chars: Vec<char> = s.chars().collect();
        let n = chars.len();
        let k = k as usize;
        let mut res = 0;
        let mut count = 0;

        for i in 0..n {
            if i >= k && Self::is_vowel(chars[i - k]) {
                count -= 1;
            }
            if Self::is_vowel(chars[i]) {
                count += 1;
            }

            res = res.max(count);
        }

        res
    }

    fn is_vowel(c: char) -> bool {
        if c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' {
            return true;
        }
        false
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "abciiidef";
        let k = 3;
        let output = 3;
        let ret = Solution::max_vowels(s, k);
        assert_eq!(ret, output);
        // Explanation: The substring "iii" contains 3 vowel letters.
    }

    #[test]
    fn case2_test() {
        let s = "aeiou";
        let k = 2;
        let output = 2;
        let ret = Solution::max_vowels(s, k);
        assert_eq!(ret, output);
        // Explanation:Any substring of length 2 contains 2 vowels.
    }

    #[test]
    fn case3_test() {
        let s = "leetcode";
        let k = 3;
        let output = 2;
        let ret = Solution::max_vowels(s, k);
        assert_eq!(ret, output);
        // Explanation:"lee", "eet" and "ode" contain 2 vowels.
    }
}
