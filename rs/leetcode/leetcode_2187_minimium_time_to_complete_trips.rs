// You are given an array time where time[i] denotes the time taken by the ith
// bus to complete one trip. Each bus can make multiple trips successively; that
// is, the next trip can start immediately after completing the current trip.
// Also, each bus operates independently; that is, the trips of one bus do not
// influence the trips of any other bus. You are also given an integer
// totalTrips, which denotes the number of trips all buses should make in total.
// Return the minimum time required for all buses to complete at least
// totalTrips trips.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn minimum_time(time: &[i32], total_trips: i32) -> i64 {
        let my_impl = || -> i64 {
            for i in (1..) {
                let mut ret = 0;
                for &j in time {
                    ret += i / j;
                    if ret >= total_trips {
                        return i as i64;
                    }
                }
            }
            0
        };
        my_impl()
    }
}

#[cfg(test)]
mod test {
    use super::super::leetcode_panic_after::panic_after;
    use super::*;
    use std::time::Duration;

    #[test]
    fn case1_test() {
        let time = [1, 2, 3];
        let total_trips = 5;
        let output = 3;
        // Explanation:
        // - At time t = 1, the number of trips completed by each bus are
        //   [1,0,0].
        // The total number of trips completed is 1 + 0 + 0 = 1.
        // - At time t = 2, the number of trips completed by each bus are
        //   [2,1,0].
        // The total number of trips completed is 2 + 1 + 0 = 3.
        // - At time t = 3, the number of trips completed by each bus are
        //   [3,1,1].
        // The total number of trips completed is 3 + 1 + 1 = 5.
        // So the minimum time needed for all buses to complete at least 5 trips
        // is 3.
        let ret = Solution::minimum_time(&time, total_trips);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let time = [2];
        let total_trips = 1;
        let output = 2;
        // Explanation:

        // There is only one bus, and it will complete its first trip at t = 2.
        // So the minimum time needed to complete 1 trip is 2.
        //
        let ret = Solution::minimum_time(&time, total_trips);
        assert_eq!(ret, output);
    }
}
