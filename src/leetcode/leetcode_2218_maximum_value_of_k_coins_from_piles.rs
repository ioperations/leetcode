// There are n piles of coins on a table. Each pile consists of a positive
// number of coins of assorted denominations.
//
// In one move, you can choose any coin on top of any pile, remove it, and add
// it to your wallet.
//
// Given a list piles, where piles[i] is a list of integers denoting the
// composition of the ith pile from top to bottom, and a positive integer k,
// return the maximum total value of coins you can have in your wallet if you
// choose exactly k coins optimally.

use std::collections::HashMap;

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn max_value_of_coins(piles: &[Vec<i32>], k: i32) -> i32 {
        // n == piles.length
        // 1 <= n <= 1000
        // 1 <= piles[i][j] <= 105
        // 1 <= k <= sum(piles[i].length) <= 2000
        fn my_impl(
            piles: &[Vec<i32>],
            k: i32,
            pre: i32,
            vec: &mut Vec<(usize, usize)>,
            cache: &mut HashMap<Vec<(usize, usize)>, i32>,
        ) -> i32 {
            if k == 0 {
                return pre;
            }

            if let Some(&v) = cache.get(vec) {
                return v;
            }
            let mut ret = pre;

            for i in 0..vec.len() {
                // pass
                let (curr, len) = vec[i];
                if curr < len {
                    vec[i].0 += 1;
                    let sub_result =
                        my_impl(piles, k - 1, pre + piles[i][curr], vec, cache);
                    vec[i].0 -= 1;
                    ret = ret.max(sub_result);
                }
            }
            cache.insert(vec.clone(), ret);
            ret
        }

        let mut vec = vec![(0, 0); piles.len()];
        for (i, k) in piles.iter().enumerate() {
            vec[i].1 = k.len();
        }
        let mut cache = HashMap::new();

        my_impl(piles, k, 0, &mut vec, &mut cache)
    }

    #[allow(unused)]
    pub fn max_value_of_coins_dp(piles: &[Vec<i32>], k: i32) -> i32 {
        let n = piles.len();
        let k = k as usize;
        let mut f = vec![0; k + 1];

        for i in 1..=n {
            let m = piles[i - 1].len();
            for j in (0..=k).rev().step_by(1) {
                let mut sum = 0;
                for s in 1..=m {
                    sum += piles[i - 1][s - 1];

                    if j >= s {
                        f[j] = f[j].max(f[j - s] + sum);
                    }
                }
            }
        }

        f[k]
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let piles = [vec![1, 100, 3], vec![7, 8, 9]];
        let k = 2;
        let output = 101;
        let ret = Solution::max_value_of_coins(&piles, k);
        assert_eq!(ret, output);
        // Explanation:
        // The above diagram shows the different ways we can choose k coins.
        // The maximum total we can obtain is 101.
    }

    #[test]
    fn case2_test() {
        let piles = [
            vec![100],
            vec![100],
            vec![100],
            vec![100],
            vec![100],
            vec![100],
            vec![1, 1, 1, 1, 1, 1, 700],
        ];
        let k = 7;
        let output = 706;
        // Explanation:
        // The maximum total can be obtained if we choose all coins from the
        // last pile.
        let ret = Solution::max_value_of_coins(&piles, k);
        assert_eq!(ret, output);
        // Explanation:
        // The above diagram shows the different ways we can choose k coins.
        // The maximum total we can obtain is 101.
    }

    #[test]
    fn case3_test() {
        let piles = [
            vec![72439, 85695, 81846, 42758, 65144, 14297, 31537, 39451],
            vec![
                19764, 71823, 36354, 46958, 28114, 87264, 15574, 87571, 48499,
                65253, 12493, 74654, 51112, 77298, 1601, 76545, 59118, 53203,
                22229, 76648, 48389, 74576, 27824, 75628, 94631, 70057, 96773,
                19142, 80941, 34050, 27069, 39616, 56459, 78920, 41584, 53761,
                17790, 58366, 24227, 34346, 22036, 44800, 81753, 99968, 82617,
                6493, 78755, 74806, 53095, 98059, 7057, 10445,
            ],
            vec![34776, 2440, 79313, 55138, 11412],
            vec![
                97557, 18667, 41675, 50022, 11123, 17590, 83474, 54019, 35627,
                13014, 37056, 77373, 91418, 41519, 76863, 15557, 27494, 14902,
                45907, 54819, 12744, 82539, 58443, 25786, 51447, 35603, 69331,
                2102, 47771, 93733, 34050, 54102, 23588, 28232, 8375, 65353,
                98823, 59315, 90163, 45968, 72447,
            ],
            vec![
                89952, 10755, 71409, 74374, 84693, 90388, 28485, 66015, 12253,
                38237, 70989, 62144, 18285, 8904, 39357, 99319, 37049, 75848,
                46183, 1649, 29040, 71809, 86758, 11868, 65928, 25781, 52564,
                25778, 16464, 99497, 5654, 65619, 19954, 53215, 45674, 69707,
                13972, 78020, 52151, 52389, 33887, 13772, 92418, 664, 75634,
                59765, 12688, 57722, 70461, 79363, 92026, 54512, 24041, 89916,
                56759, 60123, 65610, 5850, 87097, 89258, 76416, 76776, 70034,
                59027, 59023, 7240, 26813, 61778, 84256, 75049, 95050, 84324,
                51091, 24696, 33869, 2910, 83693, 20924, 6863, 47022, 86839,
                64209, 15103, 89342, 62669, 13559, 34788, 37247, 1159, 48940,
                48692, 46709, 95576, 73397, 72163, 40122, 62845, 64454, 76710,
                59387, 83344, 10579, 25225, 98674, 51953, 59175, 76545, 1637,
                83613, 66988, 65439, 49451, 42592, 36905, 77702, 99501, 17782,
                25256, 77296, 17769, 79030, 76171, 2491, 69504, 67000, 59663,
                75582, 653, 93200, 209, 43004, 33609, 20103, 48350, 50466,
                77209, 94066, 20317, 986, 82240, 1189, 63862, 96066, 66995,
                57706, 6144, 20388, 35948, 62715, 36332, 73459, 74773, 35366,
                12746, 37992, 15377, 14502, 8965, 53091, 7991, 59616, 81410,
                24191, 30420, 18217, 94581, 72227,
            ],
            vec![
                15823, 59385, 68870, 56950, 33533, 2138, 11304, 35666, 97247,
                54999, 5586, 79896, 69459, 57857, 28794, 58732, 58679, 44191,
                90823, 59036, 75475, 60690, 10485, 10769, 17784, 19888, 80099,
                99729, 19976,
            ],
            vec![
                59550, 50910, 17670, 26028, 25045, 98929, 99673, 89352, 75221,
                57620, 65351, 98616, 78247, 97883, 54080, 42619, 82387, 23327,
                91767, 43785, 66797, 66557, 58096, 85284, 84730, 80379, 80736,
                66099, 95458, 26583, 37137, 3478, 95072, 63228, 3184, 71730,
                89909, 24226, 90088, 80923, 13528, 75724, 63218, 74838, 27989,
                18828, 89766, 4895, 31905,
            ],
            vec![
                22311, 14670, 33947, 26836, 29549, 28576, 37910, 93901, 80934,
                56055, 60622, 35905, 45885, 359, 64145, 59122, 28757, 94294,
                30261, 37745, 60919, 93941, 95291, 56083, 26328, 41586, 69373,
                51571, 38224, 8198, 93813, 46157, 17867, 2827, 60845, 75333,
                38851, 50012, 71241, 10619, 14825, 61706, 64996, 94305, 30241,
                13894, 27289, 11738, 47231, 87766, 81880, 16220, 2854, 78683,
                35109, 43632, 88767, 54656, 41975,
            ],
            vec![79264, 59527, 34943, 29393, 65145],
            vec![
                78117, 31420, 94376, 13668, 98867, 95735, 61876, 62952, 28389,
                81260, 93529, 64178, 29771, 2738,
            ],
            vec![
                38084, 54888, 59209, 60068, 75301, 72449, 96921, 47727, 1566,
                77534, 86174, 77797, 26250, 21817, 62066, 66740, 20896, 40867,
                16346, 37595, 69693, 26361, 67906, 60877, 39891, 18658, 45460,
                81337, 30870, 33636, 77290, 74525, 12125, 84153, 26825,
            ],
        ];

        let k = 307;
        let output = 17_035_711;
        // Explanation:
        // The maximum total can be obtained if we choose all coins from the
        // last pile.
        let ret = Solution::max_value_of_coins_dp(&piles, k);
        assert_eq!(ret, output);
        // Explanation:
        // The above diagram shows the different ways we can choose k coins.
        // The maximum total we can obtain is 101.
    }
}
