// Given a m x n grid filled with non-negative numbers, find a path from top
// left to bottom right, which minimizes the sum of all numbers along its path.
//
// Note: You can only move either down or right at any point in time.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn min_path_sum(grid: &[Vec<i32>]) -> i32 {
        use std::collections::HashMap;
        fn dp(
            grid: &[Vec<i32>],
            from: (usize, usize),
            cache: &mut HashMap<(usize, usize), i32>,
        ) -> i32 {
            let m = grid.len() - 1;
            let n = grid[0].len() - 1;
            if from == (m, n) {
                return grid[m][n];
            }

            if let Some(&v) = cache.get(&from) {
                return v;
            }
            let (x, y) = from;

            let val = if x >= m {
                grid[x][y] + dp(grid, (x, y + 1), cache)
            } else if y >= n {
                grid[x][y] + dp(grid, (x + 1, y), cache)
            } else {
                grid[x][y]
                    + dp(grid, (x + 1, y), cache).min(dp(
                        grid,
                        (x, y + 1),
                        cache,
                    ))
            };

            cache.insert((x, y), val);
            val
        }

        let mut cache = HashMap::new();
        dp(grid, (0, 0), &mut cache)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = [vec![1, 3, 1], vec![1, 5, 1], vec![4, 2, 1]];
        let output = 7;
        let ret = Solution::min_path_sum(&grid);
        assert_eq!(ret, output);
        // Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
    }

    #[test]
    fn case2_test() {
        let grid = [vec![1, 2, 3], vec![4, 5, 6]];
        let output = 12;
        let ret = Solution::min_path_sum(&grid);
        assert_eq!(ret, output);
    }
}
