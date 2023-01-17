// Given the root of a binary tree, construct a 0-indexed m x n string matrix
// res that represents a formatted layout of the tree. The formatted layout
// matrix should be constructed using the following rules: The height of the
// tree is height and the number of rows m should be equal to height + 1.
// The number of columns n should be equal to 2height+1 - 1.
// Place the root node in the middle of the top row (more formally, at location
// res[0][(n-1)/2]). For each node that has been placed in the matrix at
// position res[r][c], Place its left child at res[r+1][c-2height-r-1] and its
// right child at res[r+1][c+2height-r-1]. Continue this process until all the
// nodes in the tree have been placed. Any empty cells should contain the empty
// string "". Return the constructed matrix res.

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, collections::VecDeque, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn print_tree(
        root: Option<Rc<RefCell<TreeNode<i32>>>>,
    ) -> Vec<Vec<String>> {
        if let Some(v) = root {
            let mut queue = VecDeque::new();
            queue.push_back((Some(v), 0));
            let mut value: Vec<Option<i32>> = vec![];
            let mut height: i32 = 0;
            while !queue.is_empty() {
                let (r, count) = queue.pop_front().unwrap();
                if let Some(n) = r {
                    height = count;
                    value.push(Some(n.as_ref().borrow().val));
                    queue.push_back((
                        n.as_ref().borrow_mut().left.take(),
                        count + 1,
                    ));
                    queue.push_back((
                        n.as_ref().borrow_mut().right.take(),
                        count + 1,
                    ));
                } else {
                    value.push(None);
                }
            }
            let value = value
                .into_iter()
                .rev()
                .skip_while(std::option::Option::is_none)
                .collect::<Vec<Option<i32>>>()
                .into_iter()
                .rev()
                .collect::<Vec<Option<i32>>>();

            let height = height;
            let m_v: i32 = height + 1;
            let n_v: i32 = 2_i32.pow((height + 1) as u32) - 1;
            let mut matrix =
                vec![vec![String::new(); n_v as usize]; m_v as usize];

            let v: (i32, i32) = (0, (n_v - 1) / 2);

            let mut index = 0;
            matrix[v.0 as usize][v.1 as usize] =
                format!("{}", value[index].unwrap());
            let mut q = VecDeque::new();

            let len = value.len();
            q.push_back(v);
            while !q.is_empty() && (index + 1) < len {
                let (r_v, c_v) = q.pop_front().unwrap();
                index += 1;
                if let Some(v) = value[index] {
                    let c = c_v - 2_i32.pow((height - r_v - 1) as u32);
                    let r = r_v + 1;
                    matrix[r as usize][c as usize] = format!("{v}");
                    q.push_back((r, c));
                }

                index += 1;
                if index >= len {
                    break;
                }

                if let Some(v) = value[index] {
                    let c = c_v + (2_i32.pow((height - r_v - 1) as u32));
                    let r = r_v + 1;
                    matrix[r as usize][c as usize] = format!("{v}");
                    q.push_back((r, c));
                }
            }

            matrix
        } else {
            std::vec::Vec::default()
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let root = vec![Some(1), Some(2)];
        let output = vec![["", "1", ""], ["2", "", ""]];
        let t = build_binary_tree(&root);
        let ret = Solution::print_tree(t);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = vec![Some(1), Some(2), Some(3), None, Some(4)];
        let output = vec![
            ["", "", "", "1", "", "", ""],
            ["", "2", "", "", "", "3", ""],
            ["", "", "4", "", "", "", ""],
        ];
        let t = build_binary_tree(&root);
        let ret = Solution::print_tree(t);
        assert_eq!(ret, output);
    }
}
