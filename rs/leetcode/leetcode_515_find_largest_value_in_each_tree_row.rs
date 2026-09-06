// Given the root of a binary tree, return an array of the largest value in each
// row of the tree (0-indexed).

// The number of nodes in the tree will be in the range [0, 104].
// -231 <= Node.val <= 231 - 1

use super::leetcode_binary_tree::TreeNode;

type TN = TreeNode<i32>;

use std::cell::RefCell;
use std::collections::BinaryHeap;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn largest_values(root: Option<Rc<RefCell<TN>>>) -> Vec<i32> {
        if root.is_none() {
            return vec![];
        }

        let mut root = root;

        struct Node {
            node: Rc<RefCell<TN>>,
            level: i32,
        };

        impl PartialEq for Node {
            fn eq(&self, other: &Self) -> bool {
                return self.level == other.level;
            }
        }

        impl Eq for Node {}
        impl Ord for Node {
            fn cmp(&self, other: &Self) -> std::cmp::Ordering {
                self.level.cmp(&other.level)
            }
        }

        impl PartialOrd for Node {
            fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
                Some(other.level.cmp(&self.level))
            }
        }

        let mut binary_heap = BinaryHeap::new();
        binary_heap.push(Node {
            node: root.take().unwrap(),
            level: 1,
        });

        let mut current_level = 1;
        let mut current_max = i32::MIN;
        let mut ret = vec![];
        while let Some(v) = binary_heap.pop() {
            if v.level == current_level {
                let v = v.node.borrow().val;
                if v > current_max {
                    current_max = v;
                }
            } else {
                ret.push(current_max);
                current_max = v.node.borrow().val;
                current_level = v.level;
            }
            if let Some(node) = v.node.borrow_mut().left.take() {
                binary_heap.push(Node {
                    node,
                    level: v.level + 1,
                });
            }
            if let Some(node) = v.node.borrow_mut().right.take() {
                binary_heap.push(Node {
                    node,
                    level: v.level + 1,
                });
            }
        }
        ret.push(current_max);

        ret
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;
    const NULL: i32 = -1;

    #[test]
    fn case1_test() {
        let root = [1, 3, 2, 5, 3, NULL, 9]
            .iter()
            .map(|&v| {
                if v == NULL {
                    return None;
                }
                Some(v)
            })
            .collect::<Vec<_>>();
        let tree = build_binary_tree(&root);
        let ret = Solution::largest_values(tree);
        let output = vec![1, 3, 9];
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let root = [1, 2, 3]
            .iter()
            .map(|&v| {
                if v == NULL {
                    return None;
                }
                Some(v)
            })
            .collect::<Vec<_>>();
        let tree = build_binary_tree(&root);
        let ret = Solution::largest_values(tree);
        let output = vec![1, 3];
        assert_eq!(output, ret);
    }
}
