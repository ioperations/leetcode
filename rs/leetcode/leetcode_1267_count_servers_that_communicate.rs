// You are given a map of a server center, represented as a m * n integer matrix
// grid, where 1 means that on that cell there is a server and 0 means that it
// is no server. Two servers are said to communicate if they are on the same row
// or on the same column.
//
// Return the number of servers that communicate with any other server.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn count_servers(grid: &[Vec<i32>]) -> i32 {
        // m == grid.length
        // n == grid[i].length
        // 1 <= m <= 250
        // 1 <= n <= 250
        // grid[i][j] == 0 or 1
        let row_len = grid.len();
        let column_len = grid[0].len();

        let mut row = vec![0; row_len]; // 这一行有多少计算机
        let mut column = vec![0; column_len]; // 这一列有多少计算机
        for i in 0..row_len {
            for j in 0..column_len {
                if grid[i][j] == 1 {
                    row[i] += 1;
                    column[j] += 1;
                }
            }
        }

        let mut ret = 0;

        for i in 0..row_len {
            for j in 0..column_len {
                if grid[i][j] == 1 {
                    if row[i] == 1 && column[j] == 1 {
                    } else {
                        ret += 1;
                    }
                }
            }
        }
        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = [[1, 0].to_vec(), [0, 1].to_vec()];
        let output = 0;
        let ret = Solution::count_servers(&grid);
        assert_eq!(output, ret);
        // Explanation: No servers can communicate with others.
    }

    #[test]
    fn case2_test() {
        let grid = [[1, 0].to_vec(), [1, 1].to_vec()];
        let output = 3;
        let ret = Solution::count_servers(&grid);
        assert_eq!(output, ret);
        // Explanation: All three servers can communicate with at least one
        // other server.
    }

    #[test]
    fn case3_test() {
        let grid = [
            [1, 1, 0, 0].to_vec(),
            [0, 0, 1, 0].to_vec(),
            [0, 0, 1, 0].to_vec(),
            [0, 0, 0, 1].to_vec(),
        ];
        let output = 4;
        let ret = Solution::count_servers(&grid);
        assert_eq!(output, ret);
        // Explanation: The two servers in the first row can communicate with
        // each other. The two servers in the third column can
        // communicate with each other. The server at right
        // bottom corner can't communicate with any other server.
    }

    #[test]
    fn case4_test() {
        let grid = [
            [1, 0, 0, 1, 0].to_vec(),
            [0, 0, 0, 0, 0].to_vec(),
            [0, 0, 0, 1, 0].to_vec(),
        ];
        let output = 3;
        let ret = Solution::count_servers(&grid);
        assert_eq!(output, ret);
        // Explanation: The two servers in the first row can communicate with
        // each other. The two servers in the third column can
        // communicate with each other. The server at right
        // bottom corner can't communicate with any other server.
    }
}
