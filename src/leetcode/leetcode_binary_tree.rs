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

/// build binary tree from &[T]
#[allow(unused)]
pub fn build_binary_tree<T>(
    input: &[Option<T>],
) -> Option<Rc<RefCell<TreeNode<T>>>>
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
            z1.as_ref().borrow_mut().left = Some(Rc::new(RefCell::new(
                TreeNode::<T>::new(input[i].unwrap()),
            )));
            queue.push_back(z1.borrow().left.as_ref().unwrap().clone());
        } else {
            z1.as_ref().borrow_mut().left = None;
        }

        i += 1;
        if i >= size {
            break;
        }
        if input[i].is_some() {
            z1.as_ref().borrow_mut().right = Some(Rc::new(RefCell::new(
                TreeNode::<T>::new(input[i].unwrap()),
            )));
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
pub fn flatten_binary_tree<T>(
    root: Option<Rc<RefCell<TreeNode<T>>>>,
) -> Vec<Option<T>>
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

#[allow(unused)]
pub fn right_expect<T>(
    root: &Option<Rc<RefCell<TreeNode<T>>>>,
    vec: &[Option<T>],
) where
    T: std::fmt::Debug + std::cmp::PartialEq + Copy,
{
    if vec.is_empty() && root.is_none() {
        return;
    }

    assert!(root.is_some());

    if let Some(n) = &root {
        assert!(vec[0].is_some());
        assert_eq!(n.as_ref().borrow().val, vec[0].unwrap());
        assert!(n.as_ref().borrow_mut().left.is_none());
        right_expect(&n.as_ref().borrow_mut().right, &vec[1..]);
    }
}

/// expect binary tree equal to input
#[allow(unused)]
pub fn expect_binary_tree<T: std::cmp::PartialEq + std::fmt::Debug + Copy>(
    input: &[Option<T>],
    root: &Option<Rc<RefCell<TreeNode<T>>>>,
) {
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
