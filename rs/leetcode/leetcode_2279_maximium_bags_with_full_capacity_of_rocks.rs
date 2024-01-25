// you have n bags numbered from 0 to n - 1. You are given two 0-indexed integer
// arrays capacity and rocks. The ith bag can hold a maximum of capacity[i]
// rocks and currently contains rocks[i] rocks. You are also given an integer
// additionalRocks, the number of additional rocks you can place in any of the
// bags.
//
// Return the maximum number of bags that could have full capacity after placing
// the additional rocks in some bags.

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn maximum_bags(
        capacity: &[i32],
        rocks: &[i32],
        additional_rocks: i32,
    ) -> i32 {
        let mut left = capacity
            .iter()
            .zip(rocks.iter())
            .map(|(&c, &i)| c - i)
            .collect::<Vec<i32>>();
        left.sort_unstable();
        // 用additional_rocks
        // 把left当中所有元素消为零,使得left当中为零的元素最多
        // 应该不用扫完
        left.into_iter()
            .scan((0, 0), |(number, sum), acc| {
                if *sum + acc <= additional_rocks {
                    *number += 1;
                    *sum += acc;
                }
                Some(*number)
            })
            .last()
            .unwrap()
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let capacity = [2, 3, 4, 5];
        let rocks = [1, 2, 4, 4];
        let additional_rocks = 2;
        let output = 3;
        let ret = Solution::maximum_bags(&capacity, &rocks, additional_rocks);
        assert_eq!(ret, output);
        // Explanation:
        // Place 1 rock in bag 0 and 1 rock in bag 1.
        // The number of rocks in each bag are now [2,3,4,4].
        // Bags 0, 1, and 2 have full capacity.
        // There are 3 bags at full capacity, so we return 3.
        // It can be shown that it is not possible to have more than 3 bags at
        // full capacity. Note that there may be other ways of placing
        // the rocks that result in an answer of 3.
        //
    }

    #[test]
    fn case2_test() {
        let capacity = [10, 2, 2];
        let rocks = [2, 2, 0];
        let additional_rocks = 100;
        let output = 3;
        let ret = Solution::maximum_bags(&capacity, &rocks, additional_rocks);
        assert_eq!(ret, output);
        // Explanation:
        // Place 8 rocks in bag 0 and 2 rocks in bag 2.
        // The number of rocks in each bag are now [10,2,2].
        // Bags 0, 1, and 2 have full capacity.
        // There are 3 bags at full capacity, so we return 3.
        // It can be shown that it is not possible to have more than 3 bags at
        // full capacity. Note that we did not use all of the additional
        // rocks.
    }
}
