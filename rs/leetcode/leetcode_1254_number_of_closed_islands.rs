// Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal
// 4-directionally connected group of 0s and a closed island is an island
// totally (all left, top, right, bottom) surrounded by 1s.
//
// Return the number of closed islands.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn closed_island(grid: Vec<Vec<i32>>) -> i32 {
        // 1 <= grid.length, grid[0].length <= 100
        // 0 <= grid[i][j] <=1
        //
        // NOTE:
        // do dfs traverse twice.
        // first time, we mark 0 that can't make an island (connect to the
        // boarder). second time, we check the number of islands.
        let mut grid = grid;
        let (m, n) = (grid.len(), grid[0].len());
        for i in 0..m {
            for j in 0..n {
                if i == 0 || j == 0 || i == m - 1 || j == n - 1 {
                    Self::dfs(&mut grid, i, j);
                }
            }
        }

        let mut count = 0;
        for i in 0..m {
            for j in 0..n {
                if grid[i][j] == 0 {
                    count += 1;
                    Self::dfs(&mut grid, i, j);
                }
            }
        }
        count
    }

    fn dfs(grid: &mut Vec<Vec<i32>>, i: usize, j: usize) {
        if i >= grid.len() || j >= grid[0].len() || grid[i][j] == 1 {
            return;
        }
        grid[i][j] = 1;
        Self::dfs(grid, i + 1, j);
        if i >= 1 {
            Self::dfs(grid, i - 1, j);
        }
        Self::dfs(grid, i, j + 1);
        if j >= 1 {
            Self::dfs(grid, i, j - 1);
        }
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = [
            vec![1, 1, 1, 1, 1, 1, 1, 0],
            vec![1, 0, 0, 0, 0, 1, 1, 0],
            vec![1, 0, 1, 0, 1, 1, 1, 0],
            vec![1, 0, 0, 0, 0, 1, 0, 1],
            vec![1, 1, 1, 1, 1, 1, 1, 0],
        ];
        let output = 2;
        let ret = Solution::closed_island(grid.into());
        assert_eq!(ret, output);
        // Explanation:
        // Islands in gray are closed because they are completely surrounded by
        // water (group of 1s).
    }

    #[test]
    fn case2_test() {
        let grid = [
            vec![0, 0, 1, 0, 0],
            vec![0, 1, 0, 1, 0],
            vec![0, 1, 1, 1, 0],
        ];
        let output = 1;
        let ret = Solution::closed_island(grid.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let grid = [
            vec![1, 1, 1, 1, 1, 1, 1],
            vec![1, 0, 0, 0, 0, 0, 1],
            vec![1, 0, 1, 1, 1, 0, 1],
            vec![1, 0, 1, 0, 1, 0, 1],
            vec![1, 0, 1, 1, 1, 0, 1],
            vec![1, 0, 0, 0, 0, 0, 1],
            vec![1, 1, 1, 1, 1, 1, 1],
        ];
        let output = 2;
        let ret = Solution::closed_island(grid.into());
        assert_eq!(ret, output);
    }
}
