// Given two strings needle and haystack, return the index of the first
// occurrence of needle in haystack, or -1 if needle is not part of haystack.

#![allow(unused)]
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn str_str(haystack: &str, needle: &str) -> i32 {
        // 1 <= haystack.length, needle.length <= 104
        // haystack and needle consist of only lowercase English characters.
        let myimpl = |haystak: &str, needle: &str| -> i32 {
            // haystack and needle consist of only lowercase English characters.
            let haystak_len = haystak.len();
            let needle_len = needle.len();

            if haystak_len < needle_len {
                return -1;
            }

            for i in 0..=(haystak_len - needle_len) {
                let val = &haystak[i..(i + needle_len)];
                if *val == *needle {
                    return i as i32;
                }
            }

            -1
        };
        myimpl(haystack, needle)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let haystack = "sadbutsad";
        let needle = "sad";
        let output = 0;
        // Explanation: "sad" occurs at index 0 and 6.
        // The first occurrence is at index 0, so we return 0.
        let ret = Solution::str_str(haystack, needle);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let haystack = "leetcode";
        let needle = "leeto";
        let output = -1;
        // Explanation: "leeto" did not occur in "leetcode", so we return -1.
        let ret = Solution::str_str(haystack, needle);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let haystack = "a";
        let needle = "a";
        let output = 0;
        // Explanation: "leeto" did not occur in "leetcode", so we return -1.
        let ret = Solution::str_str(haystack, needle);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let haystack = "ba";
        let needle = "a";
        let output = 1;
        // Explanation: "leeto" did not occur in "leetcode", so we return -1.
        let ret = Solution::str_str(haystack, needle);
        assert_eq!(ret, output);
    }
}
