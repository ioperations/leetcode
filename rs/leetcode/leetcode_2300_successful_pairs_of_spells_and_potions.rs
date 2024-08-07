// You are given two positive integer arrays spells and potions, of length n and
// m respectively, where spells[i] represents the strength of the ith spell and
// potions[j] represents the strength of the jth potion.
//
// You are also given an integer success. A spell and potion pair is considered
// successful if the product of their strengths is at least success.
//
// Return an integer array pairs of length n where pairs[i] is the number of
// potions that will form a successful pair with the ith spell.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn successful_pairs(
        spells: &[i32],
        potions: Vec<i32>,
        success: i64,
    ) -> Vec<i32> {
        // n == spells.length
        // m == potions.length
        // 1 <= n, m <= 105
        // 1 <= spells[i], potions[i] <= 105
        // 1 <= success <= 1010
        fn find_by_binary_search(po: &[i32], value: i64) -> usize {
            match po.binary_search_by(|probe| probe.cmp(&(value as i32))) {
                Ok(v) | Err(v) => v,
            }
        };

        let mut potions = potions;

        potions.sort_unstable();

        let len = potions.len();
        let mut ret = Vec::with_capacity(spells.len());

        for &k in spells {
            let divide_fully = |v: i64, to: i64| -> bool { v % to == 0 };

            let c = if divide_fully(success, k as i64) {
                find_by_binary_search(&potions, success / k as i64)
            } else {
                find_by_binary_search(&potions, success / k as i64 + 1)
            };
            ret.push((len - c) as i32);
        }

        ret
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let spells = [5, 1, 3];
        let potions = [1, 2, 3, 4, 5];
        let success = 7;
        let output = [4, 0, 3];
        let ret = Solution::successful_pairs(&spells, potions.into(), success);
        // 0th spell: 5 * [1,2,3,4,5] = [5,10,15,20,25]. 4 pairs are successful.
        // - 1st spell: 1 * [1,2,3,4,5] = [1,2,3,4,5]. 0 pairs are successful.
        // - 2nd spell: 3 * [1,2,3,4,5] = [3,6,9,12,15]. 3 pairs are successful.
        // Thus, [4,0,3] is returned.
        assert_eq!(ret, output);
    }

    // https://github.com/rust-lang/rust  9bad7ba324099d124c
    #[ignore]
    #[test]
    fn case2_test() {
        let spells = [3, 1, 2];
        let potions = [8, 5, 8];
        let success = 16;
        let output = [2, 0, 2];
        let ret = Solution::successful_pairs(&spells, potions.into(), success);
        // 0th spell: 3 * [8,5,8] = [24,15,24]. 2 pairs are successful.
        // - 1st spell: 1 * [8,5,8] = [8,5,8]. 0 pairs are successful.
        // - 2nd spell: 2 * [8,5,8] = [16,10,16]. 2 pairs are successful.
        // Thus, [2,0,2] is returned
        assert_eq!(ret, output);
    }
}
