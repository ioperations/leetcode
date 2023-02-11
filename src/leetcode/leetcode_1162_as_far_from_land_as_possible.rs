// Given an n x n grid containing only values 0 and 1, where 0 represents water
// and 1 represents land, find a water cell such that its distance to the
// nearest land cell is maximized, and return the distance. If no land or water
// exists in the grid, return -1. The distance used in this problem is the
// Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is
// |x0 - x1| + |y0 - y1|.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_distance(grid: Vec<Vec<i32>>) -> i32 {
        {
            // n == grid.length
            // n == grid[i].length
            // 1 <= n <= 100
            // grid[i][j] is 0 or 1
        }
        let mut grid = grid;
        let n = grid.len();
        let mut front: Vec<(i32, i32)> = Vec::new();
        let mut count = 0;
        for (i, item) in grid.iter().enumerate().take(n) {
            for (j, &item) in item.iter().enumerate().take(n) {
                if item == 1 {
                    count += 1;
                    front.push((i as i32, j as i32));
                }
            }
        }
        let neighbor = vec![(0, -1), (0, 1), (-1, 0), (1, 0)];
        for step in 0.. {
            let mut new_front: Vec<(i32, i32)> = Vec::new();
            for pt in front {
                for off in &neighbor {
                    let new_i = pt.0 + off.0;
                    let new_j = pt.1 + off.1;
                    if new_i >= 0
                        && new_i < n as i32
                        && new_j >= 0
                        && new_j < n as i32
                        && grid[new_i as usize][new_j as usize] == 0
                    {
                        new_front.push((new_i, new_j));
                        grid[new_i as usize][new_j as usize] = 1;
                    }
                }
            }
            if new_front.is_empty() {
                return if step == 0 { -1 } else { step };
            }
            front = new_front;
        }
        -1 // Won't reach here.
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let grid = [vec![1, 0, 1], vec![0, 0, 0], vec![1, 0, 1]];
        let output = 2;
        //  Explanation: The cell (1, 1) is as far as possible
        // from all the land with distance 2.
        let ret = Solution::max_distance(grid.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let grid = [vec![1, 0, 0], vec![0, 0, 0], vec![0, 0, 0]];
        let output = 4;
        // The cell (2, 2) is as far as possible from all the land with distance
        // 4.
        let ret = Solution::max_distance(grid.into());
        assert_eq!(ret, output);
    }
}
