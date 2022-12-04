/* Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.*/
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn largest_rectangle_area(heights: Vec<i32>) -> i32 {
        // 1 <= heights.len() <= 10^5
        // 0 <= heights[i] <= 10^4
        Self::max_area(&heights)
    }

    #[allow(unused)]
    fn max_area(heights: &[i32]) -> i32 {
        let n = heights.len();
        if n == 0 {
            return 0;
        }
        if n == 1 {
            return heights[0];
        }

        let i = 0;
        let j = n - 1;
        let pivot = {
            let mut res = (i + j) / 2;
            for i in 0..n {
                if heights[i] < heights[res] {
                    res = i;
                }
            }
            res
        };
        let mut res = heights[pivot] * (j - i + 1) as i32;
        res = res.max(Self::max_area(&heights[i..pivot]));
        res = res.max(Self::max_area(&heights[(pivot + 1)..=j]));
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let heights = [2, 1, 5, 6, 2, 3];
        let output = 10;
        /*
        Explanation: The above is a histogram where width of each bar is 1.
        The largest rectangle is shown in the red area, which has an area = 10 units.
        */
        let ret = Solution::largest_rectangle_area(heights.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let heights = [2, 4];
        let output = 4;
        let ret = Solution::largest_rectangle_area(heights.into());
        assert_eq!(ret, output);
    }
}
