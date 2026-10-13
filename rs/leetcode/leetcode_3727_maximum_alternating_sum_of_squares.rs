// You are given an integer array nums. You may rearrange the elements in any
// order.
//
// The alternating score of an array arr is defined as:
//
// score = arr[0]2 - arr[1]2 + arr[2]2 - arr[3]2 + ...
// Return an integer denoting the maximum possible alternating score of nums
// after rearranging its elements.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_alternating_sum(nums: &[i32]) -> i64 {
        let mut v: Vec<_> =
            nums.iter().map(|&v| (v as i64) * (v as i64)).collect();

        v.sort_unstable();

        let half = v.len() / 2;

        v.iter().skip(half).sum::<i64>() - v.iter().take(half).sum::<i64>()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 2, 3];
        let output = 12;
        let ret = Solution::max_alternating_sum(&nums);
        assert_eq!(output, ret);
        // A possible rearrangement for nums is [2,1,3], which gives the maximum
        // alternating score among all possible rearrangements.
        //
        // The alternating score is calculated as:
        //
        // score = 22 - 12 + 32 = 4 - 1 + 9 = 12
    }

    #[test]
    fn case2_test() {
        let nums = [1, -1, 2, -2, 3, -3];
        let output = 16;
        let ret = Solution::max_alternating_sum(&nums);
        assert_eq!(output, ret);
        // A possible rearrangement for nums is [-3,-1,-2,1,3,2], which gives
        // the maximum alternating score among all possible rearrangements.
        //
        // The alternating score is calculated as:
        //
        // score = (-3)2 - (-1)2 + (-2)2 - (1)2 + (3)2 - (2)2 = 9 - 1 + 4 - 1 +
        // 9 - 4 = 16
    }
}
