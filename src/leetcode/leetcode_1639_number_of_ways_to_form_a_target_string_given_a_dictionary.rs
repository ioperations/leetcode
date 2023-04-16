// You are given a list of strings of the same length words and a string target.
//
// Your task is to form target using the given words under the following rules:
//
// target should be formed from left to right.
// To form the ith character (0-indexed) of target, you can choose the kth
// character of the jth string in words if target[i] = words[j][k]. Once you use
// the kth character of the jth string of words, you can no longer use the xth
// character of any string in words where x <= k. In other words, all characters
// to the left of or at index k become unusuable for every string. Repeat the
// process until you form the string target.
//
// Notice that you can use multiple characters from the same string in words
// provided the conditions above are met.
//
// Return the number of ways to form target from words. Since the answer may be
// too large, return it modulo 109 + 7.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn num_ways(words: &[String], target: &str) -> i32 {
        // 1 <= words.length <= 1000
        // 1 <= words[i].length <= 1000
        // All strings in words have the same length.
        // 1 <= target.length <= 1000
        // words[i] and target contain only lowercase English letters.
        fn my_impl(words: &[String], target: &str) -> i32 {
            let n = words[0].len();
            let m = target.len();
            let target: Vec<_> =
                target.bytes().map(|c| (c - b'a') as usize).collect();

            let mut count = vec![vec![0; 26]; n];
            for word in words {
                for (j, b) in word.bytes().enumerate() {
                    count[j][(b - b'a') as usize] += 1;
                }
            }

            let mut dp = vec![vec![0u64; m]; n];
            dp[0][0] = count[0][target[0]];
            let mm = 1_000_000_007;

            for i in 1..n {
                dp[i][0] = (count[i][target[0]] + dp[i - 1][0]) % mm;
                (1..m).for_each(|j| {
                    dp[i][j] = (dp[i - 1][j - 1] * count[i][target[j]]
                        + dp[i - 1][j])
                        % mm;
                });
            }

            dp[n - 1][m - 1] as i32
        }
        my_impl(words, target)
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let words =
            ["acca", "bbbb", "caca"].map(|s| -> String { s.to_string() });
        let target = "aba";
        let output = 6;
        let ret = Solution::num_ways(&words, target);
        assert_eq!(ret, output);
        // Explanation: There are 6 ways to form target.
        // "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("caca")
        // "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("caca")
        // "aba" -> index 0 ("acca"), index 1 ("bbbb"), index 3 ("acca")
        // "aba" -> index 0 ("acca"), index 2 ("bbbb"), index 3 ("acca")
        // "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("acca")
        // "aba" -> index 1 ("caca"), index 2 ("bbbb"), index 3 ("caca")
        //
    }

    #[test]
    fn case2_test() {
        let words = ["abba", "baab"].map(std::string::ToString::to_string);
        let target = "bab";
        let output = 4;
        let ret = Solution::num_ways(&words, target);
        assert_eq!(ret, output);
        // Explanation: There are 6 ways to form target.
        // There are 4 ways to form target.
        // "bab" -> index 0 ("baab"), index 1 ("baab"), index 2 ("abba")
        // "bab" -> index 0 ("baab"), index 1 ("baab"), index 3 ("baab")
        // "bab" -> index 0 ("baab"), index 2 ("baab"), index 3 ("baab")
        // "bab" -> index 1 ("abba"), index 2 ("baab"), index 3 ("baab")
    }
}
