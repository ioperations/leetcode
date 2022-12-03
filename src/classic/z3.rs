#[allow(unused)]
fn reverse_(x: String) -> String {
    if x.is_empty() {
        String::from("")
    } else {
        return format!(
            "{:?}{:?}",
            reverse_(String::from(x.get(1..).unwrap())),
            x.chars().next()
        );
    }
}

#[allow(unused)]
fn reverse(x: String) -> String {
    if x.is_empty() {
        String::from("")
    } else {
        return format!(
            "{}{}",
            reverse(String::from(x.get(1..).unwrap())),
            x.chars().next().unwrap()
        );
    }
}

#[test]
fn string_test() {
    let str = String::from("hello");
    let s = reverse(str);

    println!("{}", s);

    let str1 = String::from("hello");
    let s1 = reverse_(str1);
    println!("{}", s1);
}
