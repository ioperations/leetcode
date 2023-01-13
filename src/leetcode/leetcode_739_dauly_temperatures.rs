// Given an array of integers temperatures represents the daily temperatures,
// return an array answer such that answer[i] is the number of days you have to wait after the ith day to get a warmer temperature.
// If there is no future day for which this is possible, keep answer[i] == 0 instead.

#[allow(unused)]
struct Solution;

#[allow(unused)]
impl Solution {
    pub fn daily_temperatures(temperatures: &[i32]) -> Vec<i32> {
        let mut stack = vec![];
        let mut res = vec![0; temperatures.len()];

        for (j, temp) in temperatures.iter().enumerate() {
            while let Some((last_temp, i)) = stack.pop() {
                if temp > last_temp {
                    res[i] = (j - i) as i32;
                } else {
                    stack.push((last_temp, i));
                    break;
                }
            }

            stack.push((temp, j));
        }

        res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let temperature = [73, 74, 75, 71, 69, 72, 76, 73];
        let output = [1, 1, 4, 2, 1, 1, 0, 0];
        let ret = Solution::daily_temperatures(&temperature);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let temperature = [30, 40, 50, 60];
        let output = [1, 1, 1, 0];
        let ret = Solution::daily_temperatures(&temperature);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let temperature = [30, 60, 90];
        let output = [1, 1, 0];
        let ret = Solution::daily_temperatures(&temperature);
        assert_eq!(ret, output);
    }
}
