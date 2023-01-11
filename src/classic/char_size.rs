#[cfg(test)]
mod tests {

    #[test]
    fn char_size_test() {
        let z = 'c';
        assert!(std::mem::size_of_val(&z) == 4);
    }

    #[test]
    fn list_usage_v2() {
        let guo = '国';
        assert!(std::mem::size_of_val(&guo) == 4);
    }
}
