// Alice and Bob are traveling to Rome for separate business meetings.
//
// You are given 4 strings arriveAlice, leaveAlice, arriveBob, and leaveBob.
// Alice will be in the city from the dates arriveAlice to leaveAlice
// (inclusive), while Bob will be in the city from the dates arriveBob to
// leaveBob (inclusive). Each will be a 5-character string in the format
// "MM-DD", corresponding to the month and day of the date.
//
// Return the total number of days that Alice and Bob are in Rome together.
//
// You can assume that all dates occur in the same calendar year, which is not a
// leap year. Note that the number of days per month can be represented as: [31,
// 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31].

// All dates are provided in the format "MM-DD".
// Alice and Bob's arrival dates are earlier than or equal to their leaving
// dates. The given dates are valid dates of a non-leap year.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn count_days_together(
        arrive_alice: String,
        leave_alice: String,
        arrive_bob: String,
        leave_bob: String,
    ) -> i32 {
        fn month_to_day(num: i32) -> i32 {
            let d = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
            d.iter().take((num - 1) as usize).sum()
        };

        fn get_day(str: &str) -> i32 {
            let p = str
                .split("-")
                .collect::<Vec<_>>()
                .iter()
                .map(|v| v.parse::<i32>().unwrap())
                .collect::<Vec<_>>();

            month_to_day(p[0]) + p[1]
        }

        let arrive_alice = get_day(&arrive_alice);
        let leave_alice = get_day(&leave_alice);
        let arrive_bob = get_day(&arrive_bob);
        let leave_bob = get_day(&leave_bob);

        0.max(leave_alice.min(leave_bob) - arrive_alice.max(arrive_bob) + 1)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let arrive_alice = "08-15".to_string();
        let leave_alice = "08-18".to_string();
        let arrive_bob = "08-16".to_string();
        let leave_bob = "08-19".to_string();
        let output = 3;
        let ret = Solution::count_days_together(
            arrive_alice,
            leave_alice,
            arrive_bob,
            leave_bob,
        );
        assert_eq!(output, ret);
        // Explanation: Alice will be in Rome from August 15 to August 18. Bob
        // will be in Rome from August 16 to August 19. They are both in Rome
        // together on August 16th, 17th, and 18th, so the answer is 3.
    }

    #[test]
    fn case2_test() {
        let arrive_alice = "10-01".to_string();
        let leave_alice = "10-31".to_string();
        let arrive_bob = "11-01".to_string();
        let leave_bob = "12-31".to_string();
        let output = 0;
        let ret = Solution::count_days_together(
            arrive_alice,
            leave_alice,
            arrive_bob,
            leave_bob,
        );
        assert_eq!(output, ret);
        // There is no day when Alice and Bob are in Rome together, so we return
        // 0.
    }
}
