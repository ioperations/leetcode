// A parentheses string is a non-empty string consisting only of '(' and ')'. It
// is valid if any of the following conditions is true:
//
// It is ().
// It can be written as AB (A concatenated with B), where A and B are valid
// parentheses strings. It can be written as (A), where A is a valid parentheses
// string.
//
// You are given a parentheses string s and a string locked, both of length n.
// locked is a binary string consisting only of '0's and '1's. For each index i
// of locked,
//
// If locked[i] is '1', you cannot change s[i].
// But if locked[i] is '0', you can change s[i] to either '(' or ')'.
//
// Return true if you can make s a valid parentheses string. Otherwise, return
// false.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn can_be_valid(s: &str, locked: &str) -> bool {
        if (!s.len().is_multiple_of(2)) {
            return false;
        }
        Self::scan(s, locked, '(', ')') && Self::scan(s, locked, ')', '(')
    }

    fn scan(s: &str, locked: &str, ch1: char, ch2: char) -> bool {
        let s = if ch1 == '(' {
            s.chars().collect::<Vec<char>>()
        } else {
            s.chars().rev().collect::<Vec<char>>()
        };

        let locked = if ch1 == '(' {
            locked.chars().collect::<Vec<char>>()
        } else {
            locked.chars().rev().collect::<Vec<char>>()
        };

        let (mut balance, mut available) = (0i32, 0i32);

        for i in 0..s.len() {
            if locked[i] == '0' {
                available += 1;
                continue;
            }
            if s[i] == ch1 {
                balance += 1;
            }
            if s[i] == ch2 {
                balance -= 1;
            }
            if balance >= 0 {
                continue;
            }

            if available == 0 {
                return false;
            }
            available -= 1;
            balance += 1;
        }

        true
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "))()))";
        let locked = "010100";
        let ret = Solution::can_be_valid(s, locked);
        assert!(ret);
        // Explanation: locked[1] == '1' and locked[3] == '1', so we cannot
        // change s[1] or s[3]. We change s[0] and s[4] to '(' while
        // leaving s[2] and s[5] unchanged to make s valid.
    }

    #[test]
    fn case2_test() {
        let s = "()()";
        let locked = "0000";
        let ret = Solution::can_be_valid(s, locked);
        assert!(ret);
        // We do not need to make any changes because s is already valid.
    }

    #[test]
    fn case3_test() {
        let s = ")";
        let locked = "0";
        let ret = Solution::can_be_valid(s, locked);
        assert!(!ret);
        // locked permits us to change s[0].
        // Changing s[0] to either '(' or ')' will not make s valid.
    }

    #[test]
    fn case4_test() {
        let s = "()";
        let locked = "11";
        let ret = Solution::can_be_valid(s, locked);
        assert!(ret);
        // locked permits us to change s[0].
        // Changing s[0] to either '(' or ')' will not make s valid.
    }

    #[test]
    fn case5_test() {
        let s = "((()";
        let locked = "0011";
        let ret = Solution::can_be_valid(s, locked);
        assert!(ret);
        // locked permits us to change s[0].
        // Changing s[0] to either '(' or ')' will not make s valid.
    }

    #[test]
    fn case6_test() {
        let s = "())(()(()(())()())(())((())(()())((())))))(((((((())(()))))(";
        let locked =
            "100011110110011011010111100111011101111110000101001101001111";
        let ret = Solution::can_be_valid(s, locked);
        assert!(!ret);
        // locked permits us to change s[0].
        // Changing s[0] to either '(' or ')' will not make s valid.
    }

    #[test]
    fn case7_test() {
        let s = "())()))()(()(((())(()()))))((((()())(())";
        let locked = "1011101100010001001011000000110010100101";
        let ret = Solution::can_be_valid(s, locked);
        assert!(ret);
        // locked permits us to change s[0].
        // Changing s[0] to either '(' or ')' will not make s valid.
    }
}
