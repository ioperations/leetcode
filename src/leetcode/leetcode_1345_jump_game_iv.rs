// Given an array of integers arr, you are initially positioned at the first
// index of the array. In one step you can jump from index i to index:
// i + 1 where: i + 1 < arr.length.
// i - 1 where: i - 1 >= 0.
// j where: arr[i] == arr[j] and i != j.
// Return the minimum number of steps to reach the last index of the array.
// Notice that you can not jump outside of the array at any time.

#[allow(unused)]
struct Solution;

use std::collections::{HashMap, HashSet, VecDeque};

impl Solution {
    #[allow(unused)]
    pub fn min_jumps(arr: &[i32]) -> i32 {
        // 1 <= arr.length <= 5 * 104
        // -108 <= arr[i] <= 108

        fn my_impl(
            arr: &[i32],
            current_index: usize,
            cache: &mut HashMap<usize, i32>,
            equal_map: &HashMap<i32, Vec<usize>>,
            steps: &mut HashSet<usize>,
        ) -> i32 {
            let len = arr.len();

            if current_index == len - 1 {
                return steps.len() as i32;
            }

            if let Some(&v) = cache.get(&current_index) {
                return v;
            }

            let mut res = std::i32::MAX;
            if (current_index + 1) < len
                && steps.get(&(current_index + 1)).is_none()
            {
                steps.insert(current_index + 1);
                let case1 =
                    my_impl(arr, current_index + 1, cache, equal_map, steps);
                if case1 < res {
                    res = case1;
                }

                steps.remove(&(current_index + 1));
            }

            if current_index >= 1 && steps.get(&(current_index - 1)).is_none() {
                steps.insert(current_index - 1);
                let case2 =
                    my_impl(arr, current_index - 1, cache, equal_map, steps);
                if case2 < res {
                    res = case2;
                }
                steps.remove(&(current_index - 1));
            }

            for &i in equal_map.get(&arr[current_index]).unwrap() {
                if i != current_index && steps.get(&i).is_none() {
                    steps.insert(i);
                    let case3 = my_impl(arr, i, cache, equal_map, steps);
                    if case3 < res {
                        res = case3;
                    }
                    steps.remove(&i);
                }
            }

            cache.entry(current_index).and_modify(|v| *v = res);

            res
        };

        let mut cache = HashMap::new();
        // equal values to there index
        let equal_map: HashMap<i32, Vec<usize>> = {
            let mut ret = HashMap::new();
            for (i, &v) in arr.iter().enumerate() {
                ret.entry(v)
                    .and_modify(|vec: &mut Vec<usize>| vec.push(i))
                    .or_insert(vec![i]);
            }
            ret
        };
        let mut steps = HashSet::new();

        my_impl(arr, 0, &mut cache, &equal_map, &mut steps)
    }

    #[allow(unused)]
    pub fn min_jumps_dfs(nums: &[i32]) -> i32 {
        let len_n: usize = nums.len();
        if len_n == 1 {
            return 0;
        }
        let mut graph = Self::build_graph(nums);
        let mut queue: VecDeque<usize> = VecDeque::new();
        queue.push_back(0);
        let mut seen: HashSet<usize> = HashSet::new();
        seen.insert(0);
        let mut steps: i32 = 0;
        while !queue.is_empty() {
            let len_q: usize = queue.len();
            for _ in 0..len_q {
                if let Some(cur) = queue.pop_front() {
                    if cur == len_n - 1 {
                        return steps;
                    }
                    if let Some(nxts) = graph.get_mut(&nums[cur]) {
                        if cur >= 1 {
                            nxts.push(cur - 1);
                        }
                        if cur + 1 < len_n {
                            nxts.push(cur + 1);
                        }
                        while let Some(nxt) = nxts.pop() {
                            if seen.insert(nxt) {
                                queue.push_back(nxt);
                            }
                        }
                    };
                }
            }
            steps += 1;
        }
        steps
    }

    #[allow(unused)]
    fn build_graph(nums: &[i32]) -> HashMap<i32, Vec<usize>> {
        let mut graph: HashMap<i32, Vec<usize>> = HashMap::new();
        for (idx, &num) in nums.iter().enumerate() {
            graph.entry(num).or_default().push(idx);
        }
        graph
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let arr = [100, -23, -23, 404, 100, 23, 23, 23, 3, 404];
        let output = 3;
        // Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9.
        // Note that index 9 is the last index of the array.
        let ret = Solution::min_jumps(&arr);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let arr = [7];
        let output = 0;
        // Explanation:
        // Start index is the last index. You do not need to jump.
        let ret = Solution::min_jumps(&arr);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let arr = [7, 6, 9, 6, 9, 6, 9, 7];
        let output = 1;
        // Explanation:
        // Explanation: You can jump directly from index 0 to index 7 which is
        // last index of the array.];
        let ret = Solution::min_jumps(&arr);
        assert_eq!(ret, output);
    }
    use std::{sync::mpsc, thread, time::Duration};

    fn panic_after<T, F>(d: Duration, f: F) -> T
    where
        T: Send + 'static,
        F: FnOnce() -> T,
        F: Send + 'static,
    {
        let (done_tx, done_rx) = mpsc::channel();
        let handle = thread::spawn(move || {
            let val = f();
            done_tx.send(()).expect("Unable to send completion signal");
            val
        });

        match done_rx.recv_timeout(d) {
            Ok(_) => handle.join().expect("Thread panicked"),
            err @ Err(_) => {
                let _ = err.err();
                panic!("Thread took too long",)
            }
        }
    }

    #[should_panic(expected = "Thread took too long")]
    #[test]
    fn case4_test() {
        let test = || {
            let arr = [
                68, -94, -44, -18, -1, 18, -87, 29, -6, -87, -27, 37, -57, 7,
                18, 68, -59, 29, 7, 53, -27, -59, 18, -1, 18, -18, -59, -1,
                -18, -84, -20, 7, 7, -87, -18, -84, -20, -27,
            ];
            let output = 5;
            // Explanation:
            // Explanation: You can jump directly from index 0 to index 7 which
            // is last index of the array.];
            let ret = Solution::min_jumps(&arr);
            assert_eq!(ret, output);
        };
        panic_after(Duration::new(2, 0), test);
    }
}

#[cfg(test)]
mod test_dfs {
    use super::*;

    #[test]
    fn case1_test() {
        let arr = [100, -23, -23, 404, 100, 23, 23, 23, 3, 404];
        let output = 3;
        // Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9.
        // Note that index 9 is the last index of the array.
        let ret = Solution::min_jumps_dfs(&arr);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let arr = [7];
        let output = 0;
        // Explanation:
        // Start index is the last index. You do not need to jump.
        let ret = Solution::min_jumps_dfs(&arr);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let arr = [7, 6, 9, 6, 9, 6, 9, 7];
        let output = 1;
        // Explanation:
        // Explanation: You can jump directly from index 0 to index 7 which is
        // last index of the array.];
        let ret = Solution::min_jumps_dfs(&arr);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let arr = [
            68, -94, -44, -18, -1, 18, -87, 29, -6, -87, -27, 37, -57, 7, 18,
            68, -59, 29, 7, 53, -27, -59, 18, -1, 18, -18, -59, -1, -18, -84,
            -20, 7, 7, -87, -18, -84, -20, -27,
        ];
        let output = 5;
        // Explanation:
        // Explanation: You can jump directly from index 0 to index 7 which is
        // last index of the array.];
        let ret = Solution::min_jumps_dfs(&arr);
        assert_eq!(ret, output);
    }
}
