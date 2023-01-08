/*you are given an array prices where prices[i] is the price of a given stock on the ith day.↳

Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).*/

use std::collections::HashMap;

#[derive(PartialEq, Eq, Hash, Copy, Clone)]
#[allow(unused)]
enum Invested {
    Yes,
    No,
    Cooldown,
}

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn max_profit(prices: Vec<i32>) -> i32 {
        let l = prices.len();
        if l == 1 {
            return 0;
        }

        let (mut buy, mut sell) = (vec![0; l], vec![0; l]);
        buy[0] = -prices[0];
        buy[1] = -(prices[0].min(prices[1]));
        sell[1] = 0.max(buy[0] + prices[1]);

        for (cur_price, i) in prices[2..].iter().zip(2..) {
            buy[i] = buy[i - 1].max(sell[i - 2] - cur_price);
            sell[i] = sell[i - 1].max(buy[i - 1] + cur_price);
        }

        sell[l - 1]
    }

    #[allow(unused)]
    fn dp(
        prices: &[i32],
        day: usize,
        invested: Invested,
        memo: &mut HashMap<(usize, Invested), i32>,
    ) -> i32 {
        if day == prices.len() {
            0
        } else if let Some(profit) = memo.get(&(day, invested)) {
            *profit
        } else {
            let rez = match invested {
                Invested::Yes => Self::dp(prices, day + 1, invested, memo)
                    .max(prices[day] + Self::dp(prices, day + 1, Invested::Cooldown, memo)),
                Invested::No => Self::dp(prices, day + 1, invested, memo)
                    .max(-prices[day] + Self::dp(prices, day + 1, Invested::Yes, memo)),
                Invested::Cooldown => Self::dp(prices, day + 1, Invested::No, memo),
            };
            memo.insert((day, invested), rez);
            rez
        }
    }

    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/solutions/2520407/rust-dp-solution-evolution-with-comments/?q=rust+dp&orderBy=most_relevant
    #[allow(unused)]
    pub fn max_profit_v2(prices: Vec<i32>) -> i32 {
        Self::dp(&prices, 0, Invested::No, &mut HashMap::new())
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let prices = [1, 2, 3, 0, 2];
        let output = 3;
        let ret = Solution::max_profit(prices.into());
        assert_eq!(ret, output);
        // Explanation: transactions = [buy, sell, cooldown, buy, sell]
    }

    #[test]
    fn case2_test() {
        let prices = [1];
        let output = 0;
        let ret = Solution::max_profit(prices.into());
        assert_eq!(ret, output);
        // Explanation: transactions = [buy, sell, cooldown, buy, sell]
    }
}

#[cfg(test)]
mod tests_v2 {
    use super::*;

    #[test]
    fn case1_test() {
        let prices = [1, 2, 3, 0, 2];
        let output = 3;
        let ret = Solution::max_profit_v2(prices.into());
        assert_eq!(ret, output);
        // Explanation: transactions = [buy, sell, cooldown, buy, sell]
    }

    #[test]
    fn case2_test() {
        let prices = [1];
        let output = 0;
        let ret = Solution::max_profit_v2(prices.into());
        assert_eq!(ret, output);
        // Explanation: transactions = [buy, sell, cooldown, buy, sell]
    }
}
