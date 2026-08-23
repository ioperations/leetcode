// Given the root of a binary tree and two integers val and depth, add a row of
// nodes with value val at the given depth depth.
//
// Note that the root node is at depth 1.
//
// The adding rule is:
//
// Given the integer depth, for each not null tree node cur at the depth depth -
// 1, create two tree nodes with value val as cur's left subtree root and right
// subtree root. cur's original left subtree should be the left subtree of the
// new left subtree root. cur's original right subtree should be the right
// subtree of the new right subtree root. If depth == 1 that means there is no
// depth depth - 1 at all, then create a tree node with value val as the new
// root of the whole original tree, and the original tree is the new root's left
// subtree.

// The depth of the tree is in the range [1, 104].
// -100 <= Node.val <= 100
// -105 <= val <= 105
// 1 <= depth <= the depth of tree + 1

use super::leetcode_binary_tree::TreeNode;

use std::cell::RefCell;
use std::collections::VecDeque;
use std::rc::Rc;

type TreeNodei32 = TreeNode<i32>;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn add_one_row(
        root: Option<Rc<RefCell<TreeNodei32>>>,
        new_val: i32,
        depth: i32,
    ) -> Option<Rc<RefCell<TreeNodei32>>> {
        Some(Rc::new(RefCell::new(match depth {
            1 => TreeNodei32 {
                val: new_val,
                left: root,
                right: None,
            },
            2 => {
                let TreeNodei32 { val, left, right } =
                    Rc::try_unwrap(root?).unwrap().into_inner();
                TreeNodei32 {
                    val,
                    left: Some(Rc::new(RefCell::new(TreeNodei32 {
                        val: new_val,
                        left,
                        right: None,
                    }))),
                    right: Some(Rc::new(RefCell::new(TreeNodei32 {
                        val: new_val,
                        left: None,
                        right,
                    }))),
                }
            }
            depth => {
                let TreeNode { val, left, right } =
                    Rc::try_unwrap(root?).unwrap().into_inner();
                TreeNodei32 {
                    val,
                    left: Self::add_one_row(left, new_val, depth - 1),
                    right: Self::add_one_row(right, new_val, depth - 1),
                }
            }
        })))
    }

    #[allow(unused)]
    pub fn add_one_row_bfs(
        root: Option<Rc<RefCell<TreeNodei32>>>,
        v: i32,
        d: i32,
    ) -> Option<Rc<RefCell<TreeNodei32>>> {
        let root = root?;

        if d == 1 {
            return Some(Rc::new(RefCell::new(TreeNode {
                val: v,
                left: Some(root),
                right: None,
            })));
        }

        let mut depth = 1;
        let mut queue = VecDeque::new();
        queue.push_back(root.clone());

        while !queue.is_empty() {
            if depth + 1 == d {
                while let Some(node) = queue.pop_front() {
                    let mut borrow = node.borrow_mut();
                    borrow.left = Some(Rc::new(RefCell::new(TreeNode {
                        val: v,
                        left: borrow.left.take(),
                        right: None,
                    })));
                    borrow.right = Some(Rc::new(RefCell::new(TreeNode {
                        val: v,
                        left: None,
                        right: borrow.right.take(),
                    })));
                }
                break;
            }

            for _ in 0..queue.len() {
                let node = queue.pop_front().unwrap();
                if let Some(ref l) = node.clone().borrow().left {
                    queue.push_back(l.clone());
                }
                if let Some(ref r) = node.clone().borrow().right {
                    queue.push_back(r.clone());
                }
            }

            depth += 1;
        }
        Some(root)
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::{
        build_binary_tree, flatten_binary_tree,
    };
    use super::*;
    const NULL: i32 = -1;

    #[test]
    fn case1_test() {
        let root: Vec<Option<i32>> =
            [4, 2, 6, 3, 1, 5].into_iter().map(|i| Some(i)).collect();
        let val = 1;
        let depth = 2;
        let binary_tree = build_binary_tree(&root);
        let output: Vec<Option<i32>> = [4, 1, 1, 2, NULL, NULL, 6, 3, 1, 5]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let ret = Solution::add_one_row(binary_tree, val, depth);

        let falttern: Vec<Option<i32>> = flatten_binary_tree(ret);
        assert_eq!(output, falttern);
    }

    #[test]
    fn case2_test() {
        let root: Vec<Option<i32>> = [4, 2, NULL, 3, 1]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let val = 1;
        let depth = 3;
        let binary_tree = build_binary_tree(&root);
        let output: Vec<Option<i32>> = [4, 2, NULL, 1, 1, 3, NULL, NULL, 1]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let ret = Solution::add_one_row(binary_tree, val, depth);

        let falttern: Vec<Option<i32>> = flatten_binary_tree(ret);
        assert_eq!(output, falttern);
    }

    #[test]
    fn case1_test_v1() {
        let root: Vec<Option<i32>> =
            [4, 2, 6, 3, 1, 5].into_iter().map(|i| Some(i)).collect();
        let val = 1;
        let depth = 2;
        let binary_tree = build_binary_tree(&root);
        let output: Vec<Option<i32>> = [4, 1, 1, 2, NULL, NULL, 6, 3, 1, 5]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let ret = Solution::add_one_row_bfs(binary_tree, val, depth);

        let falttern: Vec<Option<i32>> = flatten_binary_tree(ret);
        assert_eq!(output, falttern);
    }

    #[test]
    fn case2_test_v1() {
        let root: Vec<Option<i32>> = [4, 2, NULL, 3, 1]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let val = 1;
        let depth = 3;
        let binary_tree = build_binary_tree(&root);
        let output: Vec<Option<i32>> = [4, 2, NULL, 1, 1, 3, NULL, NULL, 1]
            .into_iter()
            .map(|i| if i == NULL { None } else { Some(i) })
            .collect();
        let ret = Solution::add_one_row_bfs(binary_tree, val, depth);

        let falttern: Vec<Option<i32>> = flatten_binary_tree(ret);
        assert_eq!(output, falttern);
    }
}
