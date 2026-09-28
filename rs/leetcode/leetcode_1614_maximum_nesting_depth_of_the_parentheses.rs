// Given a valid parentheses string s, return the nesting depth of s. The
// nesting depth is the maximum number of nested parentheses.
//
// 1 <= s.length <= 100
// s consists of digits 0-9 and characters '+', '-', '*', '/', '(', and ')'.
// It is guaranteed that parentheses expression s is a VPS.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_depth(s: &str) -> i32 {
        let mut max = 0;
        let mut par = 0;
        let vec = s.chars().collect::<Vec<_>>();
        for &i in &vec {
            if i == '(' {
                par += 1;
                max = par.max(max);
            } else if i == ')' {
                par -= 1;
            }
        }
        max
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "(1+(2*3)+((8)/4))+1".to_string();
        let output = 3;

        let ret = Solution::max_depth(&s);
        assert_eq!(output, ret);
        // Explanation:
        // Digit 8 is inside of 3 nested parentheses in the string.
    }

    #[test]
    fn case2_test() {
        let s = "(1)+((2))+(((3)))".to_string();
        let output = 3;

        let ret = Solution::max_depth(&s);
        assert_eq!(output, ret);
        // Explanation:
        // Digit 8 is inside of 3 nested parentheses in the string.
    }

    #[test]
    fn case3_test() {
        let s = "()(())((()()))".to_string();
        let output = 3;

        let ret = Solution::max_depth(&s);
        assert_eq!(output, ret);
        // Explanation:
        // Digit 8 is inside of 3 nested parentheses in the string.
    }
}
