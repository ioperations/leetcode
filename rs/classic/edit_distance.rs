mod str {

    #[allow(dead_code)]
    pub fn edit_distance_fn(a: &str, b: &str) -> usize {
        let len_a = a.chars().count();
        let len_b = b.chars().count();
        if len_a < len_b {
            return edit_distance_fn(b, a);
        }
        // handle special case of 0 length
        if len_a == 0 {
            return len_b;
        } else if len_b == 0 {
            return len_a;
        }

        let len_b = len_b + 1;

        let mut pre;
        let mut tmp;
        let mut cur = vec![0; len_b];

        // initialize string b
        #[allow(clippy::needless_range_loop)]
        for i in 1..len_b {
            cur[i] = i;
        }

        // calculate edit distance
        for (i, ca) in a.chars().enumerate() {
            // get first column for this row
            pre = cur[0];
            cur[0] = i + 1;
            for (j, cb) in b.chars().enumerate() {
                tmp = cur[j + 1];
                cur[j + 1] = std::cmp::min(
                    // deletion
                    tmp + 1,
                    std::cmp::min(
                        // insertion
                        cur[j] + 1,
                        // match or substitution
                        pre + usize::from(ca != cb),
                    ),
                );
                pre = tmp;
            }
        }
        cur[len_b - 1]
    }
} // EditDistance

#[cfg(test)]
mod tests {
    use super::str::edit_distance_fn;

    #[test]
    fn edit_distance_test() {
        let a = "hello";
        let b = "hell";
        assert_eq!(edit_distance_fn(a, b), 1);
    }

    #[test]
    fn edit_distance2_test() {
        let a = "hello";
        let b = "world";
        assert_eq!(edit_distance_fn(a, b), 4);
    }
}
