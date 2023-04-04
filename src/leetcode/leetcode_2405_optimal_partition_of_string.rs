// Given a string s, partition the string into one or more substrings such that
// the characters in each substring are unique. That is, no letter appears in a
// single substring more than once. Return the minimum number of substrings in
// such a partition. Note that each character should belong to exactly one
// substring in a partition.

use std::collections::{HashMap, HashSet};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn partition_string(s: &str) -> i32 {
        // 2 <= s.length <= 105
        // s consists of only English lowercase letters.
        fn my_impl(s: &[char], cache: &mut HashMap<Vec<char>, i32>) -> i32 {
            if s.is_empty() {
                return 0;
            }

            if s.len() == 1 {
                return 1;
            }

            if let Some(&v) = cache.get(&s.to_vec()) {
                return v;
            }
            let mut hs = HashSet::new();
            hs.insert(s[0]);
            let mut ret = std::i32::MAX;

            for (index, &value) in s.iter().enumerate().skip(1) {
                if hs.get(&value).is_some() {
                    // this substring is not allowded anymore
                    let z = my_impl(&s[index..], cache);
                    ret = ret.min(z + 1);
                    break;
                }

                let z = my_impl(&s[index..], cache) + 1;
                hs.insert(value);
                let z2 = my_impl(&s[index + 1..], cache) + 1;
                ret = ret.min(z.min(z2));
            }
            cache.insert(s.into(), ret);
            ret
        }
        let mut hashmap = HashMap::new();
        my_impl(&s.chars().collect::<Vec<_>>(), &mut hashmap)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "abacaba";
        let output = 4;
        let ret = Solution::partition_string(&s);
        assert_eq!(output, ret);
        // Explanation:
        // Two possible partitions are ("a","ba","cab","a") and
        // ("ab","a","ca","ba"). It can be shown that 4 is the minimum
        // number of substrings needed.
        //
    }

    #[test]
    fn case2_test() {
        let s = "ssssss";
        let output = 6;
        let ret = Solution::partition_string(&s);
        assert_eq!(output, ret);
        // Explanation:
        // The only valid partition is ("s","s","s","s","s","s").
    }
}
