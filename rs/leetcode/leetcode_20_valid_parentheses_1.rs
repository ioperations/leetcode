// Given a string s containing just the characters '(', ')', '{', '}', '[' and
// ']', determine if the input string is valid.
//
// An input string is valid if:
//
// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.
//
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_valid(s: &str) -> bool {
        let mut stack = vec![];
        let chars = s.chars().collect::<Vec<_>>();
        for char in chars {
            match char {
                c @ ('(' | '[' | '{') => {
                    stack.push(c);
                }
                p => {
                    let ret = stack.pop().unwrap_or('*');
                    match p {
                        ')' => return ret == '(',
                        ']' => return ret == '[',
                        '}' => return ret == '{',
                        _ => return false,
                    }
                }
            }
        }
        stack.is_empty()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "()";
        let output = true;
        let ret = Solution::is_valid(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let s = "()[]{}";
        let output = true;
        let ret = Solution::is_valid(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let s = "(]";
        let output = false;
        let ret = Solution::is_valid(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case4_test() {
        let s = "([])";
        let output = true;
        let ret = Solution::is_valid(s);
        assert_eq!(output, ret);
    }

    #[test]
    fn case5_test() {
        let s = "([)]";
        let output = false;
        let ret = Solution::is_valid(s);
        assert_eq!(output, ret);
    }
}
