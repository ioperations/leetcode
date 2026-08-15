use rs_le::Hello;

// 1. Basic Struct Test
#[derive(Hello)]
#[allow(unused)]
struct Pancakes;

// 2. Struct with Fields Test
#[derive(Hello)]
#[allow(unused)]
struct User {
    id: u64,
    name: String,
}

// 3. Enum Test
#[derive(Hello)]
#[allow(unused)]
enum Status {
    Active,
    Inactive,
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hello_macro_unit() {
        // Assert trait method calls run without panicking
        assert_eq!(
            "Hello, Macro! My name is Pancakes!",
            Pancakes::hello_macro()
        );
        assert_eq!("Hello, Macro! My name is User!", User::hello_macro());
        assert_eq!("Hello, Macro! My name is Status!", Status::hello_macro());
    }
}
