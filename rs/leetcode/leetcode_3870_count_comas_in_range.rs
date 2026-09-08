// You are given an integer n.
//
// Return the total number of commas used when writing all integers from [1, n]
// (inclusive) in standard number formatting.
//
// In standard formatting:
//
// A comma is inserted after every three digits from the right.
// Numbers with fewer than 4 digits contain no commas.
//
// 1 <= n <= 105

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_commas(n: i32) -> i32 {
        if n >= 1000 {
            return n - 999;
        }

        0
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 1002;
        let output = 3;
        let ret = Solution::count_commas(n);
        assert_eq!(output, ret);
        // The numbers "1,000", "1,001", and "1,002" each contain one comma,
        // giving a total of 3.
    }

    #[test]
    fn case2_test() {
        let n = 998;
        let output = 0;
        let ret = Solution::count_commas(n);
        assert_eq!(output, ret);
        // All numbers from 1 to 998 have fewer than four digits. Therefore, no
        // commas are used.
    }
}
