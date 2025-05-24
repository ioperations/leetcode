#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn find_words_containing(words: &[&str], x: char) -> Vec<i32> {
        fn find(str: &str, x: char) -> bool {
            for i in str.chars() {
                if x == i {
                    return true;
                }
            }
            false
        }

        let mut ret = vec![];
        for (index, i) in words.iter().enumerate() {
            if find(i, x) {
                ret.push(index.try_into().unwrap());
            }
        }
        ret
    }
}

#[cfg(test)]
mod test {
    use super::Solution;

    #[test]
    fn test_1() {
        let words = ["leet", "code"];
        let x = 'e';
        let output = [0, 1];
        let ret = Solution::find_words_containing(words.iter().as_slice(), x);
        assert_eq!(ret, output);
    }

    #[test]
    fn test_2() {
        let words = ["abc", "bcd", "aaaa", "cbc"];
        let x = 'a';
        let output = [0, 2];
        let ret = Solution::find_words_containing(words.iter().as_slice(), x);
        assert_eq!(ret, output);
    }

    #[test]
    fn test_3() {
        let words = ["abc", "bcd", "aaaa", "cbc"];
        let x = 'z';
        let output = vec![];
        let ret = Solution::find_words_containing(words.iter().as_slice(), x);
        assert_eq!(ret, output);
    }
}
