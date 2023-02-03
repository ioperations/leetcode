// For two strings s and t, we say "t divides s" if and only if s = t + ... + t
// (i.e., t is concatenated with itself one or more times). Given two strings
// str1 and str2, return the largest string x such that x divides both str1 and
// str2.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn gcd_of_strings(str1: &str, str2: &str) -> String {
        if str1 == str2 {
            str1.to_string()
        } else {
            let mut abs = str2;
            let mut ab_strl = str1;
            if str1.len() < str2.len() {
                abs = str1;
                ab_strl = str2;
            }
            if abs == &ab_strl[0..abs.len()] {
                Self::gcd_of_strings(&ab_strl[abs.len()..], abs)
            } else {
                String::new()
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let str1 = "ABCABC";
        let str2 = "ABC";
        let output = String::from("ABC");
        let ret = Solution::gcd_of_strings(str1, str2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let str1 = "ABABAB";
        let str2 = "AB";
        let output = String::from("AB");
        let ret = Solution::gcd_of_strings(str1, str2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let str1 = "LEET";
        let str2 = "CODE";
        let output = String::new();
        let ret = Solution::gcd_of_strings(str1, str2);
        assert_eq!(ret, output);
    }
}
