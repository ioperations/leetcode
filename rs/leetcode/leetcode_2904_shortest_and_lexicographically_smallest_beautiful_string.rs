// You are given a binary string s and a positive integer k.
//
// A substring of s is beautiful if the number of 1's in it is exactly k.
//
// Let len be the length of the shortest beautiful substring.
//
// Return the lexicographically smallest beautiful substring of string s with
// length equal to len. If s doesn't contain a beautiful substring, return an
// empty string.
//
// A string a is lexicographically larger than a string b (of the same length)
// if in the first position where a and b differ, a has a character strictly
// larger than the corresponding character in b.
//
// For example, "abcd" is lexicographically larger than "abcc" because the first
// position they differ is at the fourth character, and d is greater than c.
//
// 1 <= s.length <= 100
// 1 <= k <= s.length
//

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn shortest_beautiful_substring(s: &str, k: i32) -> String {
        let chars: Vec<_> = s.chars().collect();
        let len = chars.len();
        let mut vec = vec![];

        let mut start = 0;
        let mut end = 0;
        let mut cur_len = 0;

        let mut cur_min_len = usize::MAX;

        while end < len {
            let c = chars[end];
            if c == '1' {
                cur_len += 1;
            }

            if cur_len == k {
                let min_len = end - start + 1;
                if min_len < cur_min_len {
                    vec.clear();
                    cur_min_len = min_len;
                    vec.push((start, end));
                } else if min_len == cur_min_len {
                    vec.push((start, end));
                }

                Self::move_right(
                    &mut cur_len,
                    k,
                    &chars,
                    &mut start,
                    end,
                    &mut cur_min_len,
                    &mut vec,
                );
            }
            end += 1;
        }

        Self::lexicographically_smallest_beautiful(&mut vec, &chars)
    }

    fn lexicographically_smallest_beautiful(
        vec: &mut [(usize, usize)],
        chars: &[char],
    ) -> String {
        vec.sort_by(|l, r| {
            let lhs = &chars[l.0..=l.1];
            let rhs = &chars[r.0..=r.1];

            lhs.cmp(rhs)
        });

        if let Some(v) = vec.first() {
            return (v.0..=v.1).fold(String::new(), |mut acc, v| {
                acc.push(chars[v]);
                acc
            });
        }
        String::new()
    }

    fn move_right(
        cur_len: &mut i32,
        k: i32,
        chars: &[char],
        start: &mut usize,
        end: usize,
        cur_min_len: &mut usize,
        vec: &mut Vec<(usize, usize)>,
    ) {
        while *cur_len == k {
            let c = chars[*start];
            if c == '1' {
                *cur_len -= 1;
                *start += 1;
            } else {
                *start += 1;
                let min_len = end - *start + 1;
                if min_len < *cur_min_len {
                    vec.clear();
                    *cur_min_len = min_len;
                    vec.push((*start, end));
                } else if min_len == *cur_min_len {
                    vec.push((*start, end));
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn case1_test() {
        let s = "100011001";
        let k = 3;
        let output = "11001";
        let ret = Solution::shortest_beautiful_substring(&s, k);
        assert_eq!(output, ret);

        // here are 7 beautiful substrings in this example:
        // 1. The substring "[100011]001".
        // 2. The substring "[1000110]01".
        // 3. The substring "[10001100]1".
        // 4. The substring "1[00011001]".
        // 5. The substring "10[0011001]".
        // 6. The substring "100[011001]".
        // 7. The substring "1000[11001]".
        // The length of the shortest beautiful substring is 5.
        // The lexicographically smallest beautiful substring with length 5 is
        // the substring "11001".
        //
    }

    #[test]
    fn case2_test() {
        let s = "1011";
        let k = 2;
        let output = "11";
        let ret = Solution::shortest_beautiful_substring(&s, k);
        assert_eq!(output, ret);
        // There are 3 beautiful substrings in this example:
        // 1. The substring "[101]1".
        // 2. The substring "1[011]".
        // 3. The substring "10[11]".
        // The length of the shortest beautiful substring is 2.
        // The lexicographically smallest beautiful substring with length 2 is
        // the substring "11".
    }

    #[test]
    fn case3_test() {
        let s = "000";
        let k = 1;
        let output = "";
        let ret = Solution::shortest_beautiful_substring(&s, k);
        assert_eq!(output, ret);
        // There are no beautiful substrings in this example.
    }

    #[test]
    fn case4_test() {
        let s = "11000111";
        let k = 1;
        let output = "1";
        let ret = Solution::shortest_beautiful_substring(&s, k);
        assert_eq!(output, ret);
    }
}
