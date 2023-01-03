/*You are given an array of n strings strs, all of the same length.↳

The strings can be arranged such that there is one on each line, making a grid. For example, strs = ["abc", "bce", "cae"] can be arranged as:
abc
bce
cae
You want to delete the columns that are not sorted lexicographically. In the above example (0-indexed), columns 0 ('a', 'b', 'c') and 2 ('c', 'e', 'e') are sorted while column 1 ('b', 'c', 'a') is not, so you would delete column 1.
Return the number of columns that you will delete.*/

#[allow(unused)]
struct Solution;
impl Solution {
    #[allow(unused)]
    pub fn min_deletion_size(strs: Vec<String>) -> i32 {
        #[cfg(test)]
        {
            /*
             * n == strs.length
             * 1 <= n <= 100
             * 1 <= strs[i].length <= 1000
             * strs[i] consists of lowercase English letters.
             */
            assert!(!strs.is_empty() && strs.len() <= 1000);
        }

        let strs: Vec<Vec<char>> = { strs.into_iter().map(|ele| ele.chars().collect()).collect() };
        let n = strs.len();
        let strlen = strs[0].len();

        let should_drop = |i: usize| -> bool {
            for j in 0..(n - 1) {
                if strs[j + 1][i] < strs[j][i] {
                    return true;
                }
            }
            false
        };
        (0..strlen).filter(|i: &usize| should_drop(*i)).count() as i32
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let strs = ["cba", "daf", "ghi"]
            .iter()
            .map(|&str| Into::into(str))
            .collect();
        let output = 1;
        /*
        Explanation: The grid looks as follows:
          cba
          daf
          ghi
        Columns 0 and 2 are sorted, but column 1 is not, so you only need to delete 1 column.
        */
        let ret = Solution::min_deletion_size(strs);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let strs = ["a", "b"].iter().map(|&str| Into::into(str)).collect();
        let output = 0;
        /*
        The grid looks as follows:
          a
          b
        Column 0 is the only column and is sorted, so you will not delete any columns.
        */
        let ret = Solution::min_deletion_size(strs);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let strs = ["zyx", "wvu", "tsr"]
            .iter()
            .map(|&str| Into::into(str))
            .collect();
        let output = 3;
        /*
         The grid looks as follows:
          zyx
          wvu
          tsr
        All 3 columns are not sorted, so you will delete all 3.
         */
        let ret = Solution::min_deletion_size(strs);
        assert_eq!(ret, output);
    }
}
