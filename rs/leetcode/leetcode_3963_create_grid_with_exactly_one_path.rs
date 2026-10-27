// You are given two integers m and n, representing the number of rows and
// columns of a grid.
//
// Construct any m x n grid consisting only of the characters '.' and '#',
// where:
//
// '.' represents a free cell.
// '#' represents an obstacle cell.
// A valid path is a sequence of free cells that:
//
// Starts at the top-left cell (0, 0).
// Ends at the bottom-right cell (m - 1, n - 1).
// Moves only:
// Right, from (i, j) to (i, j + 1), or
// Down, from (i, j) to (i + 1, j).
// Return any grid such that there is exactly one valid path from the top-left
// cell to the bottom-right cell.
//
// 1 <= m, n <= 25

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn create_grid(m: i32, n: i32) -> Vec<String> {
        let m = m as usize;
        let n = n as usize;
        let mut grid = Vec::with_capacity(m);

        grid.push(".".repeat(n));
        let row = "#".repeat(n - 1) + ".";
        for _ in 1..m {
            grid.push(row.clone());
        }

        grid
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let m = 2;
        let n = 3;

        let output = ["...", "##."]
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<_>>();

        let ret = Solution::create_grid(m, n);
        assert_eq!(output, ret);
        // The only valid path is: (0,0) → (0,1) → (1,1) → (1,2)
    }

    #[test]
    fn case2_test() {
        let m = 3;
        let n = 3;
        let output = ["...", "##.", "##."]
            .iter()
            .map(|v| v.to_string())
            .collect::<Vec<_>>();
        let ret = Solution::create_grid(m, n);
        assert_eq!(output, ret);
        // The only valid path is: (0,0) → (0,1) → (1,1) → (1,2) → (2,2)
    }

    #[test]
    fn case3_test() {
        let m = 1;
        let n = 4;
        let output = ["...."].iter().map(|v| v.to_string()).collect::<Vec<_>>();
        let ret = Solution::create_grid(m, n);
        assert_eq!(output, ret);
        // The only valid path is: (0,0) → (0,1) → (0,2) → (0,3)
    }
}
