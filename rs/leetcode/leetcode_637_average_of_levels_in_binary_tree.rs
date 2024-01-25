use super::leetcode_binary_tree::TreeNode;
use std::collections::VecDeque;
use std::{cell::RefCell, rc::Rc};

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    fn average_of_levels(root: Option<Rc<RefCell<TreeNode<i32>>>>) -> Vec<f64> {
        let mut v = vec![];

        if let Some(r) = root {
            let mut qu = VecDeque::new();

            let mut cur_level = 1;
            let mut cur_count = 0;
            let mut cur_sum: f64 = 0.0;
            qu.push_back((r, cur_level));
            while !qu.is_empty() {
                let z = qu.pop_front().unwrap();
                if z.1 == cur_level {
                    cur_sum += z.0.as_ref().borrow().val as f64;
                    cur_count += 1;
                } else {
                    v.push(cur_sum / cur_count as f64);
                    cur_level += 1;
                    cur_sum = f64::from(z.0.as_ref().borrow().val);
                    cur_count = 1;
                }
                if let Some(n) = z.0.as_ref().borrow_mut().left.take() {
                    qu.push_back((n, cur_level + 1));
                };
                if let Some(n) = z.0.as_ref().borrow_mut().right.take() {
                    qu.push_back((n, cur_level + 1));
                };
            }
            if cur_count != 0 {
                v.push(cur_sum / f64::from(cur_count));
            }
        }
        v
    }
}

#[cfg(test)]
mod tests {
    use super::super::leetcode_binary_tree::build_binary_tree;
    use std::usize;

    use super::*;

    #[test]
    fn case1_test() {
        let r1 =
            vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = [3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }

    #[test]
    fn case2_test() {
        let r1 = vec![Some(3), Some(9), Some(20), Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = [3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }

    #[test]
    fn case3_test() {
        let r1 =
            vec![Some(3), Some(9), Some(20), None, None, Some(15), Some(7)];
        let t1 = build_binary_tree(&r1);
        let output = [3.00000, 14.50000, 11.00000];
        let ret = Solution::average_of_levels(t1);
        let mut i = 0;
        for j in ret {
            assert!((j - output[i as usize]).abs() < std::f64::EPSILON);
            i += 1;
        }

        assert_eq!(i, output.len() as i32);
    }
}
