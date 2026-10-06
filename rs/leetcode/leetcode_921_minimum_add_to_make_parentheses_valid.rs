// A parentheses string is valid if and only if:
//
// It is the empty string,
// It can be written as AB (A concatenated with B), where A and B are valid
// strings, or It can be written as (A), where A is a valid string.
// You are given a parentheses string s. In one move, you can insert a
// parenthesis at any position of the string.
//
// For example, if s = "()))", you can insert an opening parenthesis to be
// "(()))" or a closing parenthesis to be "())))".
// Return the minimum number of moves required to make s valid.
//
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn min_add_to_make_valid(s: &str) -> i32 {
        let mut ret = 0;

        let mut preleft_par = 0;
        for i in s.bytes() {
            if i == b'(' {
                preleft_par += 1;
            } else if preleft_par > 0 {
                preleft_par -= 1;
            } else {
                ret += 1;
            }
        }

        ret + preleft_par
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "())";
        let output = 1;
        let ret = Solution::min_add_to_make_valid(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let s = "(((";
        let output = 3;
        let ret = Solution::min_add_to_make_valid(s);
        assert_eq!(output, ret);
    }
}
