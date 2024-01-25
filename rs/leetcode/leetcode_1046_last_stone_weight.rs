// You are given an array of integers stones where stones[i] is the weight of
// the ith stone.
//
// We are playing a game with the stones. On each turn, we choose the heaviest
// two stones and smash them together. Suppose the heaviest two stones have
// weights x and y with x <= y. The result of this smash is:
//
// If x == y, both stones are destroyed, and
// If x != y, the stone of weight x is destroyed, and the stone of weight y has
// new weight y - x.
//
// At the end of the game, there is at most one stone left.
//
// Return the weight of the last remaining stone. If there are no stones left,
// return 0
#![allow(unused)]
struct Solution;

impl Solution {
    #![allow(unused)]
    pub fn last_stone_weight(stones: Vec<i32>) -> i32 {
        // 1 <= stones.length <= 30
        // 1 <= stones[i] <= 1000
        use std::collections::BinaryHeap;
        let mut heap = BinaryHeap::from(stones);

        loop {
            match heap.len() {
                0 => {
                    return 0;
                }
                1 => {
                    return heap.pop().unwrap();
                }
                _ => {}
            }

            let v1 = heap.pop().unwrap();
            let v2 = heap.pop().unwrap();

            let v3 = v1 - v2;
            if v3 != 0 {
                heap.push(v3);
            }
        }

        1
    }
}

#[cfg(test)]
mod test {
    use super::*;

    #[test]
    fn case1_test() {
        let stones = [2, 7, 4, 1, 8, 1];
        let output = 1;
        // Explanation:
        // We combine 7 and 8 to get 1 so the array converts to [2,4,1,1,1]
        // then, we combine 2 and 4 to get 2 so the array converts to
        // [2,1,1,1] then, we combine 2 and 1 to get 1 so the array
        // converts to [1,1,1] then, we combine 1 and 1 to get 0 so the
        // array converts to [1] then that's the value of the last stone.
        let ret = Solution::last_stone_weight(stones.into());
        assert_eq!(ret, output);
    }

    #[test]
    fn case2_test() {
        let stones = [1];
        let output = 1;
        // Explanation:
        let ret = Solution::last_stone_weight(stones.into());
        assert_eq!(ret, output);
    }
}
