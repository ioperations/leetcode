// Given a circular integer array nums of length n, return the maximum possible
// sum of a non-empty subarray of nums. A circular array means the end of the
// array connects to the beginning of the array. Formally, the next element of
// nums[i] is nums[(i + 1) % n] and the previous element of nums[i] is nums[(i -
// 1 + n) % n]. A subarray may only include each element of the fixed buffer
// nums at most once. Formally, for a subarray nums[i], nums[i + 1], ...,
// nums[j], there does not exist i <= k1, k2 <= j with k1 % n == k2 % n.
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn max_subarray_sum_circular(nums: &[i32]) -> i32 {
        let n = nums.len();
        let mut dp_max = vec![0; n];
        let mut dp_min = vec![0; n];

        let mut max = nums[0];
        let mut min = nums[0];
        let mut total = nums[0];

        dp_max[0] = nums[0];
        dp_min[0] = nums[0];

        for i in 1..n {
            dp_max[i] = std::cmp::max(dp_max[i - 1] + nums[i], nums[i]);
            dp_min[i] = std::cmp::min(dp_min[i - 1] + nums[i], nums[i]);

            max = std::cmp::max(max, dp_max[i]);
            min = std::cmp::min(min, dp_min[i]);

            total += nums[i];
        }

        if max > 0 {
            std::cmp::max(max, total - min)
        } else {
            max
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, -2, 3, -2];
        let output = 3;
        // Explanation: Subarray [3] has maximum sum 3.
        let ret = Solution::max_subarray_sum_circular(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [5, -3, 5];
        let output = 10;
        // Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.
        let ret = Solution::max_subarray_sum_circular(&nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = [-3, -2, -3];
        let output = -2;
        // Subarray [-2] has maximum sum -2.
        let ret = Solution::max_subarray_sum_circular(&nums);
        assert_eq!(ret, output);
    }
}
