// You have n flower seeds. Every seed must be planted first before it can begin
// to grow, then bloom. Planting a seed takes time and so does the growth of a
// seed. You are given two 0-indexed integer arrays plantTime and growTime, of
// length n each:
//
// plantTime[i] is the number of full days it takes you to plant the ith seed.
// Every day, you can work on planting exactly one seed. You do not have to work
// on planting the same seed on consecutive days, but the planting of a seed is
// not complete until you have worked plantTime[i] days on planting it in total.
// growTime[i] is the number of full days it takes the ith seed to grow after
// being completely planted. After the last day of its growth, the flower blooms
// and stays bloomed forever. From the beginning of day 0, you can plant the
// seeds in any order.
//
// Return the earliest possible day where all seeds are blooming.

#[allow(unused)]
struct Solution {}

impl Solution {
    #[allow(unused)]
    pub fn earliest_full_bloom(
        plant_time: Vec<i32>,
        grow_time: Vec<i32>,
    ) -> i32 {
        let mut pairs: Vec<(i32, i32)> =
            grow_time.into_iter().zip(plant_time).collect();
        pairs.sort_unstable();

        let (mut t, mut c) = (0, 0);
        for (g, p) in pairs.into_iter().rev() {
            c += p;
            t = t.max(c + g);
        }

        t
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let plant_time = vec![1, 4, 3];
        let grow_time = vec![2, 3, 1];
        let out = 9;
        let ret = Solution::earliest_full_bloom(plant_time, grow_time);
        assert_eq!(ret, out);
    }

    #[test]
    fn case2_test() {
        let plant_time = vec![1, 2, 3, 2];
        let grow_time = vec![2, 1, 2, 1];
        let output = 9;
        let ret = Solution::earliest_full_bloom(plant_time, grow_time);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let plant_time = vec![1];
        let grow_time = vec![1];
        let output = 2;
        let ret = Solution::earliest_full_bloom(plant_time, grow_time);
        assert_eq!(ret, output);
    }
}
