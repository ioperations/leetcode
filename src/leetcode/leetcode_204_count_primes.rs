#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn count_primes(n: i32) -> i32 {
        let mut vec = vec![false; n as usize];

        let mut count = 0;
        for i in 2..n {
            if vec[i as usize] {
                continue;
            }
            count += 1;

            for j in ((i + 1)..n).step_by(i as usize) {
                vec[j as usize] = true;
            }
        }

        count
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let n = 10;
        let output = 4;
        // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
        let ret = Solution::count_primes(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let n = 0;
        let output = 0;
        // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
        let ret = Solution::count_primes(n);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let n = 1;
        let output = 0;
        // Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
        let ret = Solution::count_primes(n);
        assert_eq!(ret, output);
    }
}
