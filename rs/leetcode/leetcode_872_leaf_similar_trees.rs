// Consider all the leaves of a binary tree, from left to right order,
// the values of those leaves form a leaf value sequence.
// For example, in the given tree above, the leaf value sequence is (6, 7, 4, 9,
// 8).
//
// Two binary trees are considered leaf-similar if their leaf value sequence is
// the same. Return true if and only if the two given trees with head nodes
// root1 and root2 are leaf-similar.

use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, collections::VecDeque, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn leaf_similar<T>(
        root1: &Option<Rc<RefCell<TreeNode<T>>>>,
        root2: &Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> bool
    where
        T: std::cmp::PartialEq + Copy,
    {
        fn check_tree_node<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>) -> bool {
            if let Some(v) = root {
                return v.borrow().left.is_none() && v.borrow().right.is_none();
            }
            false
        };
        let vec1: Vec<T> = {
            let mut vec: Vec<T> = Vec::new();
            Self::preorder(root1, &mut vec);
            vec
        };
        let vec2: Vec<T> = {
            let mut vec: Vec<T> = Vec::new();
            Self::preorder(root2, &mut vec);
            vec
        };
        vec1 == vec2
    }

    #[allow(unused)]
    fn preorder<T>(root: &Option<Rc<RefCell<TreeNode<T>>>>, res: &mut Vec<T>)
    where
        T: Copy,
    {
        if let Some(n) = root {
            if n.borrow().left.is_none() && n.borrow().right.is_none() {
                res.push(n.borrow().val);
            }
            Self::preorder(&n.borrow().left, res);
            Self::preorder(&n.borrow().right, res);
        }
    }

    #[allow(unused)]
    pub fn leaf_similar_v2<T>(
        root1: Option<Rc<RefCell<TreeNode<T>>>>,
        root2: Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> bool
    where
        T: std::cmp::PartialEq + Copy,
    {
        fn helper<T>(node: Option<Rc<RefCell<TreeNode<T>>>>) -> Vec<T>
        where
            T: Copy,
        {
            fn check_tree_node<T>(t: &Rc<RefCell<TreeNode<T>>>) -> bool {
                t.borrow().left.is_none() && t.borrow().right.is_none()
            }
            let mut vecdeque = VecDeque::new();
            let mut vec = Vec::new();

            if let Some(t) = node {
                vecdeque.push_back(t);

                while !vecdeque.is_empty() {
                    let n = vecdeque.pop_front().unwrap();
                    if check_tree_node(&n) {
                        vec.push(n.borrow().val);
                    } else {
                        if let Some(t) = n.as_ref().borrow_mut().left.take() {
                            vecdeque.push_back(t);
                        };
                        if let Some(t) = n.as_ref().borrow_mut().right.take() {
                            vecdeque.push_back(t);
                        };
                    }
                }
            }
            vec
        }
        helper(root1) == helper(root2)
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let null = -1;
        let root1 = [3, 5, 1, 6, 2, 9, 8, null, null, 7, 4].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let root2 = [
            3, 5, 1, 6, 7, 4, 2, null, null, null, null, null, null, 9, 8,
        ]
        .map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = true;
        let ret = Solution::leaf_similar(
            &build_binary_tree(&root1),
            &build_binary_tree(&root2),
        );
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root1 = [1, 2, 3].map(Some);
        let root2 = [1, 3, 2].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = false;
        let ret = Solution::leaf_similar(
            &build_binary_tree(&root1),
            &build_binary_tree(&root2),
        );
        assert_eq!(ret, output);
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

    #[test]
    fn case1_test() {
        let null = -1;
        let root1 = [3, 5, 1, 6, 2, 9, 8, null, null, 7, 4].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let root2 = [
            3, 5, 1, 6, 7, 4, 2, null, null, null, null, null, null, 9, 8,
        ]
        .map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = false;
        let ret = Solution::leaf_similar_v2(
            build_binary_tree(&root1),
            build_binary_tree(&root2),
        );
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let null = -1;
        let root1 = [1, 2, 3].map(Some);
        let root2 = [1, 3, 2].map(|i| {
            if null == i {
                return None;
            }
            Some(i)
        });
        let output = false;
        let ret = Solution::leaf_similar_v2(
            build_binary_tree(&root1),
            build_binary_tree(&root2),
        );
        assert_eq!(ret, output);
    }
}
