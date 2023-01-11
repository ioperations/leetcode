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
}
