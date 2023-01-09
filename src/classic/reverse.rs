#[allow(unused)]
fn reverse(x: String) -> String {
    if x.is_empty() {
        String::from("")
    } else {
        format!(
            "{}{}",
            reverse(String::from(x.get(1..).unwrap())),
            x.chars().next().unwrap()
        )
    }
}

#[test]
fn reverse_test() {
    let str = String::from("hello");
    let s = reverse(str);

    assert_eq!(s, "olleh".to_string());
}
