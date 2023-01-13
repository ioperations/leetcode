// Given a pattern and a string s, find if s follows the same pattern.
// Here follow means a full match
// such that there is a bijection between a letter in pattern and a non-empty word in s.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn word_pattern(pattern: &str, s: &str) -> bool {
        use std::collections::HashMap;
        use std::collections::HashSet;

        let mut bijection_mapping: HashMap<char, &str> = HashMap::new();
        let mut words: Vec<&str> = s.split_whitespace().collect();
        let word_set: HashSet<&str> = words.iter().copied().collect();

        if pattern.len() != words.len() {
            return false;
        }

        for (i, c) in pattern.chars().enumerate() {
            if let Some(value) = bijection_mapping.get(&c) {
                if value != &words[i] {
                    return false;
                }
            }
            bijection_mapping.insert(c, words[i]);
        }
        bijection_mapping.len() == word_set.len()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let pattern = "abba";
        let s = "dog cat cat dog";
        let output = true;
        let ret = Solution::word_pattern(pattern, s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let pattern = "abba";
        let s = "dog cat cat fish";
        let output = false;
        let ret = Solution::word_pattern(pattern, s);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let pattern = "aaaa";
        let s = "dog cat cat dog";
        let output = false;
        let ret = Solution::word_pattern(pattern, s);
        assert_eq!(ret, output);
    }
}
