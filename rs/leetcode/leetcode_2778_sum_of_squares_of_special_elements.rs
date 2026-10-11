// You are given a 1-indexed integer array nums of length n.
//
// An element nums[i] of nums is called special if i divides n, i.e. n % i == 0.
//
// Return the sum of the squares of all special elements of nums.
//
//
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn sum_of_squares(nums: &[i32]) -> i32 {
        let len = nums.len();
        nums.iter()
            .enumerate()
            .filter(|(idx, value)| len % (*idx + 1) == 0)
            .map(|(idx, value)| value * value)
            .sum()
    }
}

#[cfg(test)]
mod tests {

    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3, 4].to_vec();
        let output = 21;
        let ret = Solution::sum_of_squares(&nums);
        assert_eq!(output, ret);
        //  There are exactly 3 special elements in nums: nums[1] since 1
        // divides 4, nums[2] since 2 divides 4, and nums[4] since 4 divides 4.
        // Hence, the sum of the squares of all special elements of nums is
        // nums[1] * nums[1] + nums[2] * nums[2] + nums[4] * nums[4] = 1 * 1 + 2
        // * 2 + 4 * 4 = 21.
    }

    #[test]
    fn case2_test() {
        let nums = [2, 7, 1, 19, 18, 3].to_vec();
        let output = 63;
        let ret = Solution::sum_of_squares(&nums);
        assert_eq!(output, ret);
        // Explanation: There are exactly 4 special elements in nums: nums[1]
        // since 1 divides 6, nums[2] since 2 divides 6, nums[3] since 3 divides
        // 6, and nums[6] since 6 divides 6. Hence, the sum of the
        // squares of all special elements of nums is nums[1] * nums[1] +
        // nums[2] * nums[2] + nums[3] * nums[3] + nums[6] * nums[6] = 2 * 2 + 7
        // * 7 + 1 * 1 + 3 * 3 = 63.
        //
    }
}
