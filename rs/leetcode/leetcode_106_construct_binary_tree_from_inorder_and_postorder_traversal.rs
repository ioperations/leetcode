// Given two integer arrays inorder and postorder where inorder is the inorder
// traversal of a binary tree and postorder is the postorder traversal of the
// same tree, construct and return the binary tree.

use super::leetcode_binary_tree::TreeNode;

#[allow(unused)]
struct Solution;

use std::cell::RefCell;
use std::rc::Rc;

use std::collections::HashMap;

type InorderMap<T> = HashMap<T, usize>;
type Rn<T> = Option<Rc<RefCell<TreeNode<T>>>>;

struct TreeBuilder<T>
where
    T: std::hash::Hash + std::cmp::Eq + Copy,
{
    map: InorderMap<T>,
    postorder: Vec<T>,
    post_idx: i32,
}

impl<T> TreeBuilder<T>
where
    T: std::hash::Hash + std::cmp::Eq + Copy,
{
    fn new(inorder: &[T], postorder: Vec<T>) -> Self
    where
        T: std::hash::Hash + std::cmp::Eq + Copy,
    {
        let index = (postorder.len() - 1) as i32;

        Self {
            map: inorder
                .iter()
                .enumerate()
                .map(|(x, &v)| (v, x))
                .collect::<InorderMap<T>>(),
            postorder,
            post_idx: index,
        }
    }

    fn build_tree(&mut self, start: i32, end: i32) -> Rn<T> {
        if start > end {
            return None;
        }

        let root = self.postorder[self.post_idx as usize];
        let inorder_root_index = *self.map.get(&root).unwrap() as i32;
        let root_node = Rc::new(RefCell::new(TreeNode::new(root)));

        self.post_idx -= 1;

        {
            let mut bor = root_node.borrow_mut();

            bor.right = self.build_tree(inorder_root_index + 1, end);

            bor.left = self.build_tree(start, inorder_root_index - 1);
        }

        Some(root_node)
    }
}

impl Solution {
    #[allow(unused)]
    pub fn build_tree<T>(
        inorder: &[T],
        postorder: Vec<T>,
    ) -> Option<Rc<RefCell<TreeNode<T>>>>
    where
        T: std::hash::Hash + std::cmp::Eq + Copy,
    {
        let size = (inorder.len() - 1) as i32;
        let mut bt = TreeBuilder::new(inorder, postorder);

        bt.build_tree(0, size)
    }
}

#[cfg(test)]
mod test {
    use super::super::leetcode_binary_tree::expect_binary_tree;

    use super::*;
    const NULL: i32 = -2;

    pub trait IntoOption<T> {
        fn into_option(self) -> Vec<Option<T>>;
    }

    impl<const N: usize> IntoOption<i32> for [i32; N] {
        fn into_option(self) -> Vec<Option<i32>> {
            self.into_iter()
                .map(|i| if i == NULL { None } else { Some(i) })
                .collect()
        }
    }

    #[test]
    fn case1_test() {
        let inorder = [9, 3, 15, 20, 7];
        let postorder = [9, 15, 7, 20, 3];
        let ret = Solution::build_tree(&inorder, postorder.into());
        let output: Vec<_> = [3, 9, 20, 15, 7].into_option();
        expect_binary_tree(&output, &ret);
    }

    #[test]
    fn case2_test() {
        let inorder = [-1];
        let postorder = [-1];
        let ret = Solution::build_tree(&inorder, postorder.into());
        let output: Vec<_> = [-1].into_option();
        expect_binary_tree(&output, &ret);
    }
}
