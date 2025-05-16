// Given an array of strings words (without duplicates), return all the
// concatenated words in the given list of words. A concatenated word is defined
// as a string that is comprised entirely of at least two shorter words in the
// given array.

use std::collections::HashSet;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_all_concatenated_words_in_a_dict(
        words: &[String],
    ) -> Vec<String> {
        let mut store = HashSet::new();
        for w in words {
            store.insert(w.clone());
        }

        let mut ans = Vec::new();
        for w in words {
            if Self::foo(0, 0, w, &store) {
                ans.push(w.clone());
            }
        }

        ans
    }

    fn foo(i: usize, cnt: usize, s: &str, store: &HashSet<String>) -> bool {
        if i == s.len() {
            return cnt > 1;
        }

        for j in i..s.len() {
            if store.contains(&s[i..=j]) && Self::foo(j + 1, cnt + 1, s, store)
            {
                return true;
            }
        }

        false
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    pub trait ToString {
        fn to_vec_str(&self) -> Vec<String>;
    }

    pub trait ToHashSet {
        fn to_hash_str(&self) -> HashSet<String>;
    }

    impl<T, const N: usize> ToString for [T; N]
    where
        T: std::string::ToString,
    {
        fn to_vec_str(&self) -> Vec<String> {
            self.into_iter()
                .map(std::string::ToString::to_string)
                .collect::<Vec<String>>()
        }
    }

    impl<T, const N: usize> ToHashSet for [T; N]
    where
        T: std::string::ToString,
    {
        fn to_hash_str(&self) -> HashSet<String> {
            self.into_iter()
                .map(std::string::ToString::to_string)
                .collect::<HashSet<String>>()
        }
    }

    impl ToHashSet for Vec<String> {
        fn to_hash_str(&self) -> HashSet<String> {
            self.into_iter()
                .map(std::string::String::to_string)
                .collect::<HashSet<String>>()
        }
    }

    #[test]
    fn case1_test() {
        let words = [
            "cat",
            "cats",
            "catsdogcats",
            "dog",
            "dogcatsdog",
            "hippopotamuses",
            "rat",
            "ratcatdogcat",
        ]
        .to_vec_str();
        let output =
            ["catsdogcats", "dogcatsdog", "ratcatdogcat"].to_hash_str();
        // Explanation: "catsdogcats" can be concatenated by "cats", "dog" and
        // "cats"; "dogcatsdog" can be concatenated by "dog", "cats" and
        // "dog"; "ratcatdogcat" can be concatenated by "rat", "cat",
        // "dog" and "cat".
        let ret = Solution::find_all_concatenated_words_in_a_dict(&words);
        let ret = ret.to_hash_str();
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let words = ["cat", "dog", "catdog"].to_vec_str();
        let output = ["catdog"].to_hash_str();
        // Explanation: "catsdogcats" can be concatenated by "cats", "dog" and
        // "cats"; "dogcatsdog" can be concatenated by "dog", "cats" and
        // "dog"; "ratcatdogcat" can be concatenated by "rat", "cat",
        // "dog" and "cat".
        let ret = Solution::find_all_concatenated_words_in_a_dict(&words);
        let ret = ret.to_hash_str();
        assert_eq!(output, ret);
    }
}
