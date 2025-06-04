// You are given an array of non-overlapping intervals intervals where
// intervals[i] = [starti, endi] represent the start and the end of the ith
// interval and intervals is sorted in ascending order by starti.
// You are also given an interval newInterval = [start, end] that
// represents the start and end of another interval.
// Insert newInterval into intervals such that intervals is still sorted
// in ascending order by starti and intervals still does not
// have any overlapping intervals (merge overlapping intervals if necessary).
// Return intervals after the insertion.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn insert(
        intervals: &[Vec<i32>],
        new_interval: Vec<i32>,
    ) -> Vec<Vec<i32>> {
        let mut answer: Vec<Vec<i32>> = Vec::with_capacity(intervals.len() + 1);
        let mut i = 0;
        while i < intervals.len() && intervals[i][1] < new_interval[0] {
            answer.push(intervals[i].clone());
            i += 1;
        }
        let mut new_interval = new_interval;
        while i < intervals.len() && intervals[i][0] <= new_interval[1] {
            new_interval[0] = std::cmp::min(new_interval[0], intervals[i][0]);
            new_interval[1] = std::cmp::max(new_interval[1], intervals[i][1]);
            i += 1;
        }
        answer.push(new_interval);
        while i < intervals.len() {
            answer.push(intervals[i].clone());
            i += 1;
        }
        answer
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let intervals = [vec![1, 3], vec![6, 9]];
        let new_interval = [3, 5];
        let output = [vec![1, 5], vec![6, 9]];
        let ret = Solution::insert(&intervals, new_interval.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let intervals = [
            vec![1, 2],
            vec![3, 5],
            vec![6, 7],
            vec![8, 10],
            vec![12, 16],
        ];
        let new_interval = [4, 8];
        let output = [vec![1, 2], vec![3, 10], vec![12, 16]];
        let ret = Solution::insert(&intervals, new_interval.into());
        // Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].
        assert_eq!(ret, output);
    }
}
