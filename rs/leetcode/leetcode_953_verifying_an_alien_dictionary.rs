// In an alien language, surprisingly, they also use English lowercase letters,
// but possibly in a different order. The order of the alphabet is some
// permutation of lowercase letters. Given a sequence of words written in the
// alien language, and the order of the alphabet, return true if and only if the
// given words are sorted lexicographically in this alien language.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_alien_sorted(words: &[&str], order: &str) -> bool {
        // 1 <= words.length <= 100
        // 1 <= words[i].length <= 20
        // order.length == 26
        // All characters in words[i] and order are English lowercase letters.
        use std::collections::HashMap;
        use std::iter;

        let mut hm = HashMap::new();

        for (i, j) in order.chars().enumerate() {
            hm.entry(j).or_insert(i + 1);
        }
        hm.entry('0').or_insert(0);

        let less = |i: &str, j: &str| -> bool {
            // todo
            let max_len = i.len().max(j.len());

            for (first, second) in i
                .chars()
                .chain(iter::repeat('0'))
                .zip(j.chars().chain(iter::repeat('0')))
                .take(max_len)
            {
                match hm.get(&first).cmp(&hm.get(&second)) {
                    std::cmp::Ordering::Less => {
                        return true;
                    }

                    std::cmp::Ordering::Equal => {}
                    std::cmp::Ordering::Greater => {
                        return false;
                    }
                }
            }
            true
        };
        for (&i, &j) in words.iter().zip(words.iter().skip(1)) {
            if less(i, j) {
                continue;
            }
            return false;
        }
        true
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let words = ["hello", "leetcode"];
        let order = "hlabcdefgijkmnopqrstuvwxyz";
        let output = true;
        // Explanation: As 'h' comes before 'l' in this language, then the
        // sequence is sorted.
        let ret = Solution::is_alien_sorted(&words, order);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let words = ["word", "world", "row"];
        let order = "worldabcefghijkmnpqstuvxyz";
        let output = false;
        // As 'd' comes after 'l' in this language, then words[0] > words[1],
        // hence the sequence is unsorted.
        let ret = Solution::is_alien_sorted(&words, order);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let words = ["apple", "app"];
        let order = "abcdefghijklmnopqrstuvwxyz";
        let output = false;
        // The first three characters "app" match, and the second string is
        // shorter (in size.) According to lexicographical rules "apple" >
        // "app", because 'l' > '∅', where '∅' is defined as the blank character
        // which is less than any other character (More info).
        let ret = Solution::is_alien_sorted(&words, order);
        assert_eq!(ret, output);
    }
}
