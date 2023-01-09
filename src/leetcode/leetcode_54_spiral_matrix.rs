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
    pub fn spiral_order(matrix: &[Vec<i32>]) -> Vec<i32> {
        assert!(!matrix.is_empty());
        let row = matrix.len() as i32;
        let column = matrix[0].len() as i32;
        let mut dir = Direction::Right;
        let mut index = 0;
        let mut vec = Vec::with_capacity((row * column) as usize);
        let mut current_position: (i32, i32) = (0, -1);
        let mut hasmap = HashSet::new();

        while index < row * column {
            let (x_pos, y_pos) = &mut current_position;
            match dir {
                Direction::Right => {
                    if *y_pos + 1 >= column || hasmap.contains(&(*x_pos, *y_pos + 1)) {
                        dir = Direction::Down;
                    } else {
                        *y_pos += 1;
                        vec.push(matrix[*x_pos as usize][*y_pos as usize]);
                        hasmap.insert((*x_pos, *y_pos));
                        index += 1;
                    }
                }
                Direction::Down => {
                    if *x_pos + 1 >= row || hasmap.contains(&(*x_pos + 1, *y_pos)) {
                        dir = Direction::Left;
                    } else {
                        *x_pos += 1;
                        vec.push(matrix[*x_pos as usize][*y_pos as usize]);
                        hasmap.insert((*x_pos, *y_pos));
                        index += 1;
                    }
                }
                Direction::Left => {
                    if *y_pos - 1 < 0 || hasmap.contains(&(*x_pos, *y_pos - 1)) {
                        dir = Direction::UP;
                    } else {
                        *y_pos -= 1;
                        vec.push(matrix[*x_pos as usize][*y_pos as usize]);
                        hasmap.insert((*x_pos, *y_pos));
                        index += 1;
                    }
                }
                Direction::UP => {
                    if *x_pos - 1 < 0 || hasmap.contains(&(*x_pos - 1, *y_pos)) {
                        dir = Direction::Right;
                    } else {
                        *x_pos -= 1;
                        vec.push(matrix[*x_pos as usize][*y_pos as usize]);
                        hasmap.insert((*x_pos, *y_pos));
                        index += 1;
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
        let ret = Solution::spiral_order(&matrix);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let matrix = vec![vec![1, 2, 3, 4], vec![5, 6, 7, 8], vec![9, 10, 11, 12]];
        let output = vec![1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7];
        let ret = Solution::spiral_order(&matrix);
        assert_eq!(ret, output);
    }
}
