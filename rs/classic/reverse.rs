#[allow(unused)]
fn reverse(x: &str) -> String {
    if x.is_empty() {
        String::new()
    } else {
        format!("{}{}", reverse(&x[1..]), x.chars().next().unwrap())
    }
}

#[test]
fn reverse_test() {
    let str = String::from("hello");
    let s = reverse(str.as_str());

    assert_eq!(s, "olleh".to_string());
}
