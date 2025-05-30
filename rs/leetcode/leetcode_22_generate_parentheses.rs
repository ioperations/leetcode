// Given n pairs of parentheses, write a function to generate all combinations
// of well-formed parentheses.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn generate_parenthesis(n: i32) -> Vec<String> {
        fn back_track(s: String, open: i32, close: i32) -> Vec<String> {
            let mut res = vec![];
            if open == 0 && close == 0 {
                return vec![s];
            }
            if open > 0 {
                res.append(&mut back_track(
                    s.clone() + "(",
                    open - 1,
                    close + 1,
                ));
            }
            if close > 0 {
                res.append(&mut back_track(s + ")", open, close - 1));
            }
            res
        }
        back_track(String::new(), n, 0)
    }
}

#[cfg(test)]
mod tests {
    use std::collections::HashSet;

    use super::*;

    pub trait ToHashSet {
        fn into_hash_set(self) -> HashSet<String>;
    }

    impl ToHashSet for Vec<String>
    {
        fn into_hash_set(self) -> HashSet<String> {
            self.into_iter().collect()
        }
    }

    #[test]
    fn case1_test() {
        let n = 3;
        let ret = Solution::generate_parenthesis(n);
        let ret = ret.into_hash_set();
        let expect: Vec<String> = vec![
            "((()))".into(),
            "(()())".into(),
            "(())()".into(),
            "()(())".into(),
            "()()()".into(),
        ];
        let expect = expect.into_hash_set();

        assert_eq!(ret, expect);
    }

    #[test]
    fn case2_test() {
        let n = 1;
        let ret = Solution::generate_parenthesis(n);
        let ret = ret.into_hash_set();
        let expect: Vec<String> = vec!["()".into()];
        let expect = expect.into_hash_set();

        assert_eq!(ret, expect);
    }
}
