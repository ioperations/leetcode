/*
 * You are given a 0-indexed integer array tasks,
 * where tasks[i] represents the difficulty level of a task.
 * In each round, you can complete either 2 or 3 tasks of the same difficulty level.
 * Return the minimum rounds required to complete all the tasks,
 * or -1 if it is not possible to complete all the tasks.
 */

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn minimum_rounds(tasks: Vec<i32>) -> i32 {
        fn calculate_times(i: i32) -> Option<i32> {
            match i {
                0 | 1 => None,
                2 | 3 => Some(1),
                4 => Some(2),
                v => match v % 3 {
                    0 => Some(v / 3),
                    _ => Some(v / 3 + 1),
                },
            }
        };

        #[cfg(test)]
        {
            // 1 <= tasks.length <= 105
            // 1 <= tasks[i] <= 109
            assert!(!tasks.is_empty() && tasks.len() < 100_000);
            for v in &tasks {
                assert!((1..=1_000_000_000).contains(v));
            }
        }

        let mut tasks = tasks;
        tasks.sort_unstable();
        let tasks: Vec<usize> = tasks.group_by(|a, b| a == b).map(<[i32]>::len).collect();

        let mut i: i32 = 0;
        for v in tasks {
            if let Some(v) = calculate_times(v as i32) {
                i += v;
            } else {
                return -1;
            }
        }
        i
    }

    #[allow(unused)]
    pub fn minimum_rounds_v2(tasks: Vec<i32>) -> i32 {
        // 1 <= tasks.length <= 105
        // 1 <= tasks[i] <= 109
        fn calculate_times(i: i32) -> Option<i32> {
            match i {
                0 | 1 => None,
                2 | 3 => Some(1),
                4 => Some(2),
                v => match v % 3 {
                    0 => Some(v / 3),
                    _ => Some(v / 3 + 1),
                },
            }
        };
        use std::collections::HashMap;

        #[cfg(test)]
        {
            assert!(!tasks.is_empty() && tasks.len() < 100_000);
            for v in &tasks {
                assert!((1..=1_000_000_000).contains(v));
            }
        }

        let tasks: Vec<i32> = {
            let mut hash = HashMap::new();
            for v in tasks {
                hash.entry(v).and_modify(|k| *k += 1).or_insert(1);
            }
            hash.values().copied().collect()
        };

        let mut i: i32 = 0;
        for v in tasks {
            if let Some(v) = calculate_times(v) {
                i += v;
            } else {
                return -1;
            }
        }
        i
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let tasks = [2, 2, 3, 3, 2, 4, 4, 4, 4, 4];
        let output = 4;
        /*
         * Explanation: To complete all the tasks, a possible plan is:
         * - In the first round, you complete 3 tasks of difficulty level 2.
         * - In the second round, you complete 2 tasks of difficulty level 3.
         * - In the third round, you complete 3 tasks of difficulty level 4.
         * - In the fourth round, you complete 2 tasks of difficulty level 4.
         * It can be shown that all the tasks cannot be completed in fewer than 4 rounds, so the answer is 4.
         */
        let ret = Solution::minimum_rounds(tasks.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let tasks = [2, 3, 3];
        let output = -1;
        /*
         * There is only 1 task of difficulty level 2, but in each round, you can only complete either 2 or 3 tasks of the same difficulty level. Hence, you cannot complete all the tasks, and the answer is -1.
         */
        let ret = Solution::minimum_rounds(tasks.into());
        assert_eq!(ret, output);
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn case1_test() {
        let tasks = [2, 2, 3, 3, 2, 4, 4, 4, 4, 4];
        let output = 4;
        /*
         * Explanation: To complete all the tasks, a possible plan is:
         * - In the first round, you complete 3 tasks of difficulty level 2.
         * - In the second round, you complete 2 tasks of difficulty level 3.
         * - In the third round, you complete 3 tasks of difficulty level 4.
         * - In the fourth round, you complete 2 tasks of difficulty level 4.
         * It can be shown that all the tasks cannot be completed in fewer than 4 rounds, so the answer is 4.
         */
        let ret = Solution::minimum_rounds_v2(tasks.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let tasks = [2, 3, 3];
        let output = -1;
        /*
         * There is only 1 task of difficulty level 2, but in each round, you can only complete either 2 or 3 tasks of the same difficulty level. Hence, you cannot complete all the tasks, and the answer is -1.
         */
        let ret = Solution::minimum_rounds_v2(tasks.into());
        assert_eq!(ret, output);
    }
}
