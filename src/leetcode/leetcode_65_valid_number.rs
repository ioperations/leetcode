// A valid number can be split up into these components (in order):
//
// A decimal number or an integer.
// (Optional) An 'e' or 'E', followed by an integer.
//
// A decimal number can be split up into these components (in order):
//
// (Optional) A sign character (either '+' or '-').
// One of the following formats:
// One or more digits, followed by a dot '.'.
// One or more digits, followed by a dot '.', followed by one or more digits.
// A dot '.', followed by one or more digits.
//
// An integer can be split up into these components (in order):
//
// (Optional) A sign character (either '+' or '-').
// One or more digits.
//
// For example, all the following are valid numbers: ["2", "0089", "-0.1",
// "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93",
// "-123.456e789"], while the following are not valid numbers: ["abc", "1a",
// "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].
//
// Given a string s, return true if s is a valid number.

#[allow(unused)]
struct Parser;

impl Parser {
    #[allow(unused)]
    fn parse_number(s: &[char]) -> Option<&[char]> {
        if let Some(v) = Self::parse_digitail(s) {
            if let Some(v) = Self::consume_scitinic(v) {
                if let Some(v) = Self::parse_integer(v) {
                    return Some(v);
                }
                return None;
            }
            return Some(v);
        }
        if let Some(v) = Self::parse_integer(s) {
            if let Some(v) = Self::consume_scitinic(v) {
                if let Some(v) = Self::parse_integer(v) {
                    return Some(v);
                }
                return None;
            }
            return None;
        }
        None
    }

    #[allow(unused)]
    fn consume_scitinic(s: &[char]) -> Option<&[char]> {
        if s.is_empty() {
            return None;
        }
        if ['e', 'E'].contains(&s[0]) {
            return Some(&s[1..]);
        }
        None
    }

    #[allow(unused)]
    fn consume_dot(s: &[char]) -> Option<&[char]> {
        if s.is_empty() {
            return None;
        }
        if s[0] == '.' {
            return Some(&s[1..]);
        }
        None
    }

    #[allow(unused)]
    fn consume_plus_or_minus(s: &[char]) -> Option<&[char]> {
        if s.is_empty() {
            return None;
        }
        // consume 'e' && 'E'
        if ['+', '-'].contains(&s[0]) {
            Some(&s[1..])
        } else {
            None
        }
    }

    #[allow(unused)]
    fn consume_all_digits(s: &[char]) -> Option<&[char]> {
        let len = s.len();
        let mut index = 0;
        while index < len {
            if !s[index].is_ascii_digit() {
                break;
            }
            index += 1;
        }
        if index == 0 {
            return None;
        }
        Some(&s[index..])
    }

    #[allow(unused)]
    fn parse_digitail(s: &[char]) -> Option<&[char]> {
        let s = match Self::consume_plus_or_minus(s) {
            Some(v) => v,
            None => s,
        };
        if let Some(s) = Self::consume_dot(s) {
            if let Some(left) = Self::consume_all_digits(s) {
                return Some(left);
            }
            return None;
        }
        if let Some(left) = Self::consume_all_digits(s) {
            if let Some(left) = Self::consume_dot(left) {
                if let Some(left) = Self::consume_all_digits(left) {
                    return Some(left);
                }
                return Some(left);
            }
            return Some(left);
        }
        None
    }

    #[allow(unused)]
    fn parse_integer(s: &[char]) -> Option<&[char]> {
        let s = match Self::consume_plus_or_minus(s) {
            Some(v) => v,
            None => s,
        };

        if let Some(s) = Self::consume_all_digits(s) {
            return Some(s);
        }
        None
    }
}

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_number(s: &str) -> bool {
        // 1 <= s.length <= 20
        // s consists of only English letters (both uppercase and lowercase),
        // digits (0-9), plus '+', minus '-', or dot '.'.
        match Parser::parse_number(&s.chars().collect::<Vec<char>>()) {
            Some(v) => v.is_empty(),
            None => false,
        }
    }
}

#[cfg(test)]
mod parser_test {
    use super::*;

    #[test]
    fn consume_plus_or_minus_or_return_test() {
        let s = "0".chars().collect::<Vec<char>>();
        let ret = Parser::consume_plus_or_minus(&s);
        assert_eq!(ret, None);

        let s = "+".chars().collect::<Vec<char>>();
        let ret = Parser::consume_plus_or_minus(&s);
        let expected = "".chars().collect::<Vec<char>>();
        match ret {
            Some(v) => {
                assert_eq!(v, expected);
            }
            None => panic!("not expected"),
        }
    }

    #[test]
    fn consume_all_digits_test() {
        let s = "0".chars().collect::<Vec<char>>();
        let ret = Parser::consume_all_digits(&s);
        let expected = "".chars().collect::<Vec<char>>();
        match ret {
            Some(v) => {
                assert_eq!(v, expected);
            }
            None => panic!("not expected"),
        }

        let s = "+".chars().collect::<Vec<char>>();
        let ret = Parser::consume_all_digits(&s);
        assert_eq!(ret, None, "{}", "ok");
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "0";
        let ret = Solution::is_number(&s);
        assert!(ret);
    }

    #[test]
    fn case2_test() {
        let s = "e";
        let ret = Solution::is_number(&s);
        assert!(!ret);
    }

    #[test]
    fn case3_test() {
        let s = ".";
        let ret = Solution::is_number(&s);
        assert!(!ret);
    }

    #[test]
    fn case4_test() {
        let s = [
            "2",
            "0089",
            "-0.1",
            "+3.14",
            "4.",
            "-.9",
            "2e10",
            "-90E3",
            "3e+7",
            "+6e-1",
            "53.5e93",
            "-123.456e789",
        ];
        for i in s {
            let ret = Solution::is_number(&i);
            assert!(ret, "{}", i);
        }
    }

    #[test]
    fn case5_test() {
        let s = ["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"];
        for i in s {
            let ret = Solution::is_number(&i);
            assert!(!ret, "{}", i);
        }
    }
}
