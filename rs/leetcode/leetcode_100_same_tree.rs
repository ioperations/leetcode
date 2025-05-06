use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn is_same_tree<T>(
        p: Option<&Rc<RefCell<TreeNode<T>>>>,
        q: Option<&Rc<RefCell<TreeNode<T>>>>,
    ) -> bool
    where
        T: std::cmp::PartialEq,
    {
        if p.is_none() && q.is_none() {
            return true;
        }

        if let (Some(p), Some(q)) = (p, q) {
            let ok = q.borrow().val == p.borrow().val;

            ok && Self::is_same_tree(
                p.borrow().left.as_ref(),
                q.borrow().left.as_ref(),
            ) && Self::is_same_tree(
                p.borrow().right.as_ref(),
                q.borrow().right.as_ref(),
            )
        } else {
            false
        }
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use super::*;

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
        let tree1 = build_binary_tree(&p);
        let tree2 = build_binary_tree(&q);
        let ret = Solution::is_same_tree(tree1.as_ref(), tree2.as_ref());
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
        let tree1 = build_binary_tree(&p);
        let tree2 = build_binary_tree(&q);
        let ret = Solution::is_same_tree(tree1.as_ref(), tree2.as_ref());
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
        let tree1 = build_binary_tree(&p);
        let tree2 = build_binary_tree(&q);
        let ret = Solution::is_same_tree(tree1.as_ref(), tree2.as_ref());
        assert!(!ret);
    }
}
