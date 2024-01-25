use std::collections::{HashMap, HashSet};

#[allow(unused)]
fn str_to_hashmap(message: &str) -> HashMap<char, usize> {
    let unique: HashSet<char> = message.chars().collect();
    unique
        .iter()
        .map(|&c| (c, message.matches(c).count()))
        .collect()
}

#[allow(unused)]
fn str_to_hashmap_v2(message: &str) -> HashMap<char, usize> {
    let unique: Vec<char> = message.chars().collect();
    let mut hashmap = HashMap::new();
    for &ele in &unique {
        hashmap.entry(ele).and_modify(|s| *s += 1).or_insert(1);
    }
    hashmap
}

#[cfg(test)]
mod test {

    use super::*;
    extern crate test;

    #[test]
    fn case1() {
        let str = "test_str";
        let hashmap_v1 = str_to_hashmap(str);
        let hashmap_v2 = str_to_hashmap_v2(str);
        assert_eq!(hashmap_v1, hashmap_v2);
    }

    #[bench]
    fn bench_v1(b: &mut test::Bencher) {
        b.iter(|| {
            let str = "test_str_hello_world_too_long";
            let _hashmap_v1 = str_to_hashmap(str);
        });
    }

    #[bench]
    fn bench_v2(b: &mut test::Bencher) {
        b.iter(|| {
            let str = "test_str_hello_world_too_long";
            let _hashmap_v2 = str_to_hashmap(str);
        });
    }
}
