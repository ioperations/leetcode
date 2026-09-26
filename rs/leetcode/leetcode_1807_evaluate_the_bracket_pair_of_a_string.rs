// You are given a string s that contains some bracket pairs, with each pair
// containing a non-empty key.
//
// For example, in the string "(name)is(age)yearsold", there are two bracket
// pairs that contain the keys "name" and "age". You know the values of a wide
// range of keys. This is represented by a 2D string array knowledge where each
// knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.
//
// You are tasked to evaluate all of the bracket pairs. When you evaluate a
// bracket pair that contains some key keyi, you will:
//
// Replace keyi and the bracket pair with the key's corresponding valuei.
// If you do not know the value of the key, you will replace keyi and the
// bracket pair with a question mark "?" (without the quotation marks). Each key
// will appear at most once in your knowledge. There will not be any nested
// brackets in s.
//
// Return the resulting string after evaluating all of the bracket pairs.
//
// 1 <= s.length <= 105
// 0 <= knowledge.length <= 105
// knowledge[i].length == 2
// 1 <= keyi.length, valuei.length <= 10
// s consists of lowercase English letters and round brackets '(' and ')'.
// Every open bracket '(' in s will have a corresponding close bracket ')'.
// The key in each bracket pair of s will be non-empty.
// There will not be any nested bracket pairs in s.
// keyi and valuei consist of lowercase English letters.
// Each keyi in knowledge is unique.

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn evaluate(s: &str, knowledge: &[Vec<String>]) -> String {
        let mut hm = HashMap::new();
        for v in knowledge {
            hm.insert(v[0].clone(), v[1].clone());
        }

        let question_string = "?".to_string();
        let mut res = String::new();

        let mut cur = res.clone();
        let mut capture = false;

        for i in s.chars() {
            if i == ')' {
                let result = hm.get(&cur).unwrap_or(&question_string);
                res.push_str(result);
                cur = String::new();
                capture = false;
            } else if capture {
                cur.push(i);
            } else if i == '(' {
                capture = true;
            } else {
                res.push(i);
            }
        }

        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let s = "(name)is(age)yearsold".to_string();
        let knowledge = [["name", "bob"], ["age", "two"]]
            .iter()
            .map(|v| vec![v[0].to_string(), v[1].to_string()])
            .collect::<Vec<Vec<_>>>();
        let output = "bobistwoyearsold".to_string();
        let ret = Solution::evaluate(&s, &knowledge);
        assert_eq!(output, ret);
        // The key "name" has a value of "bob", so replace "(name)" with "bob".
        // The key "age" has a value of "two", so replace "(age)" with "two".
    }

    #[test]
    fn case2_test() {
        let s = "hi(name)".to_string();
        let knowledge = [["a", "b"]]
            .iter()
            .map(|v| vec![v[0].to_string(), v[1].to_string()])
            .collect::<Vec<Vec<_>>>();
        let output = "hi?";
        let ret = Solution::evaluate(&s, &knowledge);
        assert_eq!(output, ret);
        // As you do not know the value of the key "name", replace "(name)" with
        // "?".
    }

    #[test]
    fn case3_test() {
        let s = "(a)(a)(a)aaa".to_string();
        let knowledge = [["a", "yes"]]
            .iter()
            .map(|v| vec![v[0].to_string(), v[1].to_string()])
            .collect::<Vec<Vec<_>>>();
        let output = "yesyesyesaaa";
        let ret = Solution::evaluate(&s, &knowledge);
        assert_eq!(output, ret);
        // The same key can appear multiple times.
        // The key "a" has a value of "yes", so replace all occurrences of "(a)"
        // with "yes". Notice that the "a"s not in a bracket pair are
        // not evaluated.
    }
}
