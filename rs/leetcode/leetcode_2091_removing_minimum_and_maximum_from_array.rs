// You are given a 0-indexed array of distinct integers nums.
//
// There is an element in nums that has the lowest value and an element that has
// the highest value. We call them the minimum and maximum respectively. Your
// goal is to remove both these elements from the array.
//
// A deletion is defined as either removing an element from the front of the
// array or removing an element from the back of the array.
//
// Return the minimum number of deletions it would take to remove both the
// minimum and maximum element from the array.
//
// 1 <= nums.length <= 105
// -105 <= nums[i] <= 105
// The integers in nums are distinct.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn minimum_deletions(nums: &[i32]) -> i32 {
        let mut min = (i32::MAX, 0);
        let mut max = (i32::MIN, 0);

        for (i, &v) in nums.iter().enumerate() {
            if v <= min.0 {
                min.1 = i;
                min.0 = v;
            }

            if v >= max.0 {
                max.0 = v;
                max.1 = i;
            }
        }

        let len = nums.len();

        let mut ret = 0;

        let x_min = min.1.min(max.1);
        let y_max = min.1.max(max.1);

        let x = x_min + 1;
        let y = y_max - x_min;
        let z = len - y_max;

        (x + y).min(y + z).min(x + z) as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![2, 10, 7, 5, 4, 1, 8, 6];
        let output = 5;
        // The minimum element in the array is nums[5], which is 1.
        // The maximum element in the array is nums[1], which is 10.
        // We can remove both the minimum and maximum by removing 2 elements
        // from the front and 3 elements from the back. This results in
        // 2 + 3 = 5 deletions, which is the minimum number possible.

        let ret = Solution::minimum_deletions(&nums);
        assert_eq!(output, ret);
    }

    #[test]
    fn case2_test() {
        let nums = vec![0, -4, 19, 1, 8, -2, -3, 5];
        let output = 3;
        // The minimum element in the array is nums[1], which is -4.
        // The maximum element in the array is nums[2], which is 19.
        // We can remove both the minimum and maximum by removing 3 elements
        // from the front. This results in only 3 deletions, which is
        // the minimum number possible.
        //

        let ret = Solution::minimum_deletions(&nums);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let nums = vec![101];
        let output = 1;
        // There is only one element in the array, which makes it both the
        // minimum and maximum element. We can remove it with 1
        // deletion.

        let ret = Solution::minimum_deletions(&nums);
        assert_eq!(output, ret);
    }
}
