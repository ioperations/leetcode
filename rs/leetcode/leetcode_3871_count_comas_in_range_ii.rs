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
// 1 <= n <= 1015

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_commas(n: i64) -> i64 {
        // Count the numbers in each comma group (1-3 digits, 4-6 digits, 7-9
        // digits, ...) and multiply by how many commas each number in
        // that group has.

        let mut p: i64 = 1000;
        let mut res: i64 = 0;
        while p <= n {
            res += n - p + 1;
            p *= 1000;
        }
        res
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
