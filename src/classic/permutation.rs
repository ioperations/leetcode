#[cfg(test)]
mod tests {
    pub fn next_permutation(nums: &mut [i32]) -> bool {
        use std::cmp::Ordering;
        // or use feature(array_windows) on nightly
        let Some(last_ascending) = nums.windows(2).rposition(|w| w[0] < w[1]) else {
                nums.reverse();
                return false;
        };

        let swap_with = nums[last_ascending + 1..]
            .binary_search_by(|n| i32::cmp(&nums[last_ascending], n).then(Ordering::Less))
            .unwrap_err(); // cannot fail because the binary search will never succeed
        nums.swap(last_ascending, last_ascending + swap_with);
        nums[last_ascending + 1..].reverse();
        true
    }

    #[test]
    fn case1_test() {
        let mut z = vec![1, 2, 3];
        let mut t: Vec<Vec<i32>> = vec![vec![]];
        t.clear();
        t.push(z.clone());
        while next_permutation(&mut z) {
            t.push(z.clone());
        }

        println!("{t:?}");
    }
}
