// You are given an m x n matrix grid and a positive integer k. An island is a
// group of positive integers (representing land) that are 4-directionally
// connected (horizontally or vertically).
//
// The total value of an island is the sum of the values of all cells in the
// island.
//
// Return the number of islands with a total value divisible by k.
//
// m == grid.length
// n == grid[i].length
// 1 <= m, n <= 1000
// 1 <= m * n <= 105
// 0 <= grid[i][j] <= 106
// 1 <= k <= 106

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_islands(mut grid: Vec<Vec<i32>>, k: i32) -> i32 {
        let row = grid.len();
        let column = grid[0].len();
        let mut ret = 0;
        for i in 0..row {
            for j in 0..column {
                if grid[i][j] > 0 {
                    let v = Self::q(&mut grid, i, j);
                    if v % (k as i64) == 0 {
                        ret += 1;
                    }
                }
            }
        }
        ret
    }

    fn q(grid: &mut Vec<Vec<i32>>, i: usize, j: usize) -> i64 {
        let mut sum = grid[i][j] as i64;
        if sum == 0 {
            return 0;
        }

        grid[i][j] = 0;
        let row = grid.len();
        let column = grid[0].len();

        if i + 1 < row {
            sum += Self::q(grid, i + 1, j);
        }

        if j + 1 < column {
            sum += Self::q(grid, i, j + 1);
        }

        if i >= 1 {
            sum += Self::q(grid, i - 1, j);
        }

        if j >= 1 {
            sum += Self::q(grid, i, j - 1);
        }
        sum
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = [
            [0, 2, 1, 0, 0],
            [0, 5, 0, 0, 5],
            [0, 0, 1, 0, 0],
            [0, 1, 4, 7, 0],
            [0, 2, 0, 0, 8],
        ]
        .iter()
        .map(|v| v.to_vec())
        .collect::<Vec<_>>();
        let k = 5;
        let ret = Solution::count_islands(grid, k);
        let output = 2;
        assert_eq!(output, ret);
        // The grid contains four islands. The islands highlighted in blue have
        // a total value that is divisible by 5, while the islands highlighted
        // in red do not.
    }

    #[test]
    fn case2_test() {
        let grid = [[3, 0, 3, 0], [0, 3, 0, 3], [3, 0, 3, 0]]
            .iter()
            .map(|v| v.to_vec())
            .collect::<Vec<_>>();
        let k = 3;
        let ret = Solution::count_islands(grid, k);
        let output = 6;
        assert_eq!(output, ret);
        // The grid contains six islands, each with a total value that is
        // divisible by 3.
    }
}
