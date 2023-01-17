use super::leetcode_binary_tree::TreeNode;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn sorted_array_to_bst<T>(nums: &[T]) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: Copy,
    {
        // pass
        Self::helper(nums, 0, (nums.len() - 1) as i32)
    }

    #[allow(unused)]
    fn helper<T>(
        nums: &[T],
        start: i32,
        end: i32,
    ) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: Copy,
    {
        if start > end {
            return None;
        }
        let mid = start + (end - start) / 2;
        // println!("start is {}, end is {}, mid is {}", start, end, mid);

        let root = Rc::new(RefCell::new(TreeNode::new(nums[mid as usize])));
        root.as_ref().borrow_mut().left = Self::helper(nums, start, mid - 1);
        root.as_ref().borrow_mut().right = Self::helper(nums, mid + 1, end);

        Some(root)
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::{
        build_binary_tree, flatten_binary_tree,
    };
    use std::collections::HashSet;

    use super::*;

    #[test]
    fn case0_test() {
        let tree = [Some(1), Some(2), Some(3), Some(4)];
        let v = build_binary_tree(&tree);
        let ret = flatten_binary_tree(v);
        assert_eq!(ret, tree);
    }

    #[test]
    fn case1_test() {
        let tree = [Some(-10), Some(-3), Some(0), Some(5), Some(9)];
        let v = build_binary_tree(&tree);
        let ret = flatten_binary_tree(v);
        assert_eq!(ret, tree);
    }

    #[test]
    fn case2_test() {
        let v = vec![-10, -3, 0, 5, 9];
        let ret = Solution::sorted_array_to_bst(&v);
        let ret = flatten_binary_tree(ret);
        println!("ret =>  {ret:?}");
        let mut hashset = HashSet::new();
        hashset.insert(
            [Some(0), Some(-3), Some(9), Some(10), None, Some(9)].to_vec(),
        );
        hashset.insert(
            [Some(0), Some(-10), Some(5), None, Some(-3), None, Some(9)]
                .to_vec(),
        );

        assert!(hashset.contains(&ret));
    }
}
