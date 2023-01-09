/*You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security systems connected and it will automatically contact the police if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, return the maximum amount of money you can rob tonight without alerting the police.*/

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn rob(nums: Vec<i32>) -> i32 {
        // 1 <= nums.length <= 100
        // 0 <= nums[i] <= 400
        let len = nums.len();
        let mut nums = nums;

        if len < 2 {
            return *nums.iter().max().unwrap();
        }

        (for i in (0..len).rev() {
            if i < (len - 2) {
                nums[i] += *nums[(i + 2)..len].iter().max().unwrap();
            }
        });
        *nums.iter().max().unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 1];
        let output = 4;
        // Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
        // Total amount you can rob = 1 + 3 = 4.
        let ret = Solution::rob(nums.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [2, 7, 9, 3, 1];
        let output = 12;
        // Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
        // Total amount you can rob = 2 + 9 + 1 = 12.
        let ret = Solution::rob(nums.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [0];
        let output = 0;
        // Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
        // Total amount you can rob = 2 + 9 + 1 = 12.
        let ret = Solution::rob(nums.into());
        assert_eq!(ret, output);
    }
}
