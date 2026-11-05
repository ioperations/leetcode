// Given two integer arrays arr1 and arr2, and the integer d, return the
// distance value between the two arrays.
//
// The distance value is defined as the number of elements arr1[i] such that
// there is not any element arr2[j] where |arr1[i]-arr2[j]| <= d.

struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_the_distance_value(
        arr1: &[i32],
        arr2: Vec<i32>,
        d: i32,
    ) -> i32 {
        let mut arr2 = arr2;
        arr2.sort_unstable();

        arr1.iter()
            .filter(|&&x| {
                let p = arr2.binary_search(&x).unwrap_or_else(|i| i);
                (p >= arr2.len() || arr2[p] - x > d)
                    && (p == 0 || x - arr2[p - 1] > d)
            })
            .count() as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let arr1 = [4, 5, 8];
        let arr2 = [10, 9, 1, 8];
        let d = 2;
        let output = 2;
        let ret = Solution::find_the_distance_value(&arr1, arr2.to_vec(), d);
        assert_eq!(output, ret);
        // Explanation:
        // For arr1[0]=4 we have:
        // |4-10|=6 > d=2
        // |4-9|=5 > d=2
        // |4-1|=3 > d=2
        // |4-8|=4 > d=2
        // For arr1[1]=5 we have:
        // |5-10|=5 > d=2
        // |5-9|=4 > d=2
        // |5-1|=4 > d=2
        // |5-8|=3 > d=2
        // For arr1[2]=8 we have:
        // |8-10|=2 <= d=2
        // |8-9|=1 <= d=2
        // |8-1|=7 > d=2
        // |8-8|=0 <= d=2
    }

    #[test]
    fn case2_test() {
        let arr1 = [1, 4, 2, 3];
        let arr2 = [-4, -3, 6, 10, 20, 30];
        let d = 3;
        let output = 2;
        let ret = Solution::find_the_distance_value(&arr1, arr2.to_vec(), d);
        assert_eq!(output, ret);
    }

    #[test]
    fn case3_test() {
        let arr1 = [2, 1, 100, 3];
        let arr2 = [-5, -2, 10, -3, 7];
        let d = 6;
        let output = 1;
        let ret = Solution::find_the_distance_value(&arr1, arr2.to_vec(), d);
        assert_eq!(output, ret);
    }
}
