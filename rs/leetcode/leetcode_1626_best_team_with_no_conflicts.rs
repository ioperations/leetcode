// You are the manager of a basketball team. For the upcoming tournament, you
// want to choose the team with the highest overall score. The score of the team
// is the sum of scores of all the players in the team. However, the basketball
// team is not allowed to have conflicts. A conflict exists if a younger player
// has a strictly higher score than an older player. A conflict does not occur
// between players of the same age. Given two lists, scores and ages, where each
// scores[i] and ages[i] represents the score and age of the ith player,
// respectively, return the highest overall score of all possible basketball
// teams.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn best_team_score(scores: &[i32], ages: &[i32]) -> i32 {
        #[cfg(test)]
        {
            // 1 <= scores.length, ages.length <= 1000
            // scores.length == ages.length
            // 1 <= scores[i] <= 106
            // 1 <= ages[i] <= 1000
            assert!(
                scores.len() == ages.len(),
                "length of scores and ages show equal"
            );
            assert!(
                !scores.is_empty() && scores.len() <= 1_000,
                "invalid input size of scores"
            );
            assert!(
                !ages.is_empty() && ages.len() <= 1_000,
                "invalid input size of scores"
            );
        }

        let mut idx: Vec<usize> = (0..scores.len()).collect();
        idx.sort_unstable_by(|&a, &b| {
            if ages[a] == ages[b] {
                scores[a].cmp(&scores[b])
            } else {
                ages[a].cmp(&ages[b])
            }
        });
        // println!("{:?}", idx);

        let mut dp = vec![0; scores.len()];
        let mut ans = -1;
        for i in 0..scores.len() {
            let t = scores[idx[i]];
            dp[i] = t;
            for j in 0..i {
                if scores[idx[j]] <= t {
                    dp[i] = dp[i].max(dp[j] + t);
                }
            }
            ans = ans.max(dp[i]);
        }

        ans
    }

    #[allow(unused)]
    pub fn best_team_score_v2(scores: &[i32], ages: &[i32]) -> i32 {
        use std::collections::HashMap;
        fn f(
            i: usize,
            minscore: i32,
            zipped: &Vec<(i32, i32)>,
            cache: &mut HashMap<(usize, i32), i32>,
        ) -> i32 {
            if let Some(&res) = cache.get(&(i, minscore)) {
                return res;
            }
            if i == zipped.len() {
                return 0;
            }
            let (_, score) = zipped[i];
            let res = if score < minscore {
                f(i + 1, minscore, zipped, cache)
            } else {
                i32::max(
                    f(i + 1, minscore, zipped, cache),
                    f(i + 1, score, zipped, cache) + score,
                )
            };
            cache.insert((i, minscore), res);
            res
        }

        let mut zipped = ages
            .iter()
            .zip(scores.iter())
            .map(|(i, j)| (*i, *j))
            .collect::<Vec<_>>();

        zipped.sort_unstable(); // sort by age
        let mut cache = HashMap::new();

        f(0, 0, &zipped, &mut cache)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let scores = [1, 3, 5, 10, 15];
        let ages = [1, 2, 3, 4, 5];
        let output = 34;
        // Explanation: You can choose all the players.
        let ret = Solution::best_team_score(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let scores = [4, 5, 6, 5];
        let ages = [2, 1, 2, 1];
        let output = 16;
        // It is best to choose the last 3 players. Notice that you are allowed
        // to choose multiple people of the same age.
        let ret = Solution::best_team_score(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let scores = [1, 2, 3, 5];
        let ages = [8, 9, 10, 1];
        let output = 6;
        // It is best to choose the first 3 players.
        let ret = Solution::best_team_score(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[bench]
    fn benchv1(b: &mut test::Bencher) {
        let scores = [1, 2, 3, 5];
        let ages = [8, 9, 10, 1];
        let output = 6;
        b.iter(|| {
            // It is best to choose the first 3 players.
            let ret = Solution::best_team_score(&scores, &ages);
            assert_eq!(ret, output);
        });
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;
    extern crate test;

    #[test]
    fn case1_test() {
        let scores = [1, 3, 5, 10, 15];
        let ages = [1, 2, 3, 4, 5];
        let output = 34;
        // Explanation: You can choose all the players.
        let ret = Solution::best_team_score_v2(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let scores = [4, 5, 6, 5];
        let ages = [2, 1, 2, 1];
        let output = 16;
        // It is best to choose the last 3 players. Notice that you are allowed
        // to choose multiple people of the same age.
        let ret = Solution::best_team_score_v2(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let scores = [1, 2, 3, 5];
        let ages = [8, 9, 10, 1];
        let output = 6;
        // It is best to choose the first 3 players.
        let ret = Solution::best_team_score_v2(&scores, &ages);
        assert_eq!(ret, output);
    }

    #[bench]
    fn benchv2(b: &mut test::Bencher) {
        let scores = [1, 2, 3, 5];
        let ages = [8, 9, 10, 1];
        let output = 6;
        b.iter(|| {
            // It is best to choose the first 3 players.
            let ret = Solution::best_team_score_v2(&scores, &ages);
            assert_eq!(ret, output);
        });
    }
}
