/*
We define the usage of capitals in a word to be right when one of the following cases holds:
All letters in this word are capitals, like "USA".
All letters in this word are not capitals, like "leetcode".
Only the first letter in this word is capital, like "Google".
Given a string word, return true if the usage of capitals in it is right.*/

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn detect_capital_use(word: String) -> bool {
        fn all_upper<const T: bool>(words: &[char]) -> bool {
            if T {
                words.iter().all(|&c| ('a'..='z').contains(&c))
            } else {
                words.iter().all(|&c| ('A'..='Z').contains(&c))
            }
        }
        if word.is_empty() || word.len() == 1 {
            return true;
        }

        let word = word.chars().collect::<Vec<char>>();
        if ('a'..='z').contains(&word[0]) {
            all_upper::<true>(&word[1..])
        } else {
            all_upper::<true>(&word[1..]) || all_upper::<false>(&word[1..])
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let word = "USA";
        let output = true;
        let ret = Solution::detect_capital_use(word.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let word = "FlaG";
        let output = false;
        let ret = Solution::detect_capital_use(word.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let word = "mL";
        let output = false;
        let ret = Solution::detect_capital_use(word.into());
        assert_eq!(ret, output);
    }
}
