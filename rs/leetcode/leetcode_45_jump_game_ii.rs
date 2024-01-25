// You are given a 0-indexed array of integers nums of length n. You are
// initially positioned at nums[0]. Each element nums[i] represents the maximum
// length of a forward jump from index i. In other words, if you are at nums[i],
// you can jump to any nums[i + j] where: 0 <= j <= nums[i] and
// i + j < n
// Return the minimum number of jumps to reach nums[n - 1]. The test cases are
// generated such that you can reach nums[n - 1].

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn jump(nums: &[i32]) -> i32 {
        let (mut jumps, mut curr_end, mut furthest) = (0, 0, 0);

        #[allow(clippy::needless_range_loop)]
        for i in 0..nums.len() - 1 {
            furthest = (nums[i] as usize + i).max(furthest);

            if i == curr_end {
                curr_end = furthest;
                jumps += 1;
            }
        }

        jumps
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [2, 3, 1, 1, 4];
        let output = 2;

        // Explanation: The minimum number of jumps to reach the last index is
        // 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
        let ret = Solution::jump(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [2, 3, 0, 1, 4];
        let output = 2;

        // Explanation: The minimum number of jumps to reach the last index is
        // 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
        let ret = Solution::jump(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [0];
        let output = 0;

        let ret = Solution::jump(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let nums = [2, 1];
        let output = 1;

        let ret = Solution::jump(&nums);
        assert_eq!(ret, output);
    }
}
