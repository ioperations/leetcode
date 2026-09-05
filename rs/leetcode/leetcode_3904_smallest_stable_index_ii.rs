// You are given an integer array nums of length n and an integer k.
//
// For each index i, define its instability score as max(nums[0..i]) -
// min(nums[i..n - 1]).
//
// In other words:
//
// max(nums[0..i]) is the largest value among the elements from index 0 to index
// i. min(nums[i..n - 1]) is the smallest value among the elements from index i
// to index n - 1. An index i is called stable if its instability score is less
// than or equal to k.
//
// Return the smallest stable index. If no such index exists, return -1.
//
// 1 <= nums.length <= 105
// 0 <= nums[i] <= 109
// 0 <= k <= 109

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn first_stable_index(nums: &[i32], k: i32) -> i32 {
        // Hint 1
        // Precompute prefix maximums in an array prefMax, where prefMax[i] is
        // the maximum of nums[0..i]
        //
        // Hint 2
        // Precompute suffix minimums in an array suffMin, where suffMin[i] is
        // the minimum of nums[i..n-1]
        //
        // Hint 3
        // For each index i, compute the instability score as prefMax[i] -
        // suffMin[i]
        //
        // Hint 4
        // Return the smallest index where the instability score is <= k. If no
        // such index exists, return -1
        let len = nums.len();

        let mut prefix_max = vec![0; len];
        let mut max = i32::MIN;
        for (idx, &v) in nums.iter().enumerate() {
            if v > max {
                max = v;
            }

            prefix_max[idx] = max;
        }

        let mut prefix_min = vec![0; len];
        let mut min = i32::MAX;

        for (idx, &v) in nums.iter().rev().enumerate() {
            if v < min {
                min = v;
            }
            prefix_min[len - 1 - idx] = min;
        }

        (0..len)
            .filter_map(|i| {
                let v = prefix_max[i] - prefix_min[i];
                if v <= k {
                    return Some(i as i32);
                }
                None
            })
            .take(1)
            .next()
            .unwrap_or(-1)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![5, 0, 1, 4];
        let k = 3;

        let output = 3;
        let ret = Solution::first_stable_index(&nums, k);
        assert_eq!(output, ret);
        // At index 0: The maximum in [5] is 5, and the minimum in [5, 0, 1, 4]
        // is 0, so the instability score is 5 - 0 = 5. At index 1: The
        // maximum in [5, 0] is 5, and the minimum in [0, 1, 4] is 0, so the
        // instability score is 5 - 0 = 5. At index 2: The maximum in
        // [5, 0, 1] is 5, and the minimum in [1, 4] is 1, so the instability
        // score is 5 - 1 = 4. At index 3: The maximum in [5, 0, 1, 4]
        // is 5, and the minimum in [4] is 4, so the instability score is 5 - 4
        // = 1. This is the first index with an instability score less
        // than or equal to k = 3. Thus, the answer is 3.
    }

    #[test]
    fn case2_test() {
        let nums = vec![3, 2, 1];
        let k = 1;

        let output = -1;
        let ret = Solution::first_stable_index(&nums, k);
        assert_eq!(output, ret);
        // At index 0, the instability score is 3 - 1 = 2.
        // At index 1, the instability score is 3 - 1 = 2.
        // At index 2, the instability score is 3 - 1 = 2.
        // None of these values is less than or equal to k = 1, so the answer is
        // -1.
    }

    #[test]
    fn case3_test() {
        let nums = vec![0];
        let k = 0;

        let output = 0;
        let ret = Solution::first_stable_index(&nums, k);
        assert_eq!(output, ret);
        // At index 0, the instability score is 0 - 0 = 0, which is less than or
        // equal to k = 0. Therefore, the answer is 0.
    }

    #[test]
    fn case4_test() {
        let nums = vec![2, 0, 2];
        let k = 3;

        let output = 0;
        let ret = Solution::first_stable_index(&nums, k);
        assert_eq!(output, ret);
        // At index 0, the instability score is 0 - 0 = 0, which is less than or
        // equal to k = 0. Therefore, the answer is 0.
    }
}
