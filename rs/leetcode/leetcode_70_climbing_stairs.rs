// You are climbing a staircase. It takes n steps to reach the top.
//
// Each time you can either climb 1 or 2 steps. In how many distinct ways can
// you climb to the top?

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn climb_stairs(n: i32) -> i32 {
        let mut vec = vec![0; (n + 1) as usize];
        vec[0] = 1;
        vec[1] = 1;
        for i in (2..=n) {
            let i: usize = i as usize;
            vec[i] = vec[i - 1] + vec[i - 2];
        }
        vec[n as usize]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let ret = Solution::climb_stairs(2);

        // There are two ways to climb to the top.
        // 1. 1 step + 1 step
        // 2. 2 steps
        assert_eq!(ret, 2);
    }

    #[test]
    fn case2_test() {
        let ret = Solution::climb_stairs(3);

        // There are three ways to climb to the top.
        // 1. 1 step + 1 step + 1 step
        // 2. 1 step + 2 steps
        // 3. 2 steps + 1 step
        assert_eq!(ret, 3);
    }
}
