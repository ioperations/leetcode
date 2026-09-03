// You are given an array nums1 of n distinct integers.
//
// You want to construct another array nums2 of length n such that the elements
// in nums2 are either all odd or all even.
//
// For each index i, you must choose exactly one of the following (in any
// order):
//
// nums2[i] = nums1[i]
// nums2[i] = nums1[i] - nums1[j], for an index j != i, such that nums1[i] -
// nums1[j] >= 1 Return true if it is possible to construct such an array,
// otherwise return false.

// 1 <= n == nums1.length <= 105
// 1 <= nums1[i] <= 109
// nums1 consists of distinct integers.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn uniform_array(nums1: &[i32]) -> bool {
        // odd  奇数
        // even 偶数
        let smallest_odd = nums1.iter().filter(|&&v| v % 2 == 1).min();

        let all_odd = nums1
            .iter()
            .all(|&v| {
                v % 2 == 1
                    || (smallest_odd.is_some() && v > *smallest_odd.unwrap())
            })
            .to_owned();

        if all_odd {
            return true;
        }

        smallest_odd.is_none()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let num1 = [1, 4, 7];
        let output = true;
        let ret = Solution::uniform_array(&num1);
        assert_eq!(output, ret);
        // Set nums2[0] = nums1[0] = 1.
        // Set nums2[1] = nums1[1] - nums1[0] = 4 - 1 = 3.
        // Set nums2[2] = nums1[2] = 7.
        // nums2 = [1, 3, 7], and all elements are odd. Thus, the answer is
        // true.
    }

    #[test]
    fn case2_test() {
        let num1 = [2, 3];
        let output = false;
        let ret = Solution::uniform_array(&num1);
        assert_eq!(output, ret);
        // It is not possible to construct nums2 such that all elements have the
        // same parity. Thus, the answer is false.
    }

    #[test]
    fn case3_test() {
        let num1 = [4, 6];
        let output = true;
        let ret = Solution::uniform_array(&num1);
        assert_eq!(output, ret);
        // Set nums2[0] = nums1[0] = 4.
        // Set nums2[1] = nums1[1] = 6.
        // nums2 = [4, 6], and all elements are even. Thus, the answer is true.
        //
    }
}
