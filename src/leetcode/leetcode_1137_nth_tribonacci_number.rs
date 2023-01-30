/*The Tribonacci sequence Tn is defined as follows:
T0 = 0, T1 = 1, T2 = 1, and Tn+3 = Tn + Tn+1 + Tn+2 for n >= 0.
Given n, return the value of Tn.*/

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn tribonacci(n: i32) -> i32 {
        #[cfg(test)]
        {
            if n < 0 {
                // Constraints:
                // 0 <= n <= 37
                // The answer is guaranteed to fit within a 32-bit integer, ie. answer <= 2^31 - 1.
                panic!("not valid in current input");
            }
        }

        Self::tribonacci_impl(n)
    }

    #[allow(unused)]
    fn tribonacci_impl(n: i32) -> i32 {
        match n {
            0 => 0,
            1 | 2 => 1,
            _ => {
                (0..n - 2)
                    .scan((0, 1, 1), |(v1, v2, v3), _| {
                        let v = *v1;
                        *v1 = *v2;
                        *v2 = *v3;

                        *v3 = *v1 + *v2 + v;
                        Some((*v1, *v2, *v3))
                    })
                    .last()
                    .unwrap()
                    .2
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 4;
        let output = 4;

        // Explanation:
        // T_3 = 0 + 1 + 1 = 2
        // T_4 = 1 + 1 + 2 = 4
        let ret = Solution::tribonacci(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 25;
        let output = 1389537;

        // Explanation:
        // T_3 = 0 + 1 + 1 = 2
        // T_4 = 1 + 1 + 2 = 4
        let ret = Solution::tribonacci(n);
        assert_eq!(ret, output);
    }
}
