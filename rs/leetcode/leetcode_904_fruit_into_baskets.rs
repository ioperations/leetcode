// You are visiting a farm that has a single row of fruit trees arranged from
// left to right. The trees are represented by an integer array fruits where
// fruits[i] is the type of fruit the ith tree produces. You want to collect as
// much fruit as possible. However, the owner has some strict rules that you
// must follow:
//
// You only have two baskets, and each basket can only hold a
// single type of fruit. There is no limit on the amount of fruit each basket
// can hold. Starting from any tree of your choice, you must pick exactly one
// fruit from every tree (including the start tree) while moving to the right.
// The picked fruits must fit in one of your baskets. Once you reach a tree with
// fruit that cannot fit in your baskets, you must stop. Given the integer array
// fruits, return the maximum number of fruits you can pick.

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn total_fruit(fruits: &[i32]) -> i32 {
        use std::cmp::max;
        use std::collections::HashMap;
        let mut ans: i32 = 0;
        let mut map: HashMap<i32, i32> = HashMap::new();
        let mut left = 0;
        for right in 0..fruits.len() {
            let count = map.entry(fruits[right]).or_insert(0);
            *count += 1;
            while map.len() > 2 {
                map.entry(fruits[left]).and_modify(|x| *x -= 1);
                if *(map.get(&fruits[left]).unwrap()) == 0 {
                    map.remove(&fruits[left]);
                }
                left += 1;
            }
            ans = max(ans, (right - left + 1) as i32);
        }
        ans
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let fruit = [1, 2, 1];
        let output = 3;
        // Explanation: We can pick from all 3 trees.
        let ret = Solution::total_fruit(&fruit);
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let fruit = [0, 1, 2, 2];
        let output = 3;
        // We can pick from trees [1,2,2].
        // If we had started at the first tree, we would only pick from trees
        // [0,1].
        let ret = Solution::total_fruit(&fruit);
        assert_eq!(ret, output);
    }

    #[test]
    fn case3_test() {
        let fruit = [1, 2, 3, 2, 2];
        let output = 4;
        // We can pick from trees [2,3,2,2].
        // If we had started at the first tree, we would only pick from trees
        // [1,2].
        let ret = Solution::total_fruit(&fruit);
        assert_eq!(ret, output);
    }
}
