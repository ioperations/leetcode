// You are given a string s, which contains stars *.
//
// In one operation, you can:
//
// Choose a star in s.
// Remove the closest non-star character to its left, as well as remove the star
// itself.
//
// Return the string after all stars have been removed.
//
// Note:
//
// The input will be generated such that the operation is always possible.
// It can be shown that the resulting string will always be unique.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn remove_stars(s: String) -> String {
        // 1 <= s.length <= 105
        // s consists of lowercase English letters and stars *.
        // The operation above can be performed on s.
        let mut stack = vec![];
        for i in s.bytes() {
            if i == b'*' {
                let Some(v) = stack.pop() else {
                    return String::from("");
                };
            } else {
                stack.push(i);
            }
        }
        String::from_utf8(stack).unwrap()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "leet**cod*e";
        let output = "lecoe";
        let ret = Solution::remove_stars(s.into());
        assert_eq!(ret, output);
        // Explanation: Performing the removals from left to right:
        // - The closest character to the 1st star is 't' in "leet**cod*e". s
        //   becomes "lee*cod*e".
        // - The closest character to the 2nd star is 'e' in "lee*cod*e". s
        //   becomes "lecod*e".
        // - The closest character to the 3rd star is 'd' in "lecod*e". s
        //   becomes "lecoe".
        // There are no more stars, so we return "lecoe".
    }

    #[test]
    fn case2_test() {
        let s = "erase*****";
        let output = "";
        let ret = Solution::remove_stars(s.into());
        assert_eq!(ret, output);
        // Explanation: The entire string is removed, so we return an empty
        // string.
    }
}
