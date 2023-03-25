// You are given an integer n indicating there are n people numbered from 0 to n
// - 1. You are also given a 0-indexed 2D integer array meetings where
// meetings[i] = [xi, yi, timei] indicates that person xi and person yi have a
// meeting at timei. A person may attend multiple meetings at the same time.
// Finally, you are given an integer firstPerson.
//
// Person 0 has a secret and initially shares the secret with a person
// firstPerson at time 0. This secret is then shared every time a meeting takes
// place with a person that has the secret. More formally, for every meeting, if
// a person xi has the secret at timei, then they will share the secret with
// person yi, and vice versa.
//
// The secrets are shared instantaneously. That is, a person may receive the
// secret and share it with people in other meetings within the same time frame.
//
// Return a list of all the people that have the secret after all the meetings
// have taken place. You may return the answer in any order.
//

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn find_all_people(
        n: i32,
        meetings: Vec<Vec<i32>>,
        first_person: i32,
    ) -> Vec<i32> {
        // 2 <= n <= 105
        // 1 <= meetings.length <= 105
        // meetings[i].length == 3
        // 0 <= xi, yi <= n - 1
        // xi != yi
        // 1 <= timei <= 105
        // 1 <= firstPerson <= n - 1

        // Set of people knowing the secret.
        let mut know_secret = vec![false; n as usize];
        let mut meetings = meetings;

        know_secret[0] = true;
        know_secret[first_person as usize] = true;

        // Sorting by time in ascending order.
        meetings.sort_unstable_by_key(|x| x[2]);

        let mut left = 0;
        while left < meetings.len() {
            // We have a group of meetings at the same time.
            // Checking all the pairs of the meeting group.
            // If someone knows the secret, share it to another and set the flag
            // secret_shared. Do sharing rounds until no secret
            // shared during the round.
            let time = meetings[left][2];
            let mut secret_shared = true;
            let mut right = left;
            while secret_shared {
                secret_shared = false;
                right = left;
                while right < meetings.len() && meetings[right][2] == time {
                    let x = meetings[right][0] as usize;
                    let y = meetings[right][1] as usize;
                    if know_secret[x] && !know_secret[y]
                        || !know_secret[x] && know_secret[y]
                    {
                        // We found a person that knows the secret and can share
                        // it.
                        secret_shared = true;
                        know_secret[x] = true;
                        know_secret[y] = true;
                    }
                    right += 1;
                }
            }
            left = right;
        }

        know_secret
            .into_iter()
            .enumerate()
            .filter(|x| x.1)
            .map(|x| x.0 as i32)
            .collect()
    }
}

#[cfg(test)]
mod test {
    use hashbrown::HashSet;

    use super::*;

    #[test]
    fn case1_test() {
        let n = 6;
        let meetings = [vec![1, 2, 5], vec![2, 3, 8], vec![1, 5, 10]];
        let first_person = 1;
        let output: HashSet<i32> = [0, 1, 2, 3, 5].into_iter().collect();
        let ret = Solution::find_all_people(n, meetings.into(), first_person);
        let ret: HashSet<i32> = ret.into_iter().collect();
        assert_eq!(ret, output);
        // Explanation:
        // At time 0, person 0 shares the secret with person 1.
        // At time 5, person 1 shares the secret with person 2.
        // At time 8, person 2 shares the secret with person 3.
        // At time 10, person 1 shares the secret with person 5.​​​​
        // Thus, people 0, 1, 2, 3, and 5 know the secret after all the
        // meetings.
    }

    #[test]
    fn case2_test() {
        let n = 4;
        let meetings = [vec![3, 1, 3], vec![1, 2, 2], vec![0, 3, 3]];
        let first_person = 3;
        let output: HashSet<i32> = [0, 1, 3].into_iter().collect();
        let ret = Solution::find_all_people(n, meetings.into(), first_person);
        let ret: HashSet<i32> = ret.into_iter().collect();
        assert_eq!(ret, output);
        // Explanation:
        // At time 0, person 0 shares the secret with person 3.
        // At time 2, neither person 1 nor person 2 know the secret.
        // At time 3, person 3 shares the secret with person 0 and person 1.
        // Thus, people 0, 1, and 3 know the secret after all the meetings.
    }

    #[test]
    fn case3_test() {
        let n = 5;
        let meetings = [vec![3, 4, 2], vec![1, 2, 1], vec![2, 3, 1]];
        let first_person = 1;
        let output: HashSet<i32> = [0, 1, 2, 3, 4].into_iter().collect();
        let ret = Solution::find_all_people(n, meetings.into(), first_person);
        let ret: HashSet<i32> = ret.into_iter().collect();
        assert_eq!(ret, output);
        // Explanation:
        // At time 0, person 0 shares the secret with person 1.
        // At time 1, person 1 shares the secret with person 2, and person 2
        // shares the secret with person 3. Note that person 2 can share
        // the secret at the same time as receiving it. At time 2,
        // person 3 shares the secret with person 4. Thus, people 0, 1,
        // 2, 3, and 4 know the secret after all the meetings.
    }
}
