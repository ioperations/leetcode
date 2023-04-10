// Given a string s containing just the characters '(', ')', '{', '}', '[' and
// ']', determine if the input string is valid.
//
// An input string is valid if:
//
// Open brackets must be closed by the same type of brackets.
// Open brackets must be closed in the correct order.
// Every close bracket has a corresponding open bracket of the same type.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_valid(s: &str) -> bool {
        // 1 <= s.length <= 104
        // s consists of parentheses only '()[]{}'.
        let mut stack = vec![];
        for i in s.bytes() {
            if [b'{', b'[', b'('].contains(&i) {
                stack.push(i);
            } else {
                let Some(v) = stack.pop() else { return false };
                match v {
                    b'{' => {
                        if i != b'}' {
                            return false;
                        }
                    }
                    b'[' => {
                        if i != b']' {
                            return false;
                        }
                    }

                    b'(' => {
                        if i != b')' {
                            return false;
                        }
                    }
                    _ => return false,
                };
            }
        }
        stack.is_empty()
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "()";
        let output = true;
        let ret = Solution::is_valid(s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let s = "()[]{}";
        let output = true;
        let ret = Solution::is_valid(s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let s = "(]";
        let output = false;
        let ret = Solution::is_valid(s);
        assert_eq!(ret, output);
    }
}
