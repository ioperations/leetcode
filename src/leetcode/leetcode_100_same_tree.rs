use std::{cell::RefCell, collections::VecDeque, rc::Rc};

/// Definition for a binary tree node.
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
    fn is_same_tree<T>(
        p: &Option<Rc<RefCell<TreeNode<T>>>>,
        q: &Option<Rc<RefCell<TreeNode<T>>>>,
    ) -> bool
    where
        T: std::cmp::PartialEq,
    {
        if p.is_none() && q.is_none() {
            return true;
        }

        if let (Some(p), Some(q)) = (p, q) {
            let ok = q.borrow().val == p.borrow().val;

            ok && Self::is_same_tree(&p.borrow().left, &q.borrow().left)
                && Self::is_same_tree(&p.borrow().right, &q.borrow().right)
        } else {
            false
        }
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
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.as_ref().borrow_mut().right =
                Some(Rc::new(RefCell::new(TreeNode::<T>::new(input[i].unwrap()))));
        } else {
            z1.as_ref().borrow_mut().right = None;
        }
        queue.push_back(z1.borrow().right.as_ref().unwrap().clone());
        i += 1;
    }
    Some(root)
}

/// expect binary tree equal to input
#[allow(unused)]
fn expect_binary_tree<T>(input: &[Option<T>], root: &Option<Rc<RefCell<TreeNode<T>>>>)
where
    T: std::cmp::PartialEq + std::fmt::Debug + Copy,
{
    // pass
    let mut i = 0;
    let size = input.len();
    if i == size {
        return;
    }

    let mut q: VecDeque<Rc<RefCell<TreeNode<T>>>> = VecDeque::new();
    q.push_back(root.as_ref().unwrap().clone());
    while !q.is_empty() {
        let n1 = q.pop_front().unwrap();
        assert_eq!(Some(n1.as_ref().borrow().val), input[i]);
        i += 1;
        if let Some(v) = &n1.as_ref().borrow().left {
            q.push_back(v.clone());
        };
        if let Some(v) = &n1.as_ref().borrow().right {
            q.push_back(v.clone());
        };
    }

    assert_eq!(i, size);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case0_test() {
        let null = 1000;
        let p = [1, 2, 3]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let q = [1, 2, 3]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let tree = build_binary_tree(&p[..]);
        expect_binary_tree(&p[..], &tree);
        let tree2 = build_binary_tree(&q[..]);
        expect_binary_tree(&q[..], &tree2);
    }

    #[test]
    fn case1_test() {
        let null = 1000;
        let p = [1, 2, 3]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let q = [1, 2, 3]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let tree1 = build_binary_tree(&p[..]);
        let tree2 = build_binary_tree(&q[..]);
        let ret = Solution::is_same_tree(&tree1, &tree2);
        assert!(ret);
    }

    #[test]
    fn case2_test() {
        let null = 1000;
        let p = [1, 2]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let q = [1, 2]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let tree1 = build_binary_tree(&p[..]);
        let tree2 = build_binary_tree(&q[..]);
        let ret = Solution::is_same_tree(&tree1, &tree2);
        assert!(ret);
    }

    #[test]
    fn case3_test() {
        let null = 1000;
        let p = [1, 2, 1]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let q = [1, 1, 2]
            .map(|i| {
                if i == null {
                    return None;
                }
                Some(i)
            })
            .to_vec();
        let tree1 = build_binary_tree(&p[..]);
        let tree2 = build_binary_tree(&q[..]);
        let ret = Solution::is_same_tree(&tree1, &tree2);
        assert!(!ret);
    }
}
