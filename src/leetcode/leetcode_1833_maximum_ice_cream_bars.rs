/*
 * It is a sweltering summer day, and a boy wants to buy some ice cream bars.
 * At the store, there are n ice cream bars. You are given an array costs of length n, where costs[i] is the price of the ith ice cream bar in coins. The boy initially has coins coins to spend, and he wants to buy as many ice cream bars as possible.
 * Return the maximum number of ice cream bars the boy can buy with coins coins.
 * Note: The boy can buy the ice cream bars in any order.
 */

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn max_ice_cream(costs: Vec<i32>, coins: i32) -> i32 {
        let mut costs = costs;
        costs.sort();
        /*
         * using scan is a little stupid cause it's not worthwhile in some input
         */
        costs
            .into_iter()
            .scan((coins, 0), |(coins_left, number), acc| {
                if *coins_left >= acc {
                    *coins_left -= acc;
                    *number += 1;
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
        let costs = [1, 3, 2, 4, 1];
        let coins = 7;
        let output = 4;
        // Explanation: The boy can buy ice cream bars at indices 0,1,2,4 for a total price of 1 + 3 + 2 + 1 = 7.
        let ret = Solution::max_ice_cream(costs.into(), coins);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let costs = [10, 6, 8, 7, 7, 8];
        let coins = 5;
        let output = 0;
        // The boy cannot afford any of the ice cream bars.
        let ret = Solution::max_ice_cream(costs.into(), coins);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let costs = [1, 6, 3, 1, 2, 5];
        let coins = 20;
        let output = 6;
        // The boy can buy all the ice cream bars for a total price of 1 + 6 + 3 + 1 + 2 + 5 = 18.
        let ret = Solution::max_ice_cream(costs.into(), coins);
        assert_eq!(ret, output);
    }
}
