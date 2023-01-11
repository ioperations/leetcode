/*Given the root of a binary tree, check whether it is a mirror of itself (i.e., symmetric around its center).*/

extern crate test;

// Definition for a binary tree node.
#[derive(Debug, PartialEq, Eq)]
struct TreeNode<T> {
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
use std::cell::RefCell;
use std::rc::Rc;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn is_symmetric<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> bool
    where
        T: Copy + std::cmp::PartialEq,
    {
        /// expect binary tree equal to input
        fn flatten_binary_tree<T>(
            root: Option<Rc<RefCell<TreeNode<T>>>>,
            left_to_right: bool,
        ) -> Vec<Option<T>>
        where
            T: std::cmp::PartialEq + Copy,
        {
            let mut q: VecDeque<Option<Rc<RefCell<TreeNode<T>>>>> = VecDeque::new();
            let mut ret: Vec<Option<T>> = vec![];
            q.push_back(root);
            while !q.is_empty() {
                let n1 = q.pop_front().unwrap();
                if let Some(n) = &n1 {
                    ret.push(Some(n.as_ref().borrow().val));
                    if left_to_right {
                        q.push_back(n.as_ref().borrow_mut().left.take());
                        q.push_back(n.as_ref().borrow_mut().right.take());
                    } else {
                        q.push_back(n.as_ref().borrow_mut().right.take());
                        q.push_back(n.as_ref().borrow_mut().left.take());
                    }
                } else {
                    ret.push(None);
                }
            }

            ret.into_iter()
                .rev()
                .skip_while(std::option::Option::is_none)
                .collect::<Vec<Option<T>>>()
                .into_iter()
                .rev()
                .collect::<Vec<Option<T>>>()
        }

        if let Some(v) = root {
            let left = flatten_binary_tree(v.as_ref().borrow_mut().left.take(), true);
            let right = flatten_binary_tree(v.as_ref().borrow_mut().right.take(), false);
            return left == right;
        }
        true
    }

    #[allow(unused)]
    pub fn is_symmetric_v2<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> bool
    where
        T: Copy + std::cmp::PartialEq,
    {
        type Rn<T> = Rc<RefCell<TreeNode<T>>>;

        fn f<T>(p: Option<&Rn<T>>, q: Option<&Rn<T>>) -> bool
        where
            T: Copy + std::cmp::PartialEq,
        {
            match (p, q) {
                (None, None) => true,
                (Some(p), Some(q)) => {
                    let p = p.borrow();
                    let q = q.borrow();
                    p.val == q.val
                        && f(p.left.as_ref(), q.right.as_ref())
                        && f(p.right.as_ref(), q.left.as_ref())
                }
                _ => false,
            }
        }

        match root {
            None => true,
            Some(n) => {
                let n = n.borrow();
                f(n.left.as_ref(), n.right.as_ref())
            }
        }
    }

    // 我的实现跑题了，但看起来也是很巧妙,可以自己构造一种场景
    #[allow(unused)]
    pub fn is_symmetric_my_defination<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> bool
    where
        T: Copy + std::cmp::PartialEq,
    {
        fn is_symmetric_internal<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> (Option<T>, bool)
        where
            T: Copy + std::cmp::PartialEq,
        {
            if let Some(v) = root {
                let (left_value, left_ok) =
                    is_symmetric_internal(v.as_ref().borrow_mut().left.take());
                if !left_ok {
                    return (None, false);
                }
                let (right_value, right_ok) =
                    is_symmetric_internal(v.as_ref().borrow_mut().right.take());

                if !right_ok {
                    return (None, false);
                }
                return match (left_value, right_value) {
                    (Some(left), Some(right)) => (Some(v.as_ref().borrow_mut().val), left == right),
                    (Some(_), None) | (None, Some(_)) => (None, false),
                    (None, None) => (Some(v.as_ref().borrow_mut().val), true),
                };
            }
            (None, true)
        }
        is_symmetric_internal(root).1
    }
}
use std::collections::VecDeque;

/// build binary tree from &[T]
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

/// expect binary tree equal to input
#[allow(unused)]
fn flatten_binary_tree<T>(root: Option<Rc<RefCell<TreeNode<T>>>>) -> Vec<Option<T>>
where
    T: std::cmp::PartialEq + std::fmt::Debug + Copy,
{
    let mut q: VecDeque<Option<Rc<RefCell<TreeNode<T>>>>> = VecDeque::new();
    let mut ret: Vec<Option<T>> = vec![];
    q.push_back(root);
    while !q.is_empty() {
        let n1 = q.pop_front().unwrap();
        if let Some(n) = &n1 {
            ret.push(Some(n.as_ref().borrow().val));
            q.push_back(n.as_ref().borrow_mut().left.take());
            q.push_back(n.as_ref().borrow_mut().right.take());
        } else {
            ret.push(None);
        }
    }

    ret.into_iter()
        .rev()
        .skip_while(std::option::Option::is_none)
        .collect::<Vec<Option<T>>>()
        .into_iter()
        .rev()
        .collect::<Vec<Option<T>>>()
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let root = [1, 2, 2, 3, 4, 4, 3];
        let output = true;
        let root = root.iter().map(|i| Some(*i)).collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric(root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric(root);
        assert_eq!(ret, output);
    }
    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::is_symmetric(root);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn case1_test() {
        let root = [1, 2, 2, 3, 4, 4, 3];
        let output = true;
        let root = root.iter().map(|i| Some(*i)).collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric_v2(root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric_v2(root);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::is_symmetric_v2(root);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_my_defination {
    use super::*;

    #[test]
    fn case1_test() {
        let root = [1, 2, 2, 4, 4, 3, 3];
        let output = true;
        let root = root.iter().map(|i| Some(*i)).collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric_my_defination(root);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = root
            .iter()
            .map(|i| {
                if *i == -1 {
                    return None;
                }
                Some(*i)
            })
            .collect::<Vec<Option<i32>>>();
        let root = build_binary_tree(&root);
        let ret = Solution::is_symmetric_my_defination(root);
        assert_eq!(ret, output);
    }

    #[bench]
    fn bench_my_defination(b: &mut test::Bencher) {
        let root = [1, 2, 2, -1, 3, -1, 3];
        let output = false;
        let root = IntoIterator::into_iter(root)
            .map(|i| {
                if i == -1 {
                    return None;
                }
                Some(i)
            })
            .collect::<Vec<Option<i32>>>();
        b.iter(|| {
            let root = build_binary_tree(&root);
            let ret = Solution::is_symmetric_my_defination(root);
            assert_eq!(ret, output);
        });
    }
}
