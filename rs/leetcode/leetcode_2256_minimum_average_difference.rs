// You are given a 0-indexed integer array nums of length n.
//
// The average difference of the index i is the absolute difference between
// the average of the first i + 1 elements of nums and the average of the last n
// - i - 1 elements. Both averages should be rounded down to the nearest
// integer. Return the index with the minimum average difference.
// If there are multiple such indices, return the smallest one.
//
// Note:
// The absolute difference of two numbers is the absolute value of their
// difference. The average of n elements is the sum of the n elements divided
// (integer division) by n. The average of 0 elements is considered to be 0.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn minimum_average_difference(nums: Vec<i32>) -> i32 {
        let mut sum: i64 = 0;
        let mut sum_arr = Vec::with_capacity(nums.len());

        for n in nums {
            sum += n as i64;
            sum_arr.push(sum);
        }

        let mut min = i64::MAX;
        let mut min_index = 0;

        for i in 0..sum_arr.len() {
            let sum_at_index = sum_arr[i];

            let first_avg = sum_at_index / (i as i64 + 1);

            let last_divisor = if (i < sum_arr.len() - 1) {
                sum_arr.len() - i - 1
            } else {
                1
            } as i64;

            let last_avg = (sum - sum_at_index) / last_divisor;

            let avg = (first_avg - last_avg).abs();

            if (avg < min) {
                min = avg;
                min_index = i;
            }
        }
        min_index as i32
    }
}
#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = vec![2, 5, 3, 9, 5, 3];
        let output = 3;
        // The average difference of index 0 is: |2 / 1 - (5 + 3 + 9 + 5 + 3) /
        // 5| = |2 / 1 - 25 / 5| = |2 - 5| = 3.
        // - The average difference of index 1 is: |(2 + 5) / 2 - (3 + 9 + 5 +
        //   3) / 4| = |7 / 2 - 20 / 4| = |3 - 5| = 2.
        // - The average difference of index 2 is: |(2 + 5 + 3) / 3 - (9 + 5 +
        //   3) / 3| = |10 / 3 - 17 / 3| = |3 - 5| = 2.
        // - The average difference of index 3 is: |(2 + 5 + 3 + 9) / 4 - (5 +
        //   3) / 2| = |19 / 4 - 8 / 2| = |4 - 4| = 0.
        // - The average difference of index 4 is: |(2 + 5 + 3 + 9 + 5) / 5 - 3
        //   / 1| = |24 / 5 - 3 / 1| = |4 - 3| = 1.
        // - The average difference of index 5 is: |(2 + 5 + 3 + 9 + 5 + 3) / 6
        //   - 0| = |27 / 6 - 0| = |4 - 0| = 4.
        // The average difference of index 3 is the minimum average difference
        // so return 3.
        let ret = Solution::minimum_average_difference(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = vec![0];
        let output = 0;
        // The only index is 0 so return 0.
        // The average difference of index 0 is: |0 / 1 - 0| = |0 - 0| = 0.
        let ret = Solution::minimum_average_difference(nums);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let nums = vec![4, 2, 0];
        let output = 2;
        let ret = Solution::minimum_average_difference(nums);
        assert_eq!(ret, output);
    }
}
