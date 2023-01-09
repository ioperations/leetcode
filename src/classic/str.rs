#[allow(dead_code)]
fn greetings(s: &str) {
    println!("{s}");
}

#[allow(unused)]
fn reverse_str(str_slice: &str) -> String {
    if str_slice.is_empty() {
        String::new()
    } else {
        let mut ret = reverse_str(&str_slice[1..]);
        ret.push_str(&str_slice[0..1]);
        ret
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn function_name_test() {
        let s: Box<str> = "hello, world".into();
        greetings(s.into_string().as_str())
    }

    #[test]
    fn string_push_test() {
        let mut s = String::from("hello");
        s.push(',');
        s.push_str(" world");
        s += "!";

        println!("{s}")
    }

    #[test]
    fn string_move_test() {
        let s1 = String::from("hello,");
        {
            let s2 = String::from("world!");
            let s3 = String::from(&s1) + s2.as_str();
            assert_eq!(s3, "hello,world!");
        }
        println!("{s1}");
    }

    #[test]
    fn string_revese_test() {
        let s1 = String::from("hello,");
        let ret = reverse_str(s1.as_str());
        assert_eq!(ret, String::from(",olleh"));
    }
}
