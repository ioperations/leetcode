/*You are given a string s of even length. Split this string into two halves of equal lengths, and let a be the first half and b be the second half.
Two strings are alike if they have the same number of vowels ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains uppercase and lowercase letters.
Return true if a and b are alike. Otherwise, return false.*/

use std::collections::HashSet;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn halves_are_alike(s: &str) -> bool {
        fn same(first: &[u8], second: &[u8]) -> bool {
            let vowels = ['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'];

            let set = vowels.iter().copied().collect::<HashSet<char>>();
            let mut count = 0;

            for i in first {
                let z = *i as char;
                if set.contains(&z) {
                    count += 1;
                }
            }

            let mut count1 = 0;

            for i in second {
                let z = *i as char;
                if set.contains(&z) {
                    count1 += 1;
                }
            }

            count == count1
        }

        let len = s.len();
        if len % 2 == 1 {
            return false;
        }

        let s = s.as_bytes();
        same(&s[0..(len / 2)], &s[(len / 2)..])
    }

    #[allow(unused)]
    pub fn halves_are_alike_v2(s: &str) -> bool {
        let s: Vec<_> = s.chars().collect();
        let vowels = "AEIOUaeiou";
        s[..s.len() / 2]
            .iter()
            .filter(|&x| vowels.contains(*x))
            .count()
            == s[s.len() / 2..]
                .iter()
                .filter(|&x| vowels.contains(*x))
                .count()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "book";
        let ret = Solution::halves_are_alike(s);
        //  a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
        assert!(ret);
    }

    #[test]
    fn case2_test() {
        let s = "textbook";
        let ret = Solution::halves_are_alike(s);
        // a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
        // Notice that the vowel o is counted twice.
        assert!(!ret);
    }

    #[test]
    fn case3_test() {
        let s = "book";
        let ret = Solution::halves_are_alike_v2(s);
        //  a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel. Therefore, they are alike.
        assert!(ret);
    }

    #[test]
    fn case4_test() {
        let s = "textbook";
        let ret = Solution::halves_are_alike_v2(s);
        // a = "text" and b = "book". a has 1 vowel whereas b has 2. Therefore, they are not alike.
        // Notice that the vowel o is counted twice.
        assert!(!ret);
    }
}
