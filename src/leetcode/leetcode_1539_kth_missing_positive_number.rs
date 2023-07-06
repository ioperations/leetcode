// Given an array arr of positive integers sorted in a strictly increasing
// order, and an integer k.
//
// Return the kth positive integer that is missing from this array.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_kth_positive(arr: &[i32], k: i32) -> i32 {
        // 1 <= arr.length <= 1000
        // 1 <= arr[i] <= 1000
        // 1 <= k <= 1000
        // arr[i] < arr[j] for 1 <= i < j <= arr.length
        fn my_impl(arr: &[i32], k: i32) -> i32 {
            let mut left = Vec::new();
            let mut expected = 1;

            for &i in arr {
                if i == expected {
                    expected += 1;
                    continue;
                }
                for j in (expected..i) {
                    left.push(j);
                    let len = left.len();
                    if k == len as i32 {
                        return left[len - 1];
                    }
                }
                expected = i + 1;
            }
            let len = left.len();
            if len != 0 {
                return arr[arr.len() - 1] + (k - len as i32);
            }
            arr[arr.len() - 1] + k
        };
        my_impl(arr, k)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let arr = [2, 3, 4, 7, 11];
        let k = 5;
        let output = 9;
        // Explanation: The missing positive integers are
        // [1,5,6,8,9,10,12,13,...]. The 5th missing positive integer is 9.
        let ret = Solution::find_kth_positive(&arr, k);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let arr = [1, 2, 3, 4];
        let k = 2;
        let output = 6;
        // Explanation:
        // The missing positive integers are [5,6,7,...]. The 2nd missing
        // positive integer is 6.
        let ret = Solution::find_kth_positive(&arr, k);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let arr: Vec<_> = (1..).take(1000).collect();
        let k = 2;
        let output = 1002;
        // Explanation:
        // The missing positive integers are [5,6,7,...]. The 2nd missing
        // positive integer is 6.
        let ret = Solution::find_kth_positive(&arr, k);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let arr = [5, 6, 7, 8, 9];

        let k = 9;
        let output = 14;
        // Explanation:
        // positive integer is 6.
        let ret = Solution::find_kth_positive(&arr, k);
        assert_eq!(ret, output);
    }

    #[test]
    fn case5_test() {
        let arr = [5, 10, 11, 12];

        let k = 5;
        let output = 6;
        // Explanation:
        // positive integer is 6.
        let ret = Solution::find_kth_positive(&arr, k);
        assert_eq!(ret, output);
    }
}
