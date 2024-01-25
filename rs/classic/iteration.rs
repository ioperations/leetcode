#[cfg(test)]
mod tests {

    #[test]
    fn scan_test() {
        let ret = (0..)
            .scan((0, 1), |i, _t| {
                let z = i.0;
                (i.0, i.1) = (i.1, i.0 + i.1);
                Some(z)
            })
            .take(20)
            .collect::<Vec<i32>>();
        println!("{ret:?}");
    }

    #[test]
    fn fold_test() {
        let ret = (1..)
            .scan((0, 1), |i, _t| {
                let z = i.0;
                (i.0, i.1) = (i.1, i.0 + i.1);
                Some(z)
            })
            .take(20)
            .try_fold(0, i32::checked_add);
        //.collect::<Vec<i32>>();
        println!("{ret:?}");
    }

    #[test]
    fn once_test() {
        let data = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
        let ret = data
            .iter()
            .zip(data.iter().skip(1).chain(std::iter::once(&10)))
            .map(|(i, v): (&i32, &i32)| v.checked_sub(*i))
            .map(|v| v.unwrap_or(0))
            .reduce(|e, acc| e + acc);
        assert_eq!(ret, Some(10));
    }
}
