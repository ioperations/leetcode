// You are given an array of unique integers salary where salary[i] is the
// salary of the ith employee.
//
// Return the average salary of employees excluding the minimum and maximum
// salary. Answers within 10-5 of the actual answer will be accepted.
#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn average(salary: &[i32]) -> f64 {
        // 3 <= salary.length <= 100
        // 1000 <= salary[i] <= 106
        // All the integers of salary are unique.
        let len = salary.len() as i64;
        let (mut min, mut max) = (i32::MAX, i32::MIN);
        let mut sum = 0_i64;
        for &x in salary {
            min = min.min(x);
            max = max.max(x);
            sum += x as i64;
        }
        (sum - min as i64 - max as i64) as f64 / (len - 2) as f64
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let salary = [4000, 3000, 1000, 2000];
        let output = 2500.00000;
        // Explanation: Minimum salary and maximum salary are 1000 and 4000
        // respectively. Average salary excluding minimum and maximum
        // salary is (2000+3000) / 2 = 2500
        let ret = Solution::average(&salary);
        assert!((ret - output).abs() < f64::EPSILON);
    }

    #[test]
    fn case2_test() {
        let salary = [1000, 2000, 3000];
        let output = 2000.00000;
        // Minimum salary and maximum salary are 1000 and 3000 respectively.
        // Average salary excluding minimum and maximum salary is (2000) / 1 =
        // 2000

        let ret = Solution::average(&salary);
        assert!((ret - output).abs() < f64::EPSILON);
    }
}
