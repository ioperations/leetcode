// There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your
// goal is to visit all the rooms. However, you cannot enter a locked room without having its key.
// When you visit a room, you may find a set of distinct keys in it. Each key has a number on it,
// denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.
// Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i,
// return true if you can visit all the rooms, or false otherwise

#[allow(unused)]
struct Solution;

impl Solution {
    #[allow(unused)]
    pub fn can_visit_all_rooms(rooms: &[Vec<i32>]) -> bool {
        let mut accessible = vec![false; rooms.len()];
        accessible[0] = true;
        let mut stack = vec![0];
        let mut n_accessible = 1;

        while let Some(room) = stack.pop() {
            for key in rooms[room].iter().map(|key| *key as usize) {
                if !accessible[key] {
                    n_accessible += 1;
                    if n_accessible == rooms.len() {
                        return true;
                    }
                    accessible[key] = true;
                    stack.push(key);
                }
            }
        }
        false
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let roomes = [vec![1], vec![2], vec![3], vec![]];
        let output = true;
        let ret = Solution::can_visit_all_rooms(&roomes);
        assert_eq!(ret, output);
        /*
         We visit room 0 and pick up key 1.
         We then visit room 1 and pick up key 2.
         We then visit room 2 and pick up key 3.
         We then visit room 3.
         Since we were able to visit every room, we return true.
        */
    }

    #[test]
    fn case2_test() {
        let roomes = [vec![1, 3], vec![3, 0, 1], vec![2], vec![0]];
        let output = false;
        let ret = Solution::can_visit_all_rooms(&roomes);
        assert_eq!(ret, output);
        // We can not enter room number 2 since the only key that unlocks it is in that room.
    }
}
