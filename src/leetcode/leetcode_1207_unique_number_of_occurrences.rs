/*Given an array of integers arr, return true if the number of occurrences of each value in the array is unique, or false otherwise.
*/

use std::{collections::HashMap, usize};
#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn unique_occurrences(arr: Vec<i32>) -> bool {
        pub fn _contains_duplicate(vec: &Vec<usize>) -> bool {
            let mut map = HashMap::<usize, usize>::new();
            for (i, num) in vec.iter().enumerate() {
                match map.contains_key(num) {
                    true => return true,
                    false => map.insert(*num, i),
                };
            }
            false
        }
        let mut hasmap: HashMap<i32, usize> = HashMap::new();
        for i in arr {
            hasmap.entry(i).and_modify(|e| *e += 1).or_insert(0);
        }

        let v = hasmap
            .values()
            .into_iter()
            .map(|e| *e)
            .collect::<Vec<usize>>();

        !_contains_duplicate(&v)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let array = vec![1, 2, 2, 1, 1, 3];
        let output = true;
        let ret = Solution::unique_occurrences(array);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let array = vec![1, 2];
        let output = false;
        let ret = Solution::unique_occurrences(array);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let array = vec![-3, 0, 1, -3, 1, 1, 1, -3, 10, 0];
        let output = true;
        let ret = Solution::unique_occurrences(array);
        assert_eq!(ret, output);
    }
}
