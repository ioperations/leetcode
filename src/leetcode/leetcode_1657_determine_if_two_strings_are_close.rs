// Two strings are considered close if you can attain one from the other using
// the following operations:     Operation 1: Swap any two existing characters.
//         For example, abcde -> aecdb
//     Operation 2: Transform every occurrence of one existing character into
// another existing character, and do the same with the other character.
//         For example, aacabb -> bbcbaa (all a's turn into b's, and all b's
// turn into a's)     You can use the operations on either string as many times
// as necessary.
//
// Given two strings, word1 and word2, return true if word1 and word2 are close,
// and false otherwise.

use std::collections::{HashMap, HashSet};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn close_strings(word1: &str, word2: &str) -> bool {
        if word1.len() != word2.len() {
            return false;
        }

        let mut hm = HashMap::new();

        for i in word1.as_bytes() {
            hm.entry(*i as char).and_modify(|e| *e += 1).or_insert(0);
        }

        let mut v = hm.values().copied().collect::<Vec<usize>>();
        let s1 = hm.keys().copied().collect::<HashSet<char>>();
        v.sort_unstable();

        let mut hm = HashMap::new();
        for i in word2.as_bytes() {
            hm.entry(*i as char).and_modify(|e| *e += 1).or_insert(0);
        }

        let mut v1 = hm.values().copied().collect::<Vec<usize>>();
        let s2 = hm.keys().copied().collect::<HashSet<char>>();
        v1.sort_unstable();
        v == v1 && s1 == s2
    }

    #[allow(unused)]
    pub fn close_strings_v2(word1: &str, word2: &str) -> bool {
        let mut counts1 = [0; 26];
        let mut counts2 = [0; 26];
        for &b in word1.as_bytes() {
            counts1[(b - b'a') as usize] += 1;
        }
        for &b in word2.as_bytes() {
            counts2[(b - b'a') as usize] += 1;
        }
        if (0..26).any(|i| (counts1[i] > 0) != (counts2[i] > 0)) {
            return false;
        }
        counts1.sort_unstable();
        counts2.sort_unstable();
        counts1 == counts2
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let word1 = "abc";
        let word2 = "bca";
        let output = true;
        // Explanation: You can attain word2 from word1 in 2 operations.
        // Apply Operation 1: "abc" -> "acb"
        // Apply Operation 1: "acb" -> "bca"

        let ret = Solution::close_strings(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let word1 = "a";
        let word2 = "aa";
        let output = false;
        // It is impossible to attain word2 from word1, or vice versa, in any
        // number of operations.

        let ret = Solution::close_strings(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let word1 = "cabbba";
        let word2 = "abbccc";
        let output = true;
        // You can attain word2 from word1 in 3 operations.
        // Apply Operation 1: "cabbba" -> "caabbb"
        // Apply Operation 2: "caabbb" -> "baaccc"
        // Apply Operation 2: "baaccc" -> "abbccc"

        let ret = Solution::close_strings(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let word1 = "uau";
        let word2 = "ssx";
        let output = false;
        // You can attain word2 from word1 in 3 operations.
        // Apply Operation 1: "cabbba" -> "caabbb"
        // Apply Operation 2: "caabbb" -> "baaccc"
        // Apply Operation 2: "baaccc" -> "abbccc"

        let ret = Solution::close_strings(word1, word2);
        assert_eq!(ret, output);
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn case1_test() {
        let word1 = "abc";
        let word2 = "bca";
        let output = true;
        // Explanation: You can attain word2 from word1 in 2 operations.
        // Apply Operation 1: "abc" -> "acb"
        // Apply Operation 1: "acb" -> "bca"

        let ret = Solution::close_strings_v2(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let word1 = "a";
        let word2 = "aa";
        let output = false;
        // It is impossible to attain word2 from word1, or vice versa, in any
        // number of operations.

        let ret = Solution::close_strings_v2(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let word1 = "cabbba";
        let word2 = "abbccc";
        let output = true;
        // You can attain word2 from word1 in 3 operations.
        // Apply Operation 1: "cabbba" -> "caabbb"
        // Apply Operation 2: "caabbb" -> "baaccc"
        // Apply Operation 2: "baaccc" -> "abbccc"

        let ret = Solution::close_strings_v2(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let word1 = "uau";
        let word2 = "ssx";
        let output = false;
        // You can attain word2 from word1 in 3 operations.
        // Apply Operation 1: "cabbba" -> "caabbb"
        // Apply Operation 2: "caabbb" -> "baaccc"
        // Apply Operation 2: "baaccc" -> "abbccc"

        let ret = Solution::close_strings_v2(word1, word2);
        assert_eq!(ret, output);
    }
}
