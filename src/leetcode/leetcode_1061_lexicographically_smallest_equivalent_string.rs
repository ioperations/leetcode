// You are given two strings of the same length s1 and s2 and a string baseStr.
// We say s1[i] and s2[i] are equivalent characters.
// For example, if s1 = "abc" and s2 = "cde", then we have 'a' == 'c', 'b' == 'd', and 'c' == 'e'.
// Equivalent characters follow the usual rules of any equivalence relation:
// Reflexivity: 'a' == 'a'.
// Symmetry: 'a' == 'b' implies 'b' == 'a'.
// Transitivity: 'a' == 'b' and 'b' == 'c' implies 'a' == 'c'.
// For example, given the equivalency information from s1 = "abc" and s2 = "cde",
// "acd" and "aab" are equivalent strings of baseStr = "eed",
// and "aab" is the lexicographically smallest equivalent string of baseStr.
// Return the lexicographically smallest equivalent string of baseStr
// by using the equivalency information from s1 and s2.

use std::collections::{BTreeSet, HashMap};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn smallest_equivalent_string(s1: &str, s2: &str, base_str: &str) -> String {
        let mut p = (0..26).into_iter().collect();

        s1.as_bytes()
            .iter()
            .zip(s2.as_bytes().iter())
            .for_each(|(&k, &v)| {
                Self::union_join(&mut p, (k - b'a') as usize, (v - b'a') as usize);
            });

        let mut mp = HashMap::<usize, BTreeSet<char>>::new();
        for c in 'a'..='z' {
            let mut k = (c as u8 - b'a') as usize;
            mp.entry(Self::find(&mut p, k)).or_default().insert(c);
        }

        base_str
            .as_bytes()
            .iter()
            .map(|&c| {
                let k = (c - b'a') as usize;
                *mp.get(&Self::find(&mut p, k))
                    .unwrap()
                    .iter()
                    .next()
                    .unwrap()
            })
            .collect::<String>()
    }

    #[allow(unused)]
    fn find(p: &mut Vec<usize>, i: usize) -> usize {
        if p[i] == i {
            return i;
        }
        p[i] = Self::find(p, p[i]);
        p[i]
    }

    #[allow(unused)]
    fn union_join(p: &mut Vec<usize>, key: usize, value: usize) {
        let (u, v) = (Self::find(p, key), Self::find(p, value));
        p[u] = v;
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s1 = "parker";
        let s2 = "morris";
        let base_str = "parser";
        let output = "makkek";
        // Explanation: Based on the equivalency information in s1 and s2, we can group their characters as [m,p], [a,o], [k,r,s], [e,i].
        // The characters in each group are equivalent and sorted in lexicographical order.
        // So the answer is "makkek".
        let ret = Solution::smallest_equivalent_string(s1, s2, base_str);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let s1 = "hello";
        let s2 = "world";
        let base_str = "hold";
        let output = "hdld";
        // Based on the equivalency information in s1 and s2, we can group their characters as [h,w], [d,e,o], [l,r].
        // So only the second letter 'o' in baseStr is changed to 'd', the answer is "hdld".
        let ret = Solution::smallest_equivalent_string(s1, s2, base_str);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let s1 = "leetcode";
        let s2 = "programs";
        let base_str = "sourcecode";
        let output = "aauaaaaada";
        // We group the equivalent characters in s1 and s2 as [a,o,e,r,s,c], [l,p], [g,t] and [d,m],
        // thus all letters in baseStr except 'u' and 'd' are transformed to 'a', the answer is "aauaaaaada".
        let ret = Solution::smallest_equivalent_string(s1, s2, base_str);
        assert_eq!(ret, output);
    }
}
