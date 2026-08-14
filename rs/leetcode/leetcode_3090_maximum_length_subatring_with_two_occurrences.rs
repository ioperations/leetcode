// Given a string s, return the maximum length of a substring such that it
// contains at most two occurrences of each character.
//

use std::collections::HashMap;

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn maximum_length_substring(s: &str) -> u32 {
        let mut cnt: i32 = 0;
        let mut start = 0;
        let mut end = 0;

        let size = s.len();
        let chars = s.chars().collect::<Vec<char>>();

        let mut feq: HashMap<char, i32> = HashMap::new();
        while end < size {
            let x = chars[end];
            feq.entry(x)
                .and_modify(|x| {
                    *x += 1;
                })
                .or_insert(1);

            while *feq.get(&x).unwrap() == 3 {
                let x = chars[start];
                feq.entry(x).and_modify(|x| {
                    *x -= 1;
                });
                start += 1;
            }

            cnt = cnt.max((end as i32) - (start as i32) as i32 + 1);
            end += 1;
        }
        cnt as u32
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let s = "bcbbbcba";
        let output = 4;
        let ret = Solution::maximum_length_substring(&s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let s = "aaaa";
        let output = 2;
        let ret = Solution::maximum_length_substring(&s);
        assert_eq!(output, ret);
        // The following substring has a length of 2 and contains at most two
        // occurrences of each character: "aa".
    }
}
