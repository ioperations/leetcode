// Given a list of words, list of  single letters (might be repeating) and score
// of every character. Return the maximum score of any valid set of words formed
// by using the given letters (words[i] cannot be used two or more times). It is
// not necessary to use all characters in letters and each letter can only be
// used once. Score of letters 'a', 'b', 'c', ... ,'z' is given by score[0],
// score[1], ... , score[25] respectively.

#![allow(unused)]
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn max_score_words(
        words: &[String],
        letters: Vec<char>,
        score: &[i32],
    ) -> i32 {
        // TODO: there being much room to optimize,
        // such as hashbuilder process

        use std::collections::HashMap;

        fn check_if_can_take(str: &str, hashm: &HashMap<char, usize>) -> bool {
            let mut hm: HashMap<char, usize> = HashMap::default();
            {
                for i in str.bytes() {
                    hm.entry(i as char).and_modify(|x| *x += 1).or_insert(1);
                }
            };

            for (k, v) in hm {
                if let Some(vv) = hashm.get(&k) {
                    if *vv >= v {
                        continue;
                    }
                    return false;
                }
                return false;
            }

            true
        };

        fn take(str: &str, hashm: &mut HashMap<char, usize>) -> bool {
            let mut hm: HashMap<char, usize> = HashMap::default();
            {
                for i in str.bytes() {
                    hm.entry(i as char).and_modify(|x| *x += 1).or_insert(1);
                }
            };

            for (k, v) in hm {
                hashm.entry(k).and_modify(|counter| *counter -= v);
            }
            true
        };

        fn calculate_value(str: &str, vec: &[i32]) -> i32 {
            str.bytes()
                .scan((0), |state, x| {
                    *state += vec[(x - b'a') as usize];
                    Some(*state)
                })
                .last()
                .unwrap()
        };

        fn myimpl(
            i: usize,
            words: &[String],
            mut visibility: &mut Vec<bool>,
            letters: &mut HashMap<char, usize>,
            score: &[i32],
            before: i32,
        ) -> i32 {
            let len = words.len();
            if i >= len {
                return before;
            }

            if visibility[i] && check_if_can_take(&words[i], letters) {
                // case 1. take the str
                let leters_bk = letters.clone();
                take(&words[i], letters);
                visibility[i] = false;

                let va = calculate_value(&words[i], score);
                let case1 = myimpl(
                    i + 1,
                    words,
                    visibility,
                    letters,
                    score,
                    before + va,
                );
                visibility[i] = true;
                *letters = leters_bk;
                // case 2. do not take the str

                let case2 =
                    myimpl(i + 1, words, visibility, letters, score, before);
                return case1.max(case2);
            }
            // do not take the str
            myimpl(i + 1, words, visibility, letters, score, before)
        };

        let mut lh: HashMap<char, usize> = HashMap::default();
        {
            for i in letters {
                lh.entry(i).and_modify(|x| *x += 1).or_insert(1);
            }
        };
        let len = words.len();
        let mut visibility = vec![true; len];
        myimpl(0, words, &mut visibility, &mut lh, score, 0)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let words: Vec<String> = ["dog", "cat", "dad", "good"]
            .iter()
            .map(std::string::ToString::to_string)
            .collect();
        let letters: Vec<_> = ["a", "a", "c", "d", "d", "d", "g", "o", "o"]
            .iter()
            .map(|s| s.bytes().next().unwrap() as char)
            .collect();
        let score = [
            1, 0, 9, 5, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0,
        ];
        let output = 23;
        // Explanation:
        // Score  a=1, c=9, d=5, g=3, o=2
        // Given letters, we can form the words "dad" (5+1+5) and "good"
        // (3+2+2+5) with a score of 23. Words "dad" and "dog" only get
        // a score of 21.
        let ret = Solution::max_score_words(&words, letters, &score);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let words: Vec<String> = ["xxxz", "ax", "bx", "cx"]
            .iter()
            .map(std::string::ToString::to_string)
            .collect();
        let letters: Vec<_> = ["z", "a", "b", "c", "x", "x", "x"]
            .iter()
            .map(|s| s.bytes().next().unwrap() as char)
            .collect();
        let score = [
            4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 5, 0, 10,
        ];
        let output = 27;
        // Explanation:
        // Score  a=4, b=4, c=4, x=5, z=10
        // Given letters, we can form the words "ax" (4+5), "bx" (4+5) and "cx"
        // (4+5) with a score of 27. Word "xxxz" only get a score of 25.
        let ret = Solution::max_score_words(&words, letters, &score);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let words: Vec<_> = ["leetcode"]
            .iter()
            .map(std::string::ToString::to_string)
            .collect();
        let letters: Vec<_> = ["l", "e", "t", "c", "o", "d"]
            .iter()
            .map(|s| s.bytes().next().unwrap() as char)
            .collect();
        let score = [
            0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
            0, 0, 0, 0,
        ];
        let output = 0;
        // Explanation:
        // Letter "e" can only be used once.
        let ret = Solution::max_score_words(&words, letters, &score);
        assert_eq!(ret, output);
    }
}
