// You are given an integer array nums and two integers minK and maxK.
// A fixed-bound subarray of nums is a subarray that satisfies the following
// conditions: The minimum value in the subarray is equal to minK.
// The maximum value in the subarray is equal to maxK.
// Return the number of fixed-bound subarrays.

// A subarray is a contiguous part of an array.
#![allow(unused)]
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn count_subarrays(nums: &[i32], min_k: i32, max_k: i32) -> i64 {
        // 2 <= nums.length <= 105
        // 1 <= nums[i], minK, maxK <= 106
        let mut l = 0;
        let mut r = 0;
        let n = nums.len();

        let mut ans = 0i64;
        // count subarray in range [l, r)
        // which value in that satisfy: min_k <= value <= max_k
        let mut my_impl = |left, right| -> i64 {
            let mut min_count = 0;
            let mut max_count = 0;
            let mut l = left;
            let mut pairs = 0i64;

            for r in left..right {
                if nums[r] == min_k {
                    min_count += 1;

                    // if range [l, r] has both min_k and max_k
                    if max_count > 0 {
                        // while r keeps moving right, it still satisfy the
                        // limitation,
                        // so calculate all them directly
                        let t = (right - r) as i64;

                        let mut cnt = 0;
                        // increase l to shrink the range to get more range
                        // pairs
                        while l < r && max_count > 0 {
                            cnt += 1;
                            if nums[l] == max_k {
                                max_count -= 1;
                            }
                            l += 1;
                        }
                        pairs += cnt * t;
                    }
                } else if nums[r] == max_k {
                    // same as above with little difference
                    max_count += 1;
                    if min_count > 0 {
                        let t = (right - r) as i64;
                        let mut cnt = 0;
                        while l < r && min_count > 0 {
                            cnt += 1;
                            if nums[l] == min_k {
                                min_count -= 1;
                            }
                            l += 1;
                        }
                        pairs += cnt * t;
                    }
                }
            }
            pairs
        };

        loop {
            while l < n && (nums[l] > max_k || nums[l] < min_k) {
                l += 1;
            }
            if l >= n {
                break;
            }

            r = l;
            let mut min = nums[l];
            let mut max = nums[r];
            while r < n && nums[r] <= max_k && nums[r] >= min_k {
                min = min.min(nums[r]);
                max = max.max(nums[r]);
                r += 1;
            }
            if min == min_k && max == max_k {
                if min_k == max_k {
                    let t = (r - l) as i64;
                    ans += (t + 1) * t / 2;
                } else {
                    ans += my_impl(l, r); // check range [l, r)
                }
            }
            l = r + 1;
        }
        ans
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let nums = [1, 3, 5, 2, 7, 5];
        let min_k = 1;
        let max_k = 5;
        let output = 2;
        // Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
        let ret = Solution::count_subarrays(&nums, min_k, max_k);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let nums = [1, 1, 1, 1];
        let min_k = 1;
        let max_k = 1;
        let output = 10;
        // Every subarray of nums is a fixed-bound subarray. There are 10
        // possible subarrays.
        let ret = Solution::count_subarrays(&nums, min_k, max_k);
        assert_eq!(ret, output);
    }
}
