// Given a rectangular pizza represented as a rows x cols matrix containing the
// following characters: 'A' (an apple) and '.' (empty cell) and given the
// integer k. You have to cut the pizza into k pieces using k-1 cuts.
//
// For each cut you choose the direction: vertical or horizontal, then you
// choose a cut position at the cell boundary and cut the pizza into two pieces.
// If you cut the pizza vertically, give the left part of the pizza to a person.
// If you cut the pizza horizontally, give the upper part of the pizza to a
// person. Give the last piece of pizza to the last person.
//
// Return the number of ways of cutting the pizza such that each piece contains
// at least one apple. Since the answer can be a huge number, return this modulo
// 10^9 + 7.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    #[allow(clippy::needless_pass_by_value)]
    pub fn ways(pizza: Vec<String>, k: i32) -> i32 {
        // 1 <= rows, cols <= 50
        // rows == pizza.length
        // cols == pizza[i].length
        // 1 <= k <= 10
        // pizza consists of characters 'A' and '.' only.
        fn my_impl(pizza: &[String], k: i32) -> i32 {
            let h = pizza.len();
            let w = pizza[0].len();

            // count[i][j] means the number of apples in a slice
            // which top-left cell is pizza[i][j] and
            // bottom-right corner is the bottom-right corner of the whole
            // pizza.
            let mut count: Vec<Vec<i32>> = pizza
                .iter()
                .map(|s| s.chars().map(|ch| (ch == 'A').into()).collect())
                .collect();
            for i in (0..h - 1).rev() {
                count[i][w - 1] += count[i + 1][w - 1];
            }
            for j in (0..w - 1).rev() {
                count[h - 1][j] += count[h - 1][j + 1];
            }
            for i in (0..h - 1).rev() {
                for j in (0..w - 1).rev() {
                    count[i][j] +=
                        count[i][j + 1] + count[i + 1][j] - count[i + 1][j + 1];
                }
            }
            let mut dp: Vec<Vec<i32>> = count
                .iter()
                .map(|v| v.iter().map(|&x| x.signum()).collect())
                .collect();

            let large = 1_000_000_007;
            for _ in 1..k {
                for i in 0..h {
                    for j in 0..w {
                        dp[i][j] = 0;
                        for i2 in i + 1..h {
                            if count[i][j] > count[i2][j] && count[i2][j] != 0 {
                                dp[i][j] += dp[i2][j];
                                dp[i][j] %= large;
                            }
                        }
                        for j2 in j + 1..w {
                            if count[i][j] > count[i][j2] && count[i][j2] != 0 {
                                dp[i][j] += dp[i][j2];
                                dp[i][j] %= large;
                            }
                        }
                    }
                }
            }
            dp[0][0]
        }

        my_impl(&pizza, k)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let pizza: Vec<_> =
            ["A..", "AAA", "..."].iter().map(|&a| a.into()).collect();
        let k = 3;
        let output = 3;
        let ret = Solution::ways(pizza, k);
        assert_eq!(ret, output);
        // Explanation: The figure above shows the three ways to cut the pizza.
        // Note that pieces must contain at least one apple.
    }

    #[test]
    fn case2_test() {
        let pizza: Vec<_> =
            ["A..", "AA.", "..."].iter().map(|&a| a.into()).collect();
        let k = 3;
        let output = 1;
        let ret = Solution::ways(pizza, k);
        assert_eq!(ret, output);
        // Explanation: The figure above shows the three ways to cut the pizza.
        // Note that pieces must contain at least one apple.
    }

    #[test]
    fn case3_test() {
        let pizza: Vec<_> =
            ["A..", "A..", "..."].iter().map(|&a| a.into()).collect();
        let k = 1;
        let output = 1;
        let ret = Solution::ways(pizza, k);
        assert_eq!(ret, output);
    }
}
