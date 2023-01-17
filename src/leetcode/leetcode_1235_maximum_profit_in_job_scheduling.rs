// We have n jobs, where every job is scheduled to be done from startTime[i] to
// endTime[i], obtaining a profit of profit[i].
//
// You're given the startTime, endTime and profit arrays,
// return the maximum profit you can take such that there are no two jobs in the
// subset with overlapping time range. If you choose a job that ends at time X
// you will be able to start another job that starts at time X.

#[allow(unused)]
struct Solution;

#[allow(unused)]
struct Context {
    nodes: Vec<Node>,
    len: usize,
}

#[allow(unused)]
struct Node {
    start_time: i32,
    end_time: i32,
    profit: i32,
}

impl Solution {
    #[allow(unused)]
    pub fn job_scheduling(
        start_time: &[i32],
        end_time: &[i32],
        profit: &[i32],
    ) -> i32 {
        //
        let len = start_time.len();
        let mut nodes = vec![];

        for i in 0..len {
            nodes.push(Node {
                start_time: start_time[i],
                end_time: end_time[i],
                profit: profit[i],
            });
        }

        nodes.sort_by_key(|n| n.start_time);

        let context = Context { nodes, len };
        Self::helper(&context, 0, 0, 0)
    }

    // in [start_time] and with [choosen] , how mach profit can we get
    #[allow(unused)]
    pub fn helper(
        context: &Context,
        minimum_start_time: i32,
        job_minimium: usize,
        profit: i32,
    ) -> i32 {
        if job_minimium >= context.len {
            return profit;
        }
        // first get all possible start job
        let mut candidate = vec![];
        {
            for i in job_minimium..context.len {
                if context.nodes[i].start_time >= minimum_start_time {
                    candidate.push(i);
                }
            }
        }

        let mut max = profit;
        for i in candidate {
            // choose the i'th candiate
            max = max.max(Self::helper(
                context,
                context.nodes[i].end_time,
                i + 1,
                profit + context.nodes[i].profit,
            ));
            // do not choose the i'th candidate
            max = max.max(Self::helper(
                context,
                minimum_start_time,
                i + 1,
                profit,
            ));
        }

        max
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let start_time = vec![1, 2, 3, 3];
        let end_time = vec![3, 4, 5, 6];
        let profit = vec![50, 10, 40, 70];
        let output = 120;

        // Explanation: The subset chosen is the first and fourth job.
        // Time range [1-3]+[3-6] , we get profit of 120 = 50 + 70.
        let ret = Solution::job_scheduling(&start_time, &end_time, &profit);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let start_time = vec![1, 2, 3, 4, 6];
        let end_time = vec![3, 5, 10, 6, 9];
        let profit = vec![20, 20, 100, 70, 60];
        let output = 150;

        // The subset chosen is the first, fourth and fifth job.
        // Profit obtained 150 = 20 + 70 + 60.
        let ret = Solution::job_scheduling(&start_time, &end_time, &profit);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let start_time = vec![1, 1, 1];
        let end_time = vec![2, 3, 4];
        let profit = vec![5, 6, 4];
        let output = 6;

        let ret = Solution::job_scheduling(&start_time, &end_time, &profit);
        assert_eq!(ret, output);
    }

    #[test]
    fn case4_test() {
        let start_time = vec![6, 15, 7, 11, 1, 3, 16, 2];
        let end_time = vec![19, 18, 19, 16, 10, 8, 19, 8];
        let profit = vec![2, 9, 1, 19, 5, 7, 3, 19];
        let output = 41;

        let ret = Solution::job_scheduling(&start_time, &end_time, &profit);
        assert_eq!(ret, output);
    }
}
