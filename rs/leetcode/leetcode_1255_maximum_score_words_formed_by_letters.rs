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
        words: Vec<String>,
        letters: Vec<char>,
        score: &[i32],
    ) -> i32 {
        let n = words.len();
        let word_counts: Vec<[i32; 26]> = words
            .iter()
            .map(|w| {
                let mut cnt = [0; 26];
                for &b in w.as_bytes() {
                    cnt[(b - b'a') as usize] += 1;
                }
                cnt
            })
            .collect();

        let word_scores: Vec<i32> = words
            .iter()
            .map(|w| w.bytes().map(|b| score[(b - b'a') as usize]).sum())
            .collect();

        let mut letter_counts = [0; 26];
        for &c in &letters {
            letter_counts[(c as u8 - b'a') as usize] += 1;
        }

        fn backtrack(
            idx: usize,
            word_counts: &[[i32; 26]],
            word_scores: &[i32],
            letter_counts: &mut [i32; 26],
            current_score: i32,
        ) -> i32 {
            if idx == word_counts.len() {
                return current_score;
            }

            let mut can_take = true;
            for (j, &cnt) in word_counts[idx].iter().enumerate() {
                if cnt > 0 && letter_counts[j] < cnt {
                    can_take = false;
                    break;
                }
            }

            let skip = backtrack(idx + 1, word_counts, word_scores, letter_counts, current_score);

            if can_take {
                for (j, &cnt) in word_counts[idx].iter().enumerate() {
                    letter_counts[j] -= cnt;
                }
                let take = backtrack(idx + 1, word_counts, word_scores, letter_counts, current_score + word_scores[idx]);
                for (j, &cnt) in word_counts[idx].iter().enumerate() {
                    letter_counts[j] += cnt;
                }
                return take.max(skip);
            }

            skip
        }

        backtrack(0, &word_counts, &word_scores, &mut letter_counts, 0)
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
        let ret = Solution::max_score_words(words, letters, &score);
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
        let ret = Solution::max_score_words(words, letters, &score);
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
        let ret = Solution::max_score_words(words, letters, &score);
        assert_eq!(ret, output);
    }
}
