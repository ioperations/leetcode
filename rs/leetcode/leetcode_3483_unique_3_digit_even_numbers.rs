// You are given an array of digits called digits. Your task is to determine the
// number of distinct three-digit even numbers that can be formed using these
// digits.
//
// Note: Each copy of a digit can only be used once per number, and there may
// not be leading zeros.
//
// 3 <= digits.length <= 10
// 0 <= digits[i] <= 9

use itertools::Itertools;

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn total_numbers(digits: Vec<i32>) -> i32 {
        // Use brute force to try all possibilities
        let mut digits = digits;
        digits.sort();

        let len = digits.len();
        let ret = digits.iter().permutations(len);

        let mut hs = std::collections::HashSet::new();
        for i in ret {
            if *i[0] == 0 {
                continue;
            }

            if **i.last().unwrap() % 2 == 1 {
                continue;
            }

            let v =
                i.iter().fold(String::new(), |acc, &&v| format!("{v}{acc}"));

            hs.insert(v);
        }

        hs.len() as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let digits = vec![1, 2, 3, 4];
        let output = 12;
        let ret = Solution::total_numbers(digits);
        assert_eq!(output, ret);
        // The 12 distinct 3-digit even numbers that can be formed are 124, 132,
        // 134, 142, 214, 234, 312, 314, 324, 342, 412, and 432. Note that 222
        // cannot be formed because there is only 1 copy of the digit 2.
    }

    #[test]
    fn case2_test() {
        let digits = vec![0, 2, 2];
        let output = 2;
        let ret = Solution::total_numbers(digits);
        assert_eq!(output, ret);
        // Explanation: The only 3-digit even numbers that can be formed are 202
        // and 220. Note that the digit 2 can be used twice because it appears
        // twice in the array.
    }

    #[test]
    fn case3_test() {
        let digits = vec![6, 6, 6];
        let output = 1;
        let ret = Solution::total_numbers(digits);
        assert_eq!(output, ret);
        // Only 666 can be formed.
    }

    #[test]
    fn case4_test() {
        let digits = vec![1, 3, 5];
        let output = 0;
        let ret = Solution::total_numbers(digits);
        assert_eq!(output, ret);
        // No even 3-digit numbers can be formed.
    }
}
