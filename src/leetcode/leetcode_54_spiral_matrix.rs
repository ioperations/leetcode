/*Given an m x n matrix, return all elements of the matrix in spiral order.*/
#[allow(unused)]
struct Solution;

use std::collections::HashSet;
enum Direction {
    Left,
    Right,
    UP,
    Down,
}

impl Solution {
    #[allow(unused)]
    pub fn spiral_order(matrix: Vec<Vec<i32>>) -> Vec<i32> {
        assert!(!matrix.is_empty());
        let m = matrix.len() as i32;
        let n = matrix[0].len() as i32;
        let mut dir = Direction::Right;
        let mut i = 0;
        let mut vec = Vec::with_capacity((m * n) as usize);
        let mut current_position: (i32, i32) = (0, -1);
        let mut hasmap = HashSet::new();

        while i < m * n {
            let (x, y) = &mut current_position;
            match dir {
                Direction::Right => {
                    if *y + 1 >= n || hasmap.contains(&(*x, *y + 1)) {
                        dir = Direction::Down;
                    } else {
                        *y += 1;
                        vec.push(matrix[*x as usize][*y as usize]);
                        hasmap.insert((*x, *y));
                        i += 1;
                    }
                }
                Direction::Down => {
                    if *x + 1 >= m || hasmap.contains(&(*x + 1, *y)) {
                        dir = Direction::Left;
                    } else {
                        *x += 1;
                        vec.push(matrix[*x as usize][*y as usize]);
                        hasmap.insert((*x, *y));
                        i += 1;
                    }
                }
                Direction::Left => {
                    if *y - 1 < 0 || hasmap.contains(&(*x, *y - 1)) {
                        dir = Direction::UP;
                    } else {
                        *y -= 1;
                        vec.push(matrix[*x as usize][*y as usize]);
                        hasmap.insert((*x, *y));
                        i += 1;
                    }
                }
                Direction::UP => {
                    if *x - 1 < 0 || hasmap.contains(&(*x - 1, *y)) {
                        dir = Direction::Right;
                    } else {
                        *x -= 1;
                        vec.push(matrix[*x as usize][*y as usize]);
                        hasmap.insert((*x, *y));
                        i += 1;
                    }
                }
            }
        }

        vec
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let matrix = vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]];
        let output = vec![1, 2, 3, 6, 9, 8, 7, 4, 5];
        let ret = Solution::spiral_order(matrix);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let matrix = vec![vec![1, 2, 3, 4], vec![5, 6, 7, 8], vec![9, 10, 11, 12]];
        let output = vec![1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7];
        let ret = Solution::spiral_order(matrix);
        assert_eq!(ret, output);
    }
}
