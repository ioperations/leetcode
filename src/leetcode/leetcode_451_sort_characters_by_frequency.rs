// Given a string s, sort it in decreasing order based on the frequency of the characters.
// The frequency of a character is the number of times it appears in the string.
// Return the sorted string. If there are multiple answers, return any of them.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn frequency_sort(s: &str) -> String {
        let mut vec = Vec::with_capacity(26 + 26 + 10 + 100);

        (0..(26 + 26 + 10 + 100)).all(|i| {
            vec.push((i, 0));
            true
        });

        for ele in s.as_bytes() {
            vec[(*ele - b'0') as usize].1 += 1;
        }

        vec.sort_by(|a, b| b.1.partial_cmp(&a.1).unwrap());

        let mut s = String::new();

        for (i, j) in vec {
            if j > 0 {
                s.push_str(String::from((i + b'0') as char).repeat(j).as_str());
            }
        }

        s
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::*;

    #[test]
    fn case1_test() {
        let s = "tree";
        let output = [String::from("eert"), String::from("eetr")]
            .iter()
            .cloned()
            .collect::<HashSet<String>>();
        /*
         * Explanation: 'e' appears twice while 'r' and 't' both appear once.
         * So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
         */
        let ret = Solution::frequency_sort(s);
        assert!(output.contains(&ret));
    }

    #[test]
    fn case2_test() {
        let s = "cccaaa";
        let output = ["aaaccc".into(), "cccaaa".into()]
            .iter()
            .cloned()
            .collect::<HashSet<String>>();
        /*
         * Both 'c' and 'a' appear three times, so both "cccaaa" and "aaaccc" are valid answers.
         * Note that "cacaca" is incorrect, as the same characters must be together.
         */
        let ret = Solution::frequency_sort(s);
        assert!(output.contains(&ret));
    }

    #[test]
    fn case3_test() {
        let s = "Aabb";
        let output = ["bbAa".into(), "bbaA".into()]
            .iter()
            .cloned()
            .collect::<HashSet<String>>();
        /*
         * "bbaA" is also a valid answer, but "Aabb" is incorrect.
         * Note that 'A' and 'a' are treated as two different characters.
         */
        let ret = Solution::frequency_sort(s);
        assert!(output.contains(&ret));
    }
}
