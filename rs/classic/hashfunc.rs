#[cfg(test)]
mod tests {
    use hashbrown::HashMap as BrownHash;
    use std::collections::HashMap as StdHash;
    extern crate test;
    const BENCH_SIZE: i32 = 10_000;

    #[bench]
    fn bench_std_hash(b: &mut test::Bencher) {
        b.iter(|| {
            let mut hash_map = StdHash::new();
            (0..BENCH_SIZE).for_each(|i| {
                hash_map
                    .entry(i)
                    .and_modify(|i: &mut i32| *i += 1)
                    .or_default();
            });
        });
    }

    #[bench]
    fn bench_brown_hash(b: &mut test::Bencher) {
        b.iter(|| {
            let mut hash_map = BrownHash::new();
            (0..BENCH_SIZE).for_each(|i| {
                hash_map
                    .entry(i)
                    .and_modify(|i: &mut i32| *i += 1)
                    .or_default();
            });
        });
    }
}
