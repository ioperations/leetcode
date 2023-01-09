/*Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.*/

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn permute(nums: Vec<i32>) -> Vec<Vec<i32>> {
        fn backtrack(nums: &[i32], sub: &[i32], res: &mut Vec<Vec<i32>>) {
            if nums.is_empty() {
                res.push(sub.to_vec());
                return;
            }
            for (i, v) in nums.iter().enumerate() {
                let (mut nums_c, mut sub_c) = (nums.to_vec(), sub.to_vec());
                nums_c.remove(i);
                sub_c.push(*v);
                backtrack(&nums_c, &sub_c, res);
            }
        }
        let mut res: Vec<Vec<i32>> = vec![];
        backtrack(&nums, &[], &mut res);
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![1, 2, 3];
        let output = vec![
            vec![1, 2, 3],
            vec![1, 3, 2],
            vec![2, 1, 3],
            vec![2, 3, 1],
            vec![3, 1, 2],
            vec![3, 2, 1],
        ];
        let ret = Solution::permute(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = vec![0, 1];
        let output = vec![vec![0, 1], vec![1, 0]];
        let ret = Solution::permute(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = vec![1];
        let output = vec![vec![1]];
        let ret = Solution::permute(nums);
        assert_eq!(ret, output);
    }
}
