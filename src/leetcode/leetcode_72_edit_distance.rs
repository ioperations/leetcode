// Given two strings word1 and word2, return the minimum number of operations
// required to convert word1 to word2.
//
// You have the following three operations permitted on a word:
// Insert a character
// Delete a character
// Replace a character

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_distance(word1: &str, word2: &str) -> i32 {
        // 0 <= word1.length, word2.length <= 500
        // word1 and word2 consist of lowercase English letters.
        use std::collections::HashMap;
        fn my_impl(
            w1: &[u8],
            w2: &[u8],
            cache: &mut HashMap<(Vec<u8>, Vec<u8>), i32>,
        ) -> i32 {
            // pass
            if w1.is_empty() {
                return w2.len() as i32;
            }
            if w2.is_empty() {
                return w1.len() as i32;
            }

            let key = (w1.to_vec(), w2.to_vec());
            if let Some(&v) = cache.get(&key) {
                return v;
            }

            let res = if w1[0] == w2[0] {
                my_impl(&w1[1..], &w2[1..], cache)
            } else {
                1 + my_impl(w1, &w2[1..], cache)
                    .min(my_impl(&w1[1..], w2, cache))
                    .min(my_impl(&w1[1..], &w2[1..], cache))
            };
            cache.entry(key).or_insert(res);
            res
        };

        let mut cache = HashMap::new();

        my_impl(word1.as_bytes(), word2.as_bytes(), &mut cache)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let word1 = "horse";
        let word2 = "ros";
        let output = 3;
        // Explanation:
        // horse -> rorse (replace 'h' with 'r')
        // rorse -> rose (remove 'r')
        // rose -> ros (remove 'e')
        let ret = Solution::min_distance(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let word1 = "intention";
        let word2 = "execution";
        let output = 5;
        // Explanation:
        // intention -> inention (remove 't')
        // inention -> enention (replace 'i' with 'e')
        // enention -> exention (replace 'n' with 'x')
        // exention -> exection (replace 'n' with 'c')
        // exection -> execution (insert 'u')
        let ret = Solution::min_distance(word1, word2);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let word1 = "initrophenylhydrazine";
        let word2 = "acetylphenylhydrazine";
        let output = 5;
        // Explanation:
        // intention -> inention (remove 't')
        // inention -> enention (replace 'i' with 'e')
        // enention -> exention (replace 'n' with 'x')
        // exention -> exection (replace 'n' with 'c')
        // exection -> execution (insert 'u')
        let ret = Solution::min_distance(word1, word2);
        assert_eq!(ret, output);
    }
}
