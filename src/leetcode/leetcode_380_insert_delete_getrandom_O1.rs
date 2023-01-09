/*Implement the RandomizedSet class:

RandomizedSet() Initializes the RandomizedSet object.
bool insert(int val) Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
bool remove(int val) Removes an item val from the set if present. Returns true if the item was present, false otherwise.
int getRandom() Returns a random element from the current set of elements (it's guaranteed that at least one element exists when this method is called). Each element must have the same probability of being returned.
You must implement the functions of the class such that each function works in average O(1) time complexity.
 */
use rand::{thread_rng, Rng};

use std::cell::RefCell;
use std::collections::HashMap;

#[allow(unused)]
#[derive(Default)]
struct RandomizedSet {
    map: RefCell<HashMap<i32, usize>>,
    vec: RefCell<Vec<i32>>,
}

impl RandomizedSet {
    #[allow(unused)]
    fn new() -> Self {
        RandomizedSet::default()
    }

    #[allow(unused)]
    fn insert(&self, val: i32) -> bool {
        let contains = self.map.borrow().contains_key(&val);

        match contains {
            true => false,
            false => {
                self.map.borrow_mut().insert(val, self.vec.borrow().len());
                self.vec.borrow_mut().push(val);

                true
            }
        }
    }

    #[allow(unused)]
    fn remove(&self, val: i32) -> bool {
        let contains = self.map.borrow().contains_key(&val);

        if contains {
            let len = self.vec.borrow().len();
            let index = *self.map.borrow().get(&val).unwrap();
            let last_elem = self.vec.borrow()[len - 1];
            self.vec.borrow_mut()[index] = last_elem;
            self.map.borrow_mut().insert(last_elem, index);
            self.vec.borrow_mut().remove(len - 1);
            self.map.borrow_mut().remove(&val);

            true
        } else {
            false
        }
    }

    #[allow(unused)]
    fn get_random(&self) -> i32 {
        let mut rng = thread_rng();
        let hi = self.vec.borrow().len();

        self.vec.borrow()[rng.gen_range(0..hi)]
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn case1_test() {
        let randomized_set = RandomizedSet::default();
        assert!(randomized_set.insert(1)); // Inserts 1 to the set. Returns true as 1 was inserted successfully.
        assert!(!randomized_set.remove(2)); // Returns false as 2 does not exist in the set.
        assert!(randomized_set.insert(2)); // Inserts 2 to the set, returns true. Set now contains [1,2].
        let ret = randomized_set.get_random(); // getRandom() should return either 1 or 2 randomly.
        assert!(ret == 1 || ret == 2);
        assert!(randomized_set.remove(1)); // Removes 1 from the set, returns true. Set now contains [2].
        assert!(!randomized_set.insert(2)); // 2 was already in the set, so return false.
        assert_eq!(randomized_set.get_random(), 2); // Since 2 is the only number in the set, getRandom() will always return 2.
    }
}
