/*Given the root of a binary tree, construct a 0-indexed m x n string matrix res that represents a formatted layout of the tree. The formatted layout matrix should be constructed using the following rules:

The height of the tree is height and the number of rows m should be equal to height + 1.
The number of columns n should be equal to 2height+1 - 1.
Place the root node in the middle of the top row (more formally, at location res[0][(n-1)/2]).
For each node that has been placed in the matrix at position res[r][c], place its left child at res[r+1][c-2height-r-1] and its right child at res[r+1][c+2height-r-1].
Continue this process until all the nodes in the tree have been placed.
Any empty cells should contain the empty string "".
Return the constructed matrix res.

*/
use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

/// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
pub struct TreeNode<T> {
    pub val: T,
    pub left: Option<Rc<RefCell<TreeNode<T>>>>,
    pub right: Option<Rc<RefCell<TreeNode<T>>>>,
}

impl<T> TreeNode<T> {
    #[inline]
    pub fn new(val: T) -> Self {
        TreeNode {
            val,
            left: None,
            right: None,
        }
    }
}

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn print_tree(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> Vec<Vec<String>> {
        if let Some(v) = root {
            let mut q = VecDeque::new();
            q.push_back((Some(v), 0));
            let mut value: Vec<Option<i32>> = vec![];
            let mut height: i32 = 0;
            while !q.is_empty() {
                let (r, count) = q.pop_front().unwrap();
                if let Some(n) = r {
                    height = count;
                    value.push(Some(n.as_ref().borrow().val));
                    q.push_back((n.as_ref().borrow_mut().left.take(), count + 1));
                    q.push_back((n.as_ref().borrow_mut().right.take(), count + 1));
                } else {
                    value.push(None);
                }
            }
            let value = value
                .into_iter()
                .rev()
                .skip_while(|n| n.is_none())
                .collect::<Vec<Option<i32>>>()
                .into_iter()
                .rev()
                .collect::<Vec<Option<i32>>>();

            let height = height;
            let m: i32 = height + 1;
            let n: i32 = 2_i32.pow((height + 1) as u32) - 1;
            let mut matrix = vec![vec![String::from(""); n as usize]; m as usize];

            let v: (i32, i32) = (0, (n - 1) / 2);

            let mut i = 0;
            matrix[v.0 as usize][v.1 as usize] = format!("{}", value[i].unwrap());
            let mut q = VecDeque::new();

            let len = value.len();
            q.push_back(v);
            while !q.is_empty() && (i + 1) < len {
                let (r, c) = q.pop_front().unwrap();
                i += 1;
                if let Some(v) = value[i] {
                    let c = c - 2_i32.pow((height - r - 1) as u32);
                    let r = r + 1;
                    matrix[r as usize][c as usize] = format!("{}", v);
                    q.push_back((r, c));
                }

                i += 1;
                if i >= len {
                    break;
                }

                if let Some(v) = value[i] {
                    let c = c + (2_i32.pow((height - r - 1) as u32));
                    let r = r + 1;
                    matrix[r as usize][c as usize] = format!("{}", v);
                    q.push_back((r, c));
                }
            }

            return matrix;
        }
        vec![vec![]]
    }
}

/// build binary tree from &[i32]
#[allow(unused)]
fn build_binary_tree<T>(input: &[Option<T>]) -> Option<Rc<RefCell<TreeNode<T>>>>
where
    T: Copy,
{
    let size = input.len();
    if size == 0 {
        return None;
    }

    let mut queue: VecDeque<Rc<RefCell<TreeNode<T>>>> = VecDeque::new();
    let root = Rc::new(RefCell::new(TreeNode::<T>::new(input[0].unwrap())));
    queue.push_back(root.clone());
    let mut i = 1;

    while i < size {
        let z1 = queue.pop_front().unwrap();
        if input[i].is_some() {
            z1.as_ref().borrow_mut().left =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
            queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.as_ref().borrow_mut().right =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
            queue.push_back(z1.borrow().right.as_ref().unwrap().clone());
        } else {
            z1.as_ref().borrow_mut().right = None
        }
        i += 1;
    }
    Some(root)
}

#[cfg(test)]
mod tests {
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
