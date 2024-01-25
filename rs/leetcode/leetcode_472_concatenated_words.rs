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
        .into_iter()
        .map(std::string::ToString::to_string)
        .collect::<Vec<String>>();
        let output = ["catsdogcats", "dogcatsdog", "ratcatdogcat"]
            .into_iter()
            .map(std::string::ToString::to_string)
            .collect::<HashSet<String>>();
        // Explanation: "catsdogcats" can be concatenated by "cats", "dog" and
        // "cats"; "dogcatsdog" can be concatenated by "dog", "cats" and
        // "dog"; "ratcatdogcat" can be concatenated by "rat", "cat",
        // "dog" and "cat".
        let ret = Solution::find_all_concatenated_words_in_a_dict(&words);
        let ret = ret.into_iter().collect::<HashSet<String>>();
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let words = ["cat", "dog", "catdog"]
            .into_iter()
            .map(std::string::ToString::to_string)
            .collect::<Vec<String>>();
        let output = ["catdog"]
            .into_iter()
            .map(std::string::ToString::to_string)
            .collect::<HashSet<String>>();
        // Explanation: "catsdogcats" can be concatenated by "cats", "dog" and
        // "cats"; "dogcatsdog" can be concatenated by "dog", "cats" and
        // "dog"; "ratcatdogcat" can be concatenated by "rat", "cat",
        // "dog" and "cat".
        let ret = Solution::find_all_concatenated_words_in_a_dict(&words);
        let ret = ret.into_iter().collect::<HashSet<String>>();
        assert_eq!(output, ret);
    }
}
