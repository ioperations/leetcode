// Given an n x n array of integers matrix, return the minimum sum of any
// falling path through matrix.
// A falling path starts at any element in the first row and chooses
// the element in the next row that is either directly below or
// diagonally left/right. Specifically, the next element from position (row,
// col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn min_falling_path_sum(matrix: Vec<Vec<i32>>) -> i32 {
        // n == matrix.length == matrix[i].length
        // 1 <= n <= 100
        // -100 <= matrix[i][j] <= -100
        let len = matrix.len();
        let mut dp = matrix;
        let v = len - 1;

        for i in (0..(len - 1)).rev() {
            for j in (0..len) {
                if j == 0 {
                    dp[i][j] += dp[i + 1][j].min(dp[i + 1][j + 1]);
                } else if j == v {
                    dp[i][j] += dp[i + 1][j].min(dp[i + 1][j - 1]);
                } else {
                    dp[i][j] += dp[i + 1][j]
                        .min(dp[i + 1][j - 1])
                        .min(dp[i + 1][j + 1]);
                }
            }
        }
        *dp[0].iter().min().unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let matrix = vec![vec![2, 1, 3], vec![6, 5, 4], vec![7, 8, 9]];
        let output = 13;
        // Explanation: There are two falling paths with a minimum sum as shown.
        let ret = Solution::min_falling_path_sum(matrix);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let matrix = vec![vec![-19, 57], vec![-40, -5]];
        let output = -59;
        // The falling path with a minimum sum is shown.
        let ret = Solution::min_falling_path_sum(matrix);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let matrix = vec![vec![-19]];
        let output = -19;
        // The falling path with a minimum sum is shown.
        let ret = Solution::min_falling_path_sum(matrix);
        assert_eq!(ret, output);
    }
}
