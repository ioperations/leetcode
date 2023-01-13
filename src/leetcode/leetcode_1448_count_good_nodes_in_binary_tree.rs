use std::{cell::RefCell, collections::VecDeque, rc::Rc};

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
    /*
     * Given a binary tree root, a node X in the tree is named good if in the path
     * from root to X there are no nodes with a value greater than X.
     * Return the number of good nodes in the binary tree.
     */
    #[allow(unused)]
    fn good_nodes(r: &Option<Rc<RefCell<TreeNode<i32>>>>) -> i32 {
        if let Some(n) = r {
            let mut count = 0;
            let val = n.as_ref().borrow().val;
            Self::fun(Some(n), val, &mut count);
            return count;
        };
        0
    }

    fn fun(node: Option<&Rc<RefCell<TreeNode<i32>>>>, val: i32, count: &mut i32) {
        if node.is_none() {
            return;
        }
        let node = node.unwrap();
        if node.as_ref().borrow().val >= val {
            *count += 1;
        }
        let z = node.as_ref().borrow().val.max(val);
        Self::fun(node.borrow_mut().left.as_ref(), z, count);
        Self::fun(node.borrow_mut().right.as_ref(), z, count);
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
            z1.as_ref().borrow_mut().right = None;
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
        let root = vec![Some(3), Some(1), Some(4), Some(3), None, Some(1), Some(5)];
        let tree = build_binary_tree(&root[..]);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 4);
    }

    #[test]
    fn case2_test() {
        let root = vec![Some(3), Some(3), None, Some(4), Some(2)];
        let tree = build_binary_tree(&root[..]);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 3);
    }

    #[test]
    fn case3_test() {
        let root = vec![Some(1)];
        let tree = build_binary_tree(&root[..]);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 1);
    }

    #[test]
    fn case4_test() {
        let root = vec![Some(9), None, Some(3), Some(6)];
        let tree = build_binary_tree(&root[..]);
        let ret = Solution::good_nodes(&tree);
        assert_eq!(ret, 1);
    }
}
