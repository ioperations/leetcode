// You are given an m x n integer array grid where grid[i][j] could be:
// 1 representing the starting square. There is exactly one starting square.
// 2 representing the ending square. There is exactly one ending square.
// 0 representing empty squares we can walk over.
// -1 representing obstacles that we cannot walk over.
//
// Return the number of 4-directional walks from the starting square to the ending square,
// that walk over every non-obstacle square exactly once.

use std::collections::HashSet;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn unique_paths_iii(grid: &[Vec<i32>]) -> i32 {
        let m = grid.len();
        let n = grid[0].len();
        let cur = (|| {
            for (i, iter) in grid.iter().enumerate().take(m) {
                for (j, &v) in iter.iter().enumerate().take(n) {
                    if v == 1 {
                        return (i, j);
                    }
                }
            }
            panic!();
        })();
        let target = {
            let mut res = 0;
            for iter in grid.iter().take(m) {
                for &v in iter.iter().take(n) {
                    if v == 0 {
                        res += 1;
                    }
                }
            }
            res + 1
        };
        let mut route = HashSet::new();
        Self::dfs(grid, (m - 1, n - 1), cur, target, &mut route)
    }

    #[allow(unused)]
    fn dfs(
        grid: &[Vec<i32>],
        bounds: (usize, usize),
        cur: (usize, usize),
        target: usize,
        route: &mut HashSet<(usize, usize)>,
    ) -> i32 {
        let (m, n) = bounds;
        let (i, j) = cur;

        if grid[i][j] == 2 && route.len() == target {
            return 1;
        }
        route.insert(cur);
        let mut try_dfs = |pos: (usize, usize)| {
            if grid[i][j] == -1 || route.contains(&pos) {
                return 0;
            };
            Self::dfs(grid, bounds, pos, target, route)
        };
        let mut res = 0;
        if i > 0 {
            res += try_dfs((i - 1, j));
        }
        if i < m {
            res += try_dfs((i + 1, j));
        }
        if j > 0 {
            res += try_dfs((i, j - 1));
        }
        if j < n {
            res += try_dfs((i, j + 1));
        }
        route.remove(&cur);
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = vec![vec![1, 0, 0, 0], vec![0, 0, 0, 0], vec![0, 0, 2, -1]];
        let output = 2;
        // Explanation: We have the following two paths:
        // 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
        // 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
        let ret = Solution::unique_paths_iii(&grid);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let grid = vec![vec![1, 0, 0, 0], vec![0, 0, 0, 0], vec![0, 0, 0, 2]];
        let output = 4;
        //          We have the following four paths:
        // 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2),(2,3)
        // 2. (0,0),(0,1),(1,1),(1,0),(2,0),(2,1),(2,2),(1,2),(0,2),(0,3),(1,3),(2,3)
        // 3. (0,0),(1,0),(2,0),(2,1),(2,2),(1,2),(1,1),(0,1),(0,2),(0,3),(1,3),(2,3)
        // 4. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2),(2,3)
        let ret = Solution::unique_paths_iii(&grid);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let grid = vec![vec![0, 1], vec![2, 0]];
        let output = 0;
        // There is no path that walks over every empty square exactly once.
        // Note that the starting and ending square can be anywhere in the grid.
        let ret = Solution::unique_paths_iii(&grid);
        assert_eq!(ret, output);
    }
}
