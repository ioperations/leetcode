// You are given a string s that consists of lower case English letters and
// brackets.
//
// Reverse the strings in each pair of matching parentheses, starting from the
// innermost one.
//
// Your result should not contain any brackets.
//
// 1 <= s.length <= 2000
// s only contains lower case English characters and parentheses.
// It is guaranteed that all parentheses are balanced.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn reverse_parentheses(s: &str) -> String {
        let len = s.len();
        let mut vec: Vec<char> = Vec::with_capacity(len);
        let c = s.chars().collect::<Vec<_>>();

        for i in c {
            if i == ')' {
                let mut s = vec![];

                while let Some(v) = vec.pop() {
                    if v == '(' {
                        for &p in &s {
                            vec.push(p);
                        }
                        break;
                    }
                    s.push(v);
                }
                continue;
            }
            vec.push(i);
        }

        let mut ret = String::new();
        for i in vec {
            ret.push(i);
        }

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "(abcd)";
        let output = "dcba";
        let ret = Solution::reverse_parentheses(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let s = "(u(love)i)";
        let output = "iloveu";
        let ret = Solution::reverse_parentheses(s);
        assert_eq!(output, ret);
        // The substring "love" is reversed first, then the whole string is
        // reversed.
    }

    #[test]
    fn case3_test() {
        let s = "(ed(et(oc))el)";
        let output = "leetcode";
        let ret = Solution::reverse_parentheses(s);
        assert_eq!(output, ret);
        // First, we reverse the substring "oc", then "etco", and finally, the
        // whole string.
    }
}
