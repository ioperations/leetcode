/* Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.*/
extern crate test;

use std::collections::VecDeque;
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn largest_rectangle_area(heights: &[i32]) -> i32 {
        // 1 <= heights.len() <= 10^5
        // 0 <= heights[i] <= 10^4
        Self::max_area(heights)
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

    // @author: Leon
    // https://leetcode.com/problems/largest-rectangle-in-histogram/
    // Time Complexity:    O(`len_hts`)
    // Space Complexity:   O(`len_hts`)
    #[allow(unused)]
    pub fn largest_rectangle_area_v2(heights: &[i32]) -> i32 {
        let len_hts: usize = heights.len();
        let mut stk: VecDeque<usize> = VecDeque::new();
        let mut largest: i32 = 0;
        let mut idx: usize = 0;
        while idx < len_hts {
            while !stk.is_empty() && heights[idx] < heights[*stk.back().unwrap()] {
                let shortest = heights[stk.pop_back().unwrap()];
                let width = (idx
                    - if stk.is_empty() {
                        0
                    } else {
                        stk.back().unwrap() + 1
                    }) as i32;
                let area = shortest * width;
                largest = std::cmp::max(largest, area);
            }
            stk.push_back(idx);
            idx += 1;
        }
        while !stk.is_empty() {
            let shortest = heights[stk.pop_back().unwrap()];
            let width = (len_hts
                - if stk.is_empty() {
                    0
                } else {
                    stk.back().unwrap() + 1
                }) as i32;
            let area = shortest * width;
            largest = std::cmp::max(largest, area);
        }
        largest
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
        let ret = Solution::largest_rectangle_area(&heights);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let heights = [2, 4];
        let output = 4;
        let ret = Solution::largest_rectangle_area(&heights);
        assert_eq!(ret, output);
    }
    #[test]
    fn case3_test() {
        let heights = [2, 1, 5, 6, 2, 3];
        let output = 10;
        /*
        Explanation: The above is a histogram where width of each bar is 1.
        The largest rectangle is shown in the red area, which has an area = 10 units.
        */
        let ret = Solution::largest_rectangle_area_v2(&heights);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let heights = [2, 4];
        let output = 4;
        let ret = Solution::largest_rectangle_area_v2(&heights);
        assert_eq!(ret, output);
    }

    #[bench]
    fn case1(b: &mut test::Bencher) {
        let heights = [2, 1, 5, 6, 2, 3];
        b.iter(|| {
            Solution::largest_rectangle_area(&heights);
        })
    }

    #[bench]
    fn case2(b: &mut test::Bencher) {
        let heights = [2, 1, 5, 6, 2, 3];
        b.iter(|| {
            Solution::largest_rectangle_area_v2(&heights);
        })
    }
}
