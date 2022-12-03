use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn schedule_course(courses: Vec<Vec<i32>>) -> i32 {
        let mut courses = courses;
        courses.sort_by_cached_key(|v| v[1]);
        let mut bh = BinaryHeap::new();
        let mut total = 0;
        for course in &courses {
            bh.push(course[0]);
            total += course[0];
            if total > course[1] {
                if let Some(max) = bh.pop() {
                    total -= max;
                }
            }
        }
        bh.len() as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let courses = vec![
            vec![100, 200],
            vec![200, 1300],
            vec![1000, 1250],
            vec![2000, 3200],
        ];
        let output = 3;
        let ret = Solution::schedule_course(courses);
        assert_eq!(ret, output);
        // There are totally 4 courses, but you can take 3 courses at most:
        // First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
        // Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day.
        // Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day.
        // The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
    }

    #[test]
    fn case2_test() {
        let courses = vec![vec![1, 2]];
        let output = 1;
        let ret = Solution::schedule_course(courses);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let courses = vec![vec![3, 2], vec![4, 3]];
        let output = 0;
        let ret = Solution::schedule_course(courses);
        assert_eq!(ret, output);
    }
}
