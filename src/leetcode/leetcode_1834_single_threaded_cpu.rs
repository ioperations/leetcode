/*You are given n tasks labeled from 0 to n - 1 represented by a 2D integer array tasks, where tasks[i] = [enqueueTimei, processingTimei] means that the ith task will be available to process at enqueueTimei and will take processingTimei to finish processing.
You have a single-threaded CPU that can process at most one task at a time and will act in the following way:
If the CPU is idle and there are no available tasks to process, the CPU remains idle.
If the CPU is idle and there are available tasks, the CPU will choose the one with the shortest processing time. If multiple tasks have the same shortest processing time, it will choose the task with the smallest index.
Once a task is started, the CPU will process the entire task without stopping.
The CPU can finish a task then start a new one instantly.
Return the order in which the CPU will process the tasks.*/
use std::cmp::Reverse;
use std::collections::BinaryHeap;

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn get_order(tasks: Vec<Vec<i32>>) -> Vec<i32> {
        let mut tasks: Vec<(usize, i32, i32)> = tasks
            .into_iter()
            .enumerate()
            .map(|(idx, a)| (idx, a[0], a[1]))
            .collect();
        tasks.sort_by_key(|(_, a, _)| *a);
        tasks.reverse();
        let mut cur = 0;
        let mut res = vec![];
        let mut pq: BinaryHeap<Reverse<(i32, usize)>> = BinaryHeap::new();
        while !tasks.is_empty() || !pq.is_empty() {
            if pq.is_empty() {
                // if pq is empty, find smallest num in the tasks, push them into pq
                let task = tasks.pop().unwrap();
                cur = task.1;
                pq.push(Reverse((task.2, task.0)));
                while let Some(task) = tasks.pop() {
                    if task.1 == cur {
                        pq.push(Reverse((task.2, task.0)));
                    } else {
                        tasks.push(task);
                        break;
                    }
                }
            } else {
                // if pq is not empty, consume pq, then push avaiable tasks
                let consumed = pq.pop().unwrap();
                res.push(consumed.0 .1 as i32);
                cur += consumed.0 .0;
                while let Some(task) = tasks.pop() {
                    if task.1 <= cur {
                        pq.push(Reverse((task.2, task.0)));
                    } else {
                        tasks.push(task);
                        break;
                    }
                }
            }
        }
        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let tasks = vec![vec![1, 2], vec![2, 4], vec![3, 2], vec![4, 1]];
        let output = vec![0, 2, 3, 1];
        // Explanation: The events go as follows:
        // - At time = 1, task 0 is available to process. Available tasks = {0}.
        // - Also at time = 1, the idle CPU starts processing task 0. Available tasks = {}.
        // - At time = 2, task 1 is available to process. Available tasks = {1}.
        // - At time = 3, task 2 is available to process. Available tasks = {1, 2}.
        // - Also at time = 3, the CPU finishes task 0 and starts processing task 2 as it is the shortest. Available tasks = {1}.
        // - At time = 4, task 3 is available to process. Available tasks = {1, 3}.
        // - At time = 5, the CPU finishes task 2 and starts processing task 3 as it is the shortest. Available tasks = {1}.
        // - At time = 6, the CPU finishes task 3 and starts processing task 1. Available tasks = {}.
        // - At time = 10, the CPU finishes task 1 and becomes idle.
        let ret = Solution::get_order(tasks);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let tasks = vec![vec![7, 10], vec![7, 12], vec![7, 5], vec![7, 4], vec![7, 2]];
        let output = vec![4, 3, 2, 0, 1];
        let ret = Solution::get_order(tasks);
        // The events go as follows:
        // - At time = 7, all the tasks become available. Available tasks = {0,1,2,3,4}.
        // - Also at time = 7, the idle CPU starts processing task 4. Available tasks = {0,1,2,3}.
        // - At time = 9, the CPU finishes task 4 and starts processing task 3. Available tasks = {0,1,2}.
        // - At time = 13, the CPU finishes task 3 and starts processing task 2. Available tasks = {0,1}.
        // - At time = 18, the CPU finishes task 2 and starts processing task 0. Available tasks = {1}.
        // - At time = 28, the CPU finishes task 0 and starts processing task 1. Available tasks = {}.
        // - At time = 40, the CPU finishes task 1 and becomes idle.
        assert_eq!(ret, output);
    }
}
